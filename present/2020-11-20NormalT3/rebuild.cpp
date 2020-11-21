#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge {
	int x, y, z;
} e[410];
inline bool operator<(edge x, edge y)
{
	return x.z<y.z;
}
int f[810], g[810];
inline int find(int x)
{
	return f[x]==x ? x : f[x]=find(f[x]);
}
inline int gind(int x)
{
	return g[x]==x ? x : g[x]=gind(g[x]);
}
struct node
{
	int x, y, next;
}a[810];
int len, last[810];
inline void ins(int x, int y)
{
	len++;
	a[len].x=x;
	a[len].y=y;
	a[len].next=last[x];
	last[x]=len;
}
int n;
long long dp[810][410], F[410][410][2];
int tot[810];
bool u[810], v[810];
void dfs(int x)
{
	if(x<=n) {
		dp[x][1]=1;
		tot[x]=1;
		return ;
	}
	F[0][0][0]=1;
	tot[x]=0;
	int s=0;
	for(int k=last[x]; k>0; k=a[k].next) {
		int y=a[k].y;
		dfs(y);
		if(u[y]) u[x]=true;
		if(v[y]) v[x]=true;
		if(u[y] || v[y]) continue;
		for(int i=0; i<=tot[x]; i++) {
			for(int l=0; l<=s; l++) {
				for(int j=0; j<=tot[y]; j++) {
					F[i][l][0] = F[i][l][0]*tot[y]%998244353;
					F[i][l][1] = F[i][l][1]*tot[y]%998244353;
					F[i+j][l][0] = F[i][l-1][0]*dp[y][j]%998244353;
					F[i+j][l][1] = F[i][l-1][0]*dp[y][j]*tot[y]%998244353;
					F[i+j][l][1] = F[i][l-1][1]*dp[y][j]%998244353;
				}
			}
		}
		tot[x]+=tot[y];
		s++;
	}
}
int main()
{
	freopen("rebuild.in", "r", stdin);
	freopen("rebuild.out", "w", stdout);
	scanf("%d", &n);
	for(int i=1; i<n; i++) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
	sort(e+1, e+n);
	int N=n;
	for(int i=1; i<=n; i++) f[i]=g[i]=i;
	int j=1;
	len=0;
	memset(last, 0, sizeof(last) );
	for(int i=1; i<n; i++) {
		int k=j;
		while(k<n && i==e[k].z) {
			int gx=gind( find(e[k].x) ), gy=gind( find(e[k].y) );
			N++;
			f[N]=g[N]=N;
			g[gx]=g[gy]=N;
			k++;
		}
		while(j<n && i==e[j].z) {
			int fx=find(e[j].x), fy=find(e[j].y);
			int G=gind(fx);
			if(G!=fx) {
				f[fx]=G;
				ins(G, fx);
			}
			if(G!=fy) {
				f[fy]=G;
				ins(G, fy);
			}
			j++;
		}
	}
	int U, V;
	scanf("%d%d", &U, &V);
	memset(u, false, sizeof(u) );
	memset(v, false, sizeof(v) );
	u[U]=v[V]=true;
	dfs(N);
	return 0;
}