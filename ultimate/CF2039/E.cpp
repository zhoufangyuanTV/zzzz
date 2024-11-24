#include<cstdio>
#include<cstring>
using namespace std;
long long f[1010000],g[1010000],gg[1010000];
int main()
{
	f[2]=g[2]=gg[2]=0;
	for(long long i=3;i<=1000000;i++)
	{
		f[i]=(i*(i-3)/2+f[i-1]*(i-1)+gg[i-1])%998244353;
		g[i]=(f[i-1]+g[i-1])%998244353;
		gg[i]=(f[i-1]*(i-1)+gg[i-1])%998244353;
	}
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		printf("%lld\n",(n-1+f[n]+g[n])%998244353);
	}
	return 0;
}