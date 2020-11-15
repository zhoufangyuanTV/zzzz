#include<cstdio>
#include<cstring>
using namespace std;
int f[2100][2100],g[2100][2100],h[2100][2100],t[2100][2100];
char s[2100][2100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	t[1][1]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i==1&&j==1)continue;
			if(s[i][j]=='#')continue;
			f[i][j]=(f[i][j-1]+t[i][j-1])%1000000007;
			g[i][j]=(g[i-1][j]+t[i-1][j])%1000000007;
			h[i][j]=(h[i-1][j-1]+t[i-1][j-1])%1000000007;
			t[i][j]=((f[i][j]+g[i][j])%1000000007+h[i][j])%1000000007;
		}
	}
	printf("%d\n",t[n][m]);
	return 0;
}