#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
bitset<110> map[110],mmp[110];
int f[110][110],g[110][110];
char s[110];
int main()
{
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)if(s[j]=='*')map[i][j]=1;
	}
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i==1&&j==1)continue;
			for(int l=1;l<=n;l++)mmp[l]=map[l];
			for(int x=i,y=j;x<=n&&y<=m;x+=i-1,y+=j-1)
			{
				for(int l=1;x+l-1<=n;l++)mmp[l]|=map[x+l-1]>>(y-1);
			}
			memset(f,0,sizeof(f));f[1][1]=1;
			for(int kk=1;kk<=k;kk++)
			{
				for(int x=1;x<=n;x++)
				{
					for(int y=1;y<=m;y++)
					{
						if(!mmp[x][y])g[x][y]=(f[x-1][y]+f[x][y-1]+f[x+1][y]+f[x][y+1])%100000007;
					}
				}
				for(int x=1;x<=n;x++)
				{
					for(int y=1;y<=m;y++)
					{
						f[x][y]=g[x][y];
					}
				}
				ss=(ss+f[i][j])%100000007;
			}
		}
	}
	printf("%d\n",ss);
	return 0;
}