#include<cstdio>
#include<cstring>
using namespace std;
int a[210][11000];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int ic;
		if(i%(n*2)==0)ic=n*2;
		else ic=i%(n*2);
		for(int j=1;j<=n*2;j++)
		{
			if(ic+j-1<=n*2)a[ic+j-1][i]=(j-1)/2+1;
			else a[ic+j-1-n*2][i]=(j-1)/2+1;
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