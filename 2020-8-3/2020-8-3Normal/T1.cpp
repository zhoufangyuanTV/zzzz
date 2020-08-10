#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int g[210000];
long long h[210000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
int dep[210000];
void dfs(int x,int fa)
{
	g[x]=0;h[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dep[y]=dep[x]+1;
			dfs(y,x);
			h[x]=mymax(h[x],h[y]+a[k].c);
		}
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&h[x]==h[y]+a[k].c)
		{
			if(g[x]==0)g[x]=g[y];
			else g[x]=x;
		}
	}
	if(g[x]==0)g[x]=x;
}
int main()
{
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	dfs(1,0);
	int x=g[1];dep[x]=0;
	dfs(x,0);
	int cnt=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(h[x]==h[y]+a[k].c)cnt++;
	}
	if(cnt>2)
	{
		printf("%lld\n0\n",h[x]*2);
		return 0;
	}
	long long hh=0;int gg=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(gg==0&&h[x]==h[y]+a[k].c)gg=g[y];
		else hh=mymax(hh,h[y]+a[k].c);
	}
	cnt=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(gg!=g[y]&&hh==h[y]+a[k].c)cnt++;
	}
	if(cnt>1)
	{
		printf("%lld\n%d\n",h[x]+hh,dep[gg]);
		return 0;
	}
	int ggg=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(gg!=g[y]&&hh==h[y]+a[k].c)ggg=g[y];
	}
	printf("%lld\n%d\n",h[x]+hh,dep[gg]+dep[ggg]);
	return 0;
}