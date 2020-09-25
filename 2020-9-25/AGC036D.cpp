#include<cstdio>
#include<cstring>
using namespace std;
long long f[510][510],a[510][510],b[510][510];
inline long long mymin(long long x,long long y){return x<y?x:y;}
inline long long CVN(int ll,int lr,int rl,int rr){return a[lr][rr]-a[ll-1][rr]-a[lr][rl-1]+a[ll-1][rl-1];}
int main()
{
	int n;scanf("%d",&n);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;
			int c;scanf("%d",&c);
			a[i][j]=a[i-1][j]+a[i][j-1]+c-a[i-1][j-1];
		}
	}
	for(int j=2;j<=n;j++)
	{
		for(int i=1;i<j;i++)b[i][j]=b[i][j-1]+CVN(i,j-1,j,j);
	}
	memset(f,63,sizeof(f));f[0][1]=0;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			for(int k=j+1;k<=n+1;k++)
			{
				f[j][k]=mymin(f[j][k],f[i][j]+b[j][k-1]+CVN(k,n,i,j-1));
			}
		}
	}
	long long ss=0x3f3f3f3f3f3f3f3fll;
	for(int i=1;i<=n;i++)if(f[i][n+1]<ss)ss=f[i][n+1];
	printf("%lld\n",ss);
	return 0;
}