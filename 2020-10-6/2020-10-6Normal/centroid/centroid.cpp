#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[110000];int len,last[51000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long f[51000][510][2],g[51000][510],c[51000];
int m,s[51000];
long long ss=0;
void dfs(int x,int fa)
{
	s[x]=1;
	f[x][1][0]=f[x][1][1]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			s[x]+=s[y];
			for(int i=s[x]>m?m:s[x];i>=1;i--)
			{
				for(int j=i-s[x]+s[y]<1?1:i-s[x]+s[y];j<=i&&j<=s[y];j++)
				{
					if(j<(m+1)/2)f[x][i][1]=(f[x][i][1]+f[x][i-j][1]*f[y][j][0])%1000000007;
					f[x][i][0]=(f[x][i][0]+f[x][i-j][0]*f[y][j][0])%1000000007;
					g[x][i]=(g[x][i]+g[x][i-j]*f[y][j][0]+g[y][j]*f[x][i-j][0])%1000000007;
				}
			}
		}
	}
	for(int i=(m+1)/2;i<=m;i++)g[x][i]=(g[x][i]+(m%2==0&&i==m/2&&fa<x?c[fa]:c[x])*f[x][i][1])%1000000007;
	ss=(ss+g[x][m])%1000000007;
}
int main()
{
	freopen("centroid.in","r",stdin);
	freopen("centroid.out","w",stdout);
	int n;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	dfs(1,0);
	printf("%lld\n",ss);
	return 0;
}