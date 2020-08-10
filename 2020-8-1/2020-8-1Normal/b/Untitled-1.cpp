#include<cstdio>
#include<cstring>
using namespace std;
int f[110][110];
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	memset(f,0,sizeof(f));f[1][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			for(int l=1;l<=i;l++)if(i%l==0)f[i][j]+=f[l][j-1];
		}
	}
	for(int i=1;i<=n;i++)printf("%d\n",f[i][k]);
	return 0;
}