#include "guess.h"
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <unordered_map>
#include <cstdint>
#include <bitset>
using namespace std;

#define LOG(f...) fprintf(stderr, f)

namespace sample_grader {
  const char token[] = "Correct!";

  mt19937 rng;

  const int N = 3005;
  const int LOG_LIM = 500;

  vector<int> G[N];
  int st[16][N * 2];
  int lg[N * 2];
  int fst[N], dep[N], euler_dfc = 0, dfc = 0;
  int dfn[N];

  void DFS(int x, int fa = 0) {
    st[0][++euler_dfc] = x; fst[x] = euler_dfc;
    dfn[++dfc] = x;
    if (fa)
      G[x].erase(find(begin(G[x]), end(G[x]), fa));
    for (int v : G[x]) {
      dep[v] = dep[x] + 1;
      DFS(v, x);
      st[0][++euler_dfc] = x;
    }
  }

  int min_dep(int x, int y) { return dep[x] < dep[y] ? x : y; }

  void pre_log2() {
    for (int i = 2; i < (N * 2); i <<= 1)
      lg[i] = 1;
    for (int i = 3; i < (N * 2); ++i)
      lg[i] += lg[i - 1];
  }
  void build_st() {
    for (int i = 1; i <= lg[euler_dfc]; ++i)
      for (int j = 1, li = euler_dfc - (1 << i) + 1; j <= li; ++j)
        st[i][j] = min_dep(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
  }

  int LCA(int x, int y) {
    x = fst[x]; y = fst[y];
    if (x > y)
      swap(x, y);
    int k = lg[y - x + 1];
    return min_dep(st[k][x], st[k][y - (1 << k) + 1]);
  }

  unordered_map<uint32_t, bool> edges;
  int cnt_query = 0;
  int n, L, data_type;
  int reported = 0;
}

int query(const vector<int> &S) {
  using namespace sample_grader;
  ++cnt_query;
  if (cnt_query > L)
    printf("FAIL : Query limit exceeded\n"), exit(0);
  if ((int)S.size() < 2)
    printf("FAIL : Query with |S| < 2"), exit(0);
  for (int x : S)
    if (x < 1 || x > n)
      printf("FAIL : Vertex id not in [1, n]\n"), exit(0);
  int cnt = S.size();

  if (cnt <= LOG_LIM) {
    static int A[LOG_LIM];
    copy(begin(S), end(S), A);
    sort(A, A + cnt, [](int x, int y) { return fst[x] < fst[y]; });
    int maxd = -1, pos = 0;
    for (int i = 1; i < cnt; ++i) {
      if (A[i - 1] == A[i])
        printf("FAIL : Duplicate vertices in single query\n"), exit(0);
      int D = dep[LCA(A[i - 1], A[i])];
      if (D > maxd) {
        maxd = D;
        pos = LCA(A[i - 1], A[i]);
      }
    }
    return pos;
  }
  else {
    static bitset<N> vis;
    vis.reset();
    for (int x : S) {
      if (vis._Unchecked_test(x))
        printf("FAIL : Duplicate vertices in single query\n"), exit(0);
      vis._Unchecked_set(x);
    }
    for (int i = n; i >= 1; --i) {
      int cnt = 0;
      for (int v : G[dfn[i]])
        cnt += vis._Unchecked_test(v);
      cnt += vis._Unchecked_test(dfn[i]);
      if (cnt >= 2)
        return dfn[i];
      if (cnt)
        vis.set(dfn[i]);
    }
    printf("GRADER ERROR : Answer not found!\n");
    throw;
  }
}

void report(int u, int v) {
  using namespace sample_grader;
  if (u < 1 || u > n)
    printf("FAIL : Report u not in [1, n]\n"), exit(0);
  if (v < 1 || v > n)
    printf("FAIL : Report v not in [1, n]\n"), exit(0);
  if (u > v)
    swap(u, v);
  uint32_t id = uint32_t(u) << 15 | uint32_t(v);
  auto it = edges.find(id);
  if (it == edges.end())
    printf("FAIL : Reported edge (%d, %d) does not exist\n", u, v), exit(0);
  if (it->second)
    printf("FAIL : Duplicate edge (%d, %d) reported\n", u, v), exit(0);
  it->second = true;
  ++reported;
}
void mian() {
  using namespace sample_grader;
  pre_log2();
  int T;
  assert(scanf("%d", &T) == 1);
  for (int caseid = 1; caseid <= T; ++caseid) {
    euler_dfc = 0; dfc = 0;
    assert(scanf("%d%d%d", &n, &L, &data_type) == 3);
    edges.clear();
    reported = 0;
    cnt_query = 0;
    for (int i = 1; i <= n; ++i)
      G[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v;
      assert(scanf("%d%d", &u, &v) == 2);
      if (u > v)
        swap(u, v);
      edges.emplace(uint32_t(u) << 15 | uint32_t(v), false);
      G[u].emplace_back(v); G[v].emplace_back(u);
    }
    assert((int)edges.size() == n - 1);
    DFS(1);
    build_st();

    solve(n, L, data_type);
    if (reported != n - 1)
      printf("FAIL : Some edges not reported\n"), exit(0);
    printf("Case %d : %d / %d query\n", caseid, cnt_query, L);
  }
  printf("%s\n", token);
  printf("Real time : %lldms\n", clock() * 1000LL / CLOCKS_PER_SEC);
}


