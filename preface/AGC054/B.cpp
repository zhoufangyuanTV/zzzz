#include<cstdio>
#include<cstring>
using namespace std;
long long f[110][21000],g[110][21000],c[110];
int a[110];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	c[1]=1;
	for(int i=2;i<=n;i++)c[i]=(998244353-c[998244353%i])*(998244353/i)%998244353;
	f[0][10000]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++)
		{
			for(int k=0;k<=20000;k++)
			{
				g[j][k]=f[j][k];
				f[j][k]=0;
			}
		}
		for(int j=0;j<i;j++)
		{
			for(int k=0;k<=20000;k++)
			{
				if(g[j][k]>0)
				{
					if(k>=a[i])
					{
						f[j][k-a[i]]=(f[j][k-a[i]]+g[j][k]*(i-j))%998244353;
					}
					if(k+a[i]<=20000)
					{
						f[j+1][k+a[i]]=(f[j+1][k+a[i]]+g[j][k]*(j+1))%998244353;
					}
				}
			}
		}
	}
	long long ss=0;
	for(int i=0;i<=n;i++)
	{
		ss+=f[i][10000];
	}
	printf("%lld\n",ss%998244353);
	return 0;
}