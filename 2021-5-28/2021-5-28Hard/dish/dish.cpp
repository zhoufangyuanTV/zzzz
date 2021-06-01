#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n,g;
int a[1010000],b[1010000],c[1010000];
int f[1100][1100];
bool dfs(int t)
{
	if(t==n*(n-1)/2*g/3+1)
	{
		printf("%d\n",t-1);
		for(int i=1;i<t;i++)printf("%d %d %d\n",a[i],b[i],c[i]);
		fflush(stdout);
		return true;
	}
	else
	{
		for(int i=1;i<=n-2;i++)
		{
			for(int j=i+1;j<=n-1;j++)
			{
				if(f[i][j]<g)
				{
					f[i][j]++;
					a[t]=i;
					b[t]=j;
					bool re=false;
					for(int k=j+1;k<=n;k++)
					{
						if(f[i][k]<g&&f[j][k]<g)
						{
							f[i][k]++;f[j][k]++;
							c[t]=k;
							re=dfs(t+1);
							f[i][k]--;f[j][k]--;
							if(re)break;
						}
					}
					f[i][j]--;
					if(re)return true;
				}
			}
		}
		return false;
	}
}
int main()
{
	freopen("dish.in","r",stdin);
	//freopen("dish.out","w",stdout);
	while(scanf("%d",&n)!=EOF)
	{
		memset(f,0,sizeof(f));
		for(g=1;n*(n-1)/2*g/3<=n*n;g++)
		{
			if(n*(n-1)/2*g%3!=0)continue;
			//printf("%d\n",g);
			fflush(stdout);
			dfs(1);
		}
	}
	return 0;
}
