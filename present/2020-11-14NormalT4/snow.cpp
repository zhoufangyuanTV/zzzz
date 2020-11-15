#include <cstdio>
#include <cstring>
using namespace std;
struct node {
	int x, y, next;
} a[410000];
int len, last[210000];
inline void ins(int x, int y)
{
	len++;
	a[len].x=x;
	a[len].y=y;
	a[len].next=last[x];
	last[x]=len;
}
int n, fa[210000], dep[210000], son[210000], tot[210000];
void dfs(int x)
{
	son[x]=0;
	tot[x]=1;
	for(int k=last[x]; k>0; k=a[k].next) {
		int y=a[k].y;
		if(y!=fa[x]) {
			fa[y]=x;
			dep[y] = dep[x]+1;
			dfs(y);
			if(tot[ son[x] ]<tot[y]) son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
int z, ys[210000], top[210000];
void dfs(int x, int tp)
{
	ys[x]=++z;
	top[x]=tp;
	if(son[x]!=0) dfs(son[x], tp);
	for(int k=last[x]; k>0; k=a[k].next) {
		int y=a[k].y;
		if(y!=fa[x] && y!=son[x]) dfs(y,y);
	}
}
int w[210000];
int d[210000], maxz[210000], zz[210000];
struct trnode {
	int l, r, lc, rc;
	long long w, mc;
	long long du, z;
} tr[410000];
int trlen;
inline int mymin(int x, int y)
{
	return x<y ? x : y;
}
void bt(int l, int r)
{
	int now=++trlen;
	tr[now].l=l;
	tr[now].r=r;
	tr[now].lc=tr[now].rc=-1;
	if(l<r) {
		int mid = (l+r)/2;
		tr[now].lc = trlen+1;
		bt(l, mid);
		tr[now].rc = trlen+1;
		bt(mid+1, r);
		tr[now].w = tr[tr[now].lc].w+tr[tr[now].rc].w;
		tr[now].mc=mymin(tr[tr[now].lc].mc, tr[tr[now].rc].mc);
		tr[now].du=tr[now].z=0;
	} else {
		int x=tr[now].l;
		if(maxz[x]*2 > d[x]) {
			tr[now].w=w[x];
			tr[now].mc = maxz[x]*2 - d[x];
		} else {
			tr[now].w=0;
			tr[now].mc=0x3f3f3f3f3f3f3f3fll;
		}
		tr[now].du=d[x];
		tr[now].z=zz[x];
	}
}
void change(int now, int l, int r, int c)
int main()
{
	freopen("snow.in", "r", stdin);
	freopen("snow.out", "w", stdout);
	return 0;
}