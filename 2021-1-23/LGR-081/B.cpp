#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int dep[1010000];
long long c[1010000],tot[1010000];
void dfs(int x,int fa)
{
	tot[x]=c[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dep[y]=dep[x]+1;
			dfs(y,x);
			tot[x]=(tot[x]+tot[y])%99991;
		}
	}
}
long long f[1010000],ff[1010000];
void dp(int x,int fa)
{
	f[x]=ff[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dp(y,x);
			f[x]=(f[x]+f[y]+tot[y])%99991;
			ff[x]=(ff[x]+ff[y]+tot[y]*(tot[1]-tot[y]+99991))%99991;
		}
	}
}
long long g[1010000],gg[1010000];
void hg(int x,int fa)
{
	long long gl=g[x],ggl=gg[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			gl=(gl+f[y]+tot[y])%99991;
			ggl=(ggl+ff[y]+tot[y]*(tot[1]-tot[y]+99991))%99991;
		}
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			g[y]=(gl+tot[1]-tot[y]-f[y]-tot[y]+199982)%99991;
			gg[y]=(ggl-ff[y]+99991)%99991;
			hg(y,x);
		}
	}
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	dep[1]=1;dfs(1,0);
	dp(1,0);
	g[1]=gg[1]=0;hg(1,0);
	long long s1=0,s2=0;
	for(int i=1;i<=m;i++)
	{
		int e;scanf("%d",&e);
		int x=a[e*2].x,y=a[e*2].y;
		if(dep[x]>dep[y])x^=y^=x^=y;
		long long tg=(tot[1]-tot[y]+99991)%99991;
		long long ss=((gg[y]+tot[y]*(tot[1]-tot[y]+99991)%99991)*tot[y]-(g[y]+tg+99991)%99991*tot[y]*tot[y]%99991+199982+ff[y]*tg-f[y]*tg*tg%99991)%99991;
		s1=s1+ss;s2=s2^ss;
	}
	printf("%lld\n%lld\n",s1,s2);
	return 0;
}