#include<cstdio>
#include<cstring>
using namespace std;
long long a[20010000],b[20010000];
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
	freopen("table.out","w",stdout);
	printf("{0");
	long long ss=0;
	for(long long i=20000000;i<998244353;i+=20000000)
	{
		a[0]=1;
		for(long long j=1;j<=20000000;j++)a[j]=a[j-1]*(i-20000000+j)%998244353;
		b[20000000]=ksm(a[20000000],998244351);
		for(long long j=19999999;j>=1;j--)b[j]=b[j+1]*(i-19999999+j)%998244353;
		for(long long j=1;j<=20000000;j++)ss=(ss+a[j-1]*b[j])%998244353;
		printf(",%lld",ss);
	}
	putchar('}');
	return 0;
}