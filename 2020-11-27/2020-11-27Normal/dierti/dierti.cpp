#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,next;
}a[810000];int len,last[810000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int z,in[810000],out[810000];
int f[810000],g[810000];
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x)
{
	in[x]=++z;
	g[x]=x;
	int gg=0x3f3f3f3f;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		dfs(y);
		if(g[y]<g[x])gg=g[x],g[x]=g[y];
		else if(g[y]<gg)gg=g[y];
	}
	if(gg<x)f[x]=gg;
	else f[x]=x;
	out[x]=z;
}
struct el
{
	int x,t;
}ex[810000];
inline bool cmp(el x,el y){return x.t<y.t;}
inline int lowbit(int x){return x&-x;}
int n,c[810000],cc[810000];
void change(int h[810000],int x,int s)
{
	while(x<=n)
	{
		h[x]+=s;
		x+=lowbit(x);
	}
}
int sum(int h[810000],int x)
{
	int s=0;
	while(x>0)
	{
		s+=h[x];
		x-=lowbit(x);
	}
	return s;
}
int main()
{
	freopen("dierti.in","r",stdin);
	freopen("dierti.out","w",stdout);
	scanf("%d",&n);
	int rt;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)
	{
		int fa;scanf("%d",&fa);
		if(fa==0)rt=i;
		else ins(fa,i);
	}
	z=0;dfs(rt);
	for(int i=1;i<=n;i++)ex[i]=(el){i,f[i]};
	sort(ex+1,ex+n+1,cmp);
	long long ss=1,s=0;
	memset(c,0,sizeof(c));
	memset(cc,0,sizeof(cc));
	int j=1;
	for(int i=1;i<=n;i++)
	{
		while(j<=n&&ex[j].t==i)
		{
			change(c,in[ex[j].x],1);
			change(c,out[ex[j].x]+1,-1);
			s=(s+sum(cc,out[ex[j].x])-sum(cc,in[ex[j].x]-1))%1000000007;
			j++;
		}
		s=(s+sum(c,in[i]))%1000000007;
		change(cc,in[i],1);
		ss=ss*s%1000000007;
	}
	printf("%lld\n",ss);
	return 0;
}