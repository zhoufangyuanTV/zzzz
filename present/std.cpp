#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200001, INF = 1 << 30;

struct Edge{
	int y, c, nxt;
} adj[MAXN*2];

struct Child{
	int id, col;
} chd[MAXN];//children

int val[MAXN];
int fch[MAXN];
bool vis[MAXN];
int que[MAXN];//for div&con
int sz[MAXN], id[MAXN], par[MAXN];
int dep[MAXN], wei[MAXN], col[MAXN];
int Q[MAXN], qs;//for bfs
int a[MAXN], as;//subtree
int b1[MAXN], b2[MAXN], bc1[MAXN], bc2[MAXN], b[MAXN], bs;
int n, m, L, R, ms, ans, si;

void add(int u, int v, int c){
	adj[++ ms] = (Edge){v, c, fch[u]}; fch[u] = ms;
}

void init()
{
	scanf("%d%d%d%d", &n, &m, &L, &R);
	for (int i = 0; i < m; i ++)
		scanf("%d", &val[i]);
	memset(fch, 0, sizeof(fch));
	ms = 0;
	for (int i = 1; i < n; i ++){
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		c --;
		add(u, v, c);
		add(v, u, c);
	}
}

void bfs(int r, int w)
{
	int h = 0, t = 0; as = 0;
	Q[0] = r; par[r] = 0; id[r] = ++ si;
	dep[r] = 1; wei[r] = val[w]; col[r] = w;
	while (h <= t){
		int u = Q[h ++];
		if (dep[u] > as)
			a[++ as] = wei[u];
		else if (wei[u] > a[dep[u]])
			a[dep[u]] = wei[u];
		for (int i = fch[u]; i; i = adj[i].nxt){
			int v = adj[i].y;
			if (vis[v] || id[v] == si) continue;
			id[v] = si; par[v] = u; col[v] = adj[i].c;
			dep[v] = dep[u] + 1;
			wei[v] = wei[u];
			if (col[v] != col[u]) wei[v] += val[col[v]];
			Q[++ t] = v;
		}
	}
	qs = t+1;
}

int find_root()
{
	int r = Q[0], w = qs;
	for (int j = qs-1; j >= 0; j --){
		int u = Q[j], s = 0;
		sz[u] = 1;
		for (int i = fch[u]; i; i = adj[i].nxt){
			int v = adj[i].y;
			if (vis[v] || v == par[u]) continue;
			sz[u] += sz[v];
			if (sz[v] > s) s = sz[v];
		}
		if (qs - sz[u] > s) s = qs - sz[u];
		if (s < w){
			w = s; r = u;
		}
	}
	return r;
}

void check(int extra){
	int h = 0, t = -1, p = bs;
	for (int i = 1; i <= as; i ++){
		while (p >= 0 && p + i >= L){
			while (h <= t && b[Q[t]] <= b[p]) t --;
			Q[++ t] = p --;
		}
		while (h <= t && Q[h] + i > R)
			h ++;
		if (h <= t && ans < b[Q[h]] + a[i] + extra)
			ans = b[Q[h]] + a[i] + extra;
	}
}

bool cmp(Child x, Child y){
	return sz[x.id] < sz[y.id];
}

void solve()
{
	int h = 0, t = 0; que[0] = 1; ans = -INF;
	while (h <= t){
		int u = que[h ++];
		//find
		bfs(u, 0);
		u = find_root();
		//sort children
		bfs(u, 0);
		find_root();
		int cs = 0;
		for (int i = fch[u]; i; i = adj[i].nxt){
			int v = adj[i].y;
			if (vis[v]) continue;
			chd[cs ++] = (Child){v, adj[i].c};
		}
		sort(chd, chd + cs, cmp);
		//calculate
		vis[u] = true;
		bs = 0; b1[0] = 0; bc1[0] = -1; b2[0] = -INF;
		for (int i = 0; i < cs; i ++){
			bfs(chd[i].id, chd[i].col);
			//check
			if (as + bs >= L){
				for (int j = 0; j <= bs; j ++)
					if (chd[i].col == bc1[j]) b[j] = b2[j];
						else b[j] = b1[j];
				check(0);
				for (int j = 0; j <= bs; j ++)
					if (chd[i].col == bc1[j]) b[j] = b1[j];
						else if (chd[i].col == bc2[j]) b[j] = b2[j];
							else b[j] = -INF;
				check(-val[chd[i].col]);
			}
			//merge
			for (int j = 1; j <= bs; j ++)
				if (chd[i].col == bc1[j]){
					if (a[j] > b1[j])
						b1[j] = a[j];
				} else {
					if (a[j] > b1[j]){
						b2[j] = b1[j]; bc2[j] = bc1[j];
						b1[j] = a[j]; bc1[j] = chd[i].col;
					} else if (a[j] > b2[j]){
						b2[j] = a[j]; bc2[j] = chd[i].col;
					}
				}
			for (int j = bs+1; j <= as; j ++){
				b1[j] = a[j]; bc1[j] = chd[i].col;
				b2[j] = -INF; bc2[j] = -1;
			}
			bs = as;
			if ((as-1)*2 >= L)//insert
				que[++ t] = chd[i].id;
		}
	}
}

int main()
{
	freopen("journey.in", "r", stdin);
	freopen("journey.ans", "w", stdout);
	init();
	solve();
	printf("%d\n", ans);
	return 0;
}