#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long f[110000],s[110000];
void dfs(int x,int fa)
{
	f[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			s[x]+=s[y];
			f[x]+=f[y]+a[k].c*s[y];
		}
	}
}
long long ss;int p,ddp;
void dfs(int x,int fa,long long fg,long long st,int dp)
{
	if(fg+f[x]<ss||fg+f[x]==ss&&dp<ddp)ss=fg+f[x],p=x,ddp=dp;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,fg+f[x]+a[k].c*(st+s[x]-s[y])-f[y]-a[k].c*s[y],st+s[x]-s[y],dp+a[k].c);
	}
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	dfs(1,0);
	ss=0x3f3f3f3f3f3f3f3fll;
	dfs(1,0,0,0,0);
	printf("%d\n%lld\n",p,ss);
	return 0;
}