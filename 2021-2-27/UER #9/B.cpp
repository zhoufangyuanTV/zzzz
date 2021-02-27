#include<cstdio>
#include<cstring>
using namespace std;
int f[510][510];
int p[3100],cnt[3100];
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=2*k;
	for(int i=1;i<=n;i++)f[i][i]=0;
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		f[x][y]=1;f[y][x]=1;
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(p[i]==p[j])f[i][j]=f[j][i]=1;
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)f[i][j]=mymin(f[i][j],f[i][k]+f[k][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)cnt[f[i][j]]++;
	}
	for(int i=1;i<=2*k;i++)printf("%d ",cnt[i-1]);
	printf("%d\n",cnt[2*k]);
	return 0;
}