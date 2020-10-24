#include<cstdio>
#include<cstring>
using namespace std;
unsigned f[3100][3100][2];
int main()
{
	freopen("justice.in","r",stdin);
	freopen("justice.out","w",stdout);
	int n,m,k,x,y;scanf("%d%d%d%d%d",&n,&m,&k,&x,&y);
	if(x==y)
	{
		printf("1\n");
		return 0;
	}
	f[0][0][0]=1;
	int ss=0;
	for(int i=1;i<=(n+m-1)/(k-1);i++)
	{
		for(int j=0;j<=n;j++)
		{
			f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%1000000007;
			for(int l=1;l<=j&&l<k;l++)
			{
				f[i][j][1]=(f[i][j][1]+f[i-1][j-l][0]+f[i-1][j-l][1])%1000000007;
			}
			if(j%(k-1)==n%(k-1)&&j<=n&&i*(k-1)-j+1<=m)ss=(ss+f[i][j][1])%1000000007;
		}
	}
	printf("%d\n",ss);
	return 0;
}