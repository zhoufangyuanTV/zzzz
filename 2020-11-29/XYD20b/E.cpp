#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long f[410];
void dfs(int x,int fa,int dep)
{
	f[dep]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,dep+1);
	}
}
long long F[410][410],Ans[410];
int main()
{
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(Ans,0,sizeof(Ans));
	for(int i=1;i<=n;i++)
	{
		memset(F,0,sizeof(F));
		for(int j=1;j<n;j++)F[j][0]=1;
		for(int k=last[i];k>0;k=a[k].next)
		{
			int y=a[k].y;
			memset(f,0,sizeof(f));
			dfs(y,i,1);
			for(int j=1;j<n;j++)
			{
				for(int K=n-1;K>=1;K--)
				{
					F[j][K]=(F[j][K]+F[j][K-1]*f[j])%998244353;
				}
			}
		}
		for(int j=1;j<n;j++)
		{
			for(int k=1;k<n;k++)Ans[k]=(Ans[k]+F[j][k])%998244353;
		}
	}
	for(int i=3;i<n;i++)printf("%lld\n",Ans[i]);
	return 0;
}