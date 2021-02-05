#include<cstdio>
#include<cstring>
using namespace std;
long long p;
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
long long _[4010000];
long long jc[2100],fjc[2100];
long long f[2100],g[2100];
int main()
{
	int t;scanf("%d%lld",&t,&p);
	jc[0]=1;fjc[0]=1;
	for(int i=1;i<=2000;i++)
	{
		jc[i]=jc[i-1]*i%p;
		fjc[i]=ksm(jc[i],p-2);
	}
	_[0]=1;
	for(int i=1;i<=4000000;i++)_[i]=_[i-1]*2%p;
	for(int i=0;i<=2000;i++)
	{
		g[i]=0;
		for(int j=0;j<=i;j++)
		{
			g[i]=(g[i]+_[j*(i-j)]*jc[i]%p*fjc[j]%p*fjc[i-j])%p;
		}
	}
	for(int i=0;i<=2000;i++)
	{
		f[i]=0;
		for(int j=0;j<=i;j++)
		{
			f[i]=(f[i]+g[j]*_[j*(i-j)]%p*jc[i]%p*fjc[j]%p*fjc[i-j])%p;
		}
	}
	while(t--)
	{
		int n;scanf("%d",&n);
		printf("%lld\n",f[n]);
	}
	return 0;
}