#include<cstdio>
#include<cstring>
using namespace std;
double f[110][110][110];
int main()
{
	int a,b,c;scanf("%d%d%d",&a,&b,&c);
	for(int i=100;i>=0;i--)
	{
		for(int j=100;j>=0;j--)
		{
			for(int k=100;k>=0;k--)
			{
				if(i==100||j==100||k==100)
				{
					f[i][j][k]=0;
					continue;
				}
				if(i+j+k==0)break;
				f[i][j][k]=f[i+1][j][k]*i/(i+j+k);
				f[i][j][k]+=f[i][j+1][k]*j/(i+j+k);
				f[i][j][k]+=f[i][j][k+1]*k/(i+j+k);
				f[i][j][k]+=1;
			}
		}
	}
	printf("%.6lf\n",f[a][b][c]);
	return 0;
}