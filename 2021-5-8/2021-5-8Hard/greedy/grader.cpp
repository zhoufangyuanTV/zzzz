#include "greedy.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
const int N = 3005;
struct Gedge{
	int Gto, Gnxt;
}Gtree[N << 1];
int Gn, Groot, Gty, Ghead[N], Gin[N], Gout[N], Gid[N], Gparent[N], Gcnt = 0, Gtot = 0;
void Gread (int *x) {
	int sgn = 1;
	char ch;
	*x = 0;
	for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar()) ;
	if (ch == '-') ch = getchar(), sgn = -1;
	for (; '0' <= ch && ch <= '9'; ch = getchar()) *x = *x * 10 + ch - '0';
	*x *= sgn;
}
void Gwrite (int x) {
	if (x < 0) putchar('-'), Gwrite(-x);
	else if (x < 10) putchar(x + '0');
	else Gwrite(x / 10), putchar(x % 10 + '0');
}
void Gaddedge (int u, int v) {
	Gedge x = {v, Ghead[u]};
	Gtree[Ghead[u] = Gcnt++] = x;
}
void Gdfs (int u, int fa) {
	Gin[u] = ++Gtot, Gid[Gtot] = u, Gparent[u] = fa;
	for (int i = Ghead[u]; ~i; i = Gtree[i].Gnxt) {
		int v = Gtree[i].Gto;
		if(v != fa)Gdfs(v, u);
	}
	Gout[u] = Gtot;
}
bool Gvis[N];
int Gask_cnt = 0;
bool Gcheck (int sz, int *vec) {
	if (sz <= 0 || sz > Gn) return false;
	for (int i = 1; i <= Gn; i++) Gvis[i] = false;
	for (int i = 0; i < sz; i++) {
		if (vec[i] <= 0 || vec[i] > Gn) return false;
		if (Gvis[vec[i]]) return false;
		Gvis[vec[i]] = true;
	}
	return true;
}
int GAsk (int sz, int *vec) {
	Gask_cnt++;
	if (!Gcheck(sz, vec)) {
		printf("Wrong Answer [1]\n");
		exit(0);
	}
	int ans = 0;
	for (int i = 1; i <= Gn; i++) Gvis[i] = false;
	for (int i = 0; i < sz; i++) {
		int u = vec[i];
		if (!Gvis[u]) {
			ans++;
			for (int v = u; !Gvis[v]; v = Gparent[v]) Gvis[v] = true;
			for (int j = Gin[u]; j <= Gout[u]; j++) Gvis[Gid[j]] = true;
		}
	}
	return ans;
}
bool has_answer = false;
void GAnswer(int *par){
	bool right = true;
	has_answer = true;
	for (int i = 1; i <= Gn; i++) {
		if (par[i - 1] != Gparent[i]) {
			printf("Wrong Answer [3]\n"), right = false;
			exit(0);
		}
	}
	if (right) {
		printf("Accepted\n");
		printf("Attempts: %d\n", Gask_cnt);
		exit(0);
	}
}
void GSolve (int n, int ty) {
	solve(n, ty);
	if (!has_answer) printf("No Answer\n");
}
void Gmain () {
	Gread(&Gn), Gread(&Groot),  Gread(&Gty);
	for (int i = 1; i <= Gn; i++) Ghead[i] = -1;
	for (int i = 1; i < Gn; i++) {
		int u, v;
		Gread(&u), Gread(&v);
		Gaddedge(u, v), Gaddedge(v, u);
	}
	Gdfs(Groot, 0);
	GSolve(Gn, Gty);
}
int ask (int sz, int *vec) {
	return GAsk(sz, vec);
}
void answer (int *par) {
	GAnswer(par);
}
