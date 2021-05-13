#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[1100];int len,last[510];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long jc[510],fjc[510];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
long long f[151][151][151],g[151][151];
int tot[510];
void dfs(int x,int fa)
{
	tot[x]=0;f[x][0][0]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			for(int i=0;i<=tot[x];i++)
			{
				for(int j=0;j<=i;j++)
				{
					for(int k=0;k<=tot[y];k++)
					{
						for(int l=0;l<=k;l++)
						{
							g[i+k][j+l]=(g[i+k][j+l]+f[x][i][j]*f[y][k][l])%998244353;
						}
					}
				}
			}
			tot[x]+=tot[y];
			for(int i=0;i<=tot[x];i++)
			{
				for(int j=0;j<=i;j++)
				{
					f[x][i][j]=g[i][j];
					g[i][j]=0;
				}
			}
		}
	}
	tot[x]++;
	for(int j=tot[x];j>=1;j--)
	{
		long long s=0;
		for(int i=j;i<=tot[x];i++)
		{
			s=(s+f[x][i-1][j-1]*jc[i-1]%998244353*jc[tot[x]-i])%998244353;
			f[x][i][j]=(f[x][i][j]+s*fjc[i]%998244353*fjc[tot[x]-i])%998244353;
		}
	}
}
int main()
{
	freopen("increase.in","r",stdin);
	freopen("increase.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	dfs(1,0);
	long long ss=0;
	for(int i=1;i<=m;i++)ss+=f[1][n][i];
	printf("%lld\n",ss%998244353);
	return 0;
}
