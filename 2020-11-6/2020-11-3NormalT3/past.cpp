#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
char buf[1<<21], *p1=buf, *p2=buf;
#define getchar()\
(p1==p2 && (p2 = (p1=buf)+fread(buf, 1, 1<<21, stdin), p1==p2) ? EOF : *p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') {
		x = x*10 + c - '0';
		c=getchar();
	}
}
struct node {
	int x, y, next;
} a[610000];
int len, last[310000];
inline void ins(int x, int y)
{
	len++;
	a[len].x=x;
	a[len].y=y;
	a[len].next=last[x];
	last[x]=len;
}
int dS[310000];
int z, dfn[610000], in[310000], out[310000];
void dfs(int x, int fa)
{
	dfn[++z]=x;
	in[x]=z;
	for(int k=last[x]; k>0; k=a[k].next) {
		int y=a[k].y;
		if(y!=fa) {
			dS[y] = dS[x]+1;
			dfs(y, x);
			dfn[++z]=x;
		}
	}
	out[x]=z;
}
inline int mymin(int x, int y)
{
	return dS[x]<dS[y] ? x : y;
}
int log2[610000];
int st[610000][20];
void build()
{
	log2[0]=-1;
	for(int i=1; i<=z; i++) log2[i] = log2[i/2]+1;
	for(int i=1; i<=z; i++) st[i][0]=dfn[i];
	for(int j=1; j<=log2[z]; j++) {
		for(int i=1; i <= z-(1<<j)+1; i++)
			st[i][j]=mymin(st[i][j-1], st[i+(1 << j-1)][j-1]);
	}
}
inline int lca(int x, int y)
{
	int l=in[x], r=in[y];
	return mymin(st[l][ log2[r-l+1] ], st[r-(1<<log2[r-l+1])+1][ log2[r-l+1] ]);
}
bool b[310000];
int tot[310000];
void count(int x, int fa)
{
	tot[x]=1;
	for(int k=last[x]; k>0; k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa && b[y]) {
			count(y, x);
			tot[x]+=tot[y];
		}
	}
}
int ce, ff, size;
void find(int x, int fa)
{
	int f = size-tot[x];
	for(int k=last[x]; k>0; k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa && b[y]) {
			find(y, x);
			if(f<tot[y]) f=tot[y];
		}
	}
	if(f<ff) ce=x, ff=f;
}
int DT[310000];
int plen, p[310000];
bool g[310000];
void add(int x, int fa)
{
	p[++plen]=x;
	g[x]=true;
	for(int k=last[x]; k>0; k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa && b[y]) {
			DT[y] = DT[x]+1;
			add(y, x);
		}
	}
}
inline bool cmp(int x, int y)
{
	return in[x]<in[y];
}
int sta[310000], top;
vector<int> son[310000];
int js[1024], pp[310000];
int im()
{
	if(plen<=100) sort(p+1, p+plen+1, cmp);
	else {
		memset(js, 0, sizeof(js) );
		for(int i=1; i<=plen; i++) js[in[ p[i] ]&1023 ^ 1023]++;
		for(int i=1; i<1024; i++) js[i]+=js[i-1];
		for(int i=1; i<=plen; i++) pp[js[in[ p[i] ]&1023 ^ 1023]--]=p[i];
		memset(js, 0, sizeof(js) );
		for(int i=1; i<=plen; i++) js[in[ pp[i] ]>>10]++;
		for(int i=1; i<1024; i++) js[i]+=js[i-1];
		for(int i=1; i<=plen; i++) p[js[in[ pp[i] ]>>10]--]=pp[i];
	}
	top=1;
	sta[1]=p[1];
	for(int i=2; i<=plen; i++)
	{
		int fa=lca(p[i-1], p[i]);
		while(top>0 && dS[fa]<dS[ sta[top] ]) {
			if(sta[top]!=p[i-1]) son[ sta[top] ].push_back(sta[top+1]);
			top--;
		}
		if(fa!=p[i-1]) son[fa].push_back(sta[top+1]);
		if(fa!=sta[top]) sta[++top]=fa;
		sta[++top]=p[i];
	}
	while(--top) son[ sta[top] ].push_back(sta[top+1]);
	return sta[1];
}
int ss=0, s;
long long fd[310000], Lv[310000], SdS[310000], SDT[310000];
inline int plus(int x, int y)
{
	return x+y >= 998244353 ? x+y-998244353 : x+y;
}
void treedp(int x)
{
	if(g[x]) {
		g[x]=false;
		fd[x]=0;
		Lv[x]=1;
		SdS[x]=0;
		SDT[x]=DT[x];
	} else {
		fd[x]=0;
		Lv[x]=0;
		SdS[x]=0;
		SDT[x]=0;
	}
	for(int y:son[x]) {
		treedp(y);
		fd[y] = (fd[y] + SDT[y]*(dS[y]-dS[x]) )%998244353;
		SdS[y] = (SdS[y] + Lv[y]*(dS[y]-dS[x]) )%998244353;
		s = (s + fd[x]*Lv[y] + fd[y]*Lv[x])%998244353;
		s = (s + SdS[x]*SDT[y] + SdS[y]*SDT[x])%998244353;
		fd[x]=plus(fd[x], fd[y]);
		Lv[x]=plus(Lv[x], Lv[y]);
		SdS[x]=plus(SdS[x], SdS[y]);
		SDT[x]=plus(SDT[x], SDT[y]);
	}
	son[x].clear();
}
void div(int x)
{
	count(x, 0);
	ff=0x3f3f3f3f;
	size=tot[x];
	find(x, 0);
	DT[ce]=0;
	plen=0;
	add(ce, 0);
	int irt=im();
	s=0;
	treedp(irt);
	ss=plus(ss, s);
	for(int k=last[ce]; k>0; k=a[k].next) {
		int y=a[k].y;
		if(b[y]) {
			plen=0;
			add(a[k].y, ce);
			irt=im();
			s=0;
			treedp(irt);
			ss=plus(ss, 998244353-s);
		}
	}
	b[ce]=false;
	for(int k=last[ce]; k>0; k=a[k].next) {
		int y=a[k].y;
		if(b[y]) div(y);
	}
}
int main()
{
	freopen("past.in", "r", stdin);
	freopen("past.out", "w", stdout);
	int n;
	read(n);
	len=0;
	memset(last, 0, sizeof(last) );
	for(int i=1; i<n; i++) {
		int x, y;
		read(x);
		read(y);
		ins(x, y);
		ins(y, x);
	}
	dS[1]=1;
	z=0;
	dfs(1, 0);
	build();
	len=0;
	memset(last, 0, sizeof(last) );
	for(int i=1; i<n; i++) {
		int x, y;
		read(x);
		read(y);
		ins(x, y);
		ins(y, x);
	}
	memset(b, true, sizeof(b) );
	div(1);
	printf("%d\n", ss);
	return 0;
}