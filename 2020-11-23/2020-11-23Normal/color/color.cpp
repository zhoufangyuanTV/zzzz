#include<cstdio>
#include<cstring>
using namespace std;
int a[210][11000],g[210];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	if(m>n*(n*2-1)){puts("-1");return 0;}
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++)g[i]=i;
	for(int i=1;i<=m;i++)
	{
		if((i-1)%(n*2-1)==0)
		{
			int t=g[1];
			for(int j=1;j<=n;j++)g[j]=g[j+1];
			g[n]=t;
		}
		int ic=(i-1)%(n*2-1)+1;
		int len=0;
		for(int j=1;j<=n*2;j++)
		{
			if(a[j][i]==0)
			{
				a[j][i]=g[++len];
				int k=ic-j+2;
				if(k<1)k+=2*n-1;
				if(j!=k)a[k][i]=g[len];
				else a[2*n][i]=g[len];
			}
		}
	}
	for(int i=1;i<=n*2;i++)
	{
		for(int j=1;j<m;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("%d\n",a[i][m]);
	}
	return 0;
}