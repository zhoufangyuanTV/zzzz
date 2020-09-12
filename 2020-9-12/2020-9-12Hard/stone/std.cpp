#include<cstdio>
#include<cstring>
using namespace std;
bool f[11][11][11][11][11][2];
int main()
{
	freopen("stone.in","r",stdin);
	freopen("stone.ans","w",stdout);
	int n,a,b,c1=0,c2=0,c3=0,c4=0,c5=0;scanf("%d%d%d",&n,&a,&b);
	if(1<=n)scanf("%d",&c1);
	if(2<=n)scanf("%d",&c2);
	if(3<=n)scanf("%d",&c3);
	if(4<=n)scanf("%d",&c4);
	if(5<=n)scanf("%d",&c5);
	memset(f,false,sizeof(f));
	int Alice=0,Bob=0,first=0,second=0;
	for(int i=0;i<=c1;i++)
	{
		for(int j=0;j<=c2;j++)
		{
			for(int k=0;k<=c3;k++)
			{
				for(int l=0;l<=c4;l++)
				{
					for(int m=0;m<=c5;m++)
					{
						if(a<=i&&!f[i-a][j][k][l][m][1])f[i][j][k][l][m][0]=true;
						if(a<=j&&!f[i][j-a][k][l][m][1])f[i][j][k][l][m][0]=true;
						if(a<=k&&!f[i][j][k-a][l][m][1])f[i][j][k][l][m][0]=true;
						if(a<=l&&!f[i][j][k][l-a][m][1])f[i][j][k][l][m][0]=true;
						if(a<=m&&!f[i][j][k][l][m-a][1])f[i][j][k][l][m][0]=true;
						if(b<=i&&!f[i-b][j][k][l][m][0])f[i][j][k][l][m][1]=true;
						if(b<=j&&!f[i][j-b][k][l][m][0])f[i][j][k][l][m][1]=true;
						if(b<=k&&!f[i][j][k-b][l][m][0])f[i][j][k][l][m][1]=true;
						if(b<=l&&!f[i][j][k][l-b][m][0])f[i][j][k][l][m][1]=true;
						if(b<=m&&!f[i][j][k][l][m-b][0])f[i][j][k][l][m][1]=true;
						if((i==0||i==c1)&&(j==0||j==c2)&&(k==0||k==c3)&&(l==0||l==c4)&&(m==0||m==c5))
						{
							if(f[i][j][k][l][m][0]&&!f[i][j][k][l][m][1])Alice++;
							if(!f[i][j][k][l][m][0]&&f[i][j][k][l][m][1])Bob++;
							if(f[i][j][k][l][m][0]&&f[i][j][k][l][m][1])first++;
							if(!f[i][j][k][l][m][0]&&!f[i][j][k][l][m][1])second++;
						}
					}
				}
			}
		}
	}
	printf("%d %d %d %d\n",Alice,Bob,first,second);
	return 0;
}