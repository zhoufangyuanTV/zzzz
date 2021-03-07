#include<cstdio>
#include<cstring>
using namespace std;
int z[11000];
int a[11000],b[11000],d[11000];
int f[610][610],g[610][610];
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		memset(z,0,sizeof(z));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&a[i],&b[i],&d[i]);
			z[a[i]]=z[b[i]]=1;
		}
		for(int i=2;i<=10000;i++)z[i]+=z[i-1];
		memset(g,-1,sizeof(g));
		for(int i=1;i<=n;i++)
		{
			a[i]=z[a[i]];b[i]=z[b[i]];
			if(g[a[i]][b[i]]==-1||d[g[a[i]][b[i]]]<d[i])g[a[i]][b[i]]=i;
		}
		memset(f,0,sizeof(f));
		for(int i=z[10000];i>=1;i--)
		{
			for(int j=i;j<=z[10000];j++)
			{
				if(g[i+1][j]!=-1)
				{
					if(g[i][j]==-1||d[g[i][j]]<d[g[i+1][j]])g[i][j]=g[i+1][j];
				}
				if(g[i][j-1]!=-1)
				{
					if(g[i][j]==-1||d[g[i][j]]<d[g[i][j-1]])g[i][j]=g[i][j-1];
				}
				if(g[i][j]!=-1)
				{
					f[i][j]=0x3f3f3f3f;
					for(int k=a[g[i][j]];k<=b[g[i][j]];k++)
					{
						f[i][j]=mymin(f[i][j],f[i][k-1]+d[g[i][j]]+f[k+1][j]);
					}
				}
			}
		}
		printf("%d\n",f[1][z[10000]]);
	}
	return 0;
}