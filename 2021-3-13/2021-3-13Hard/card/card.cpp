#include<cstdio>
#include<cstring>
using namespace std;
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
long long d[10010000];
int main()
{
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	long long n,p,c;scanf("%lld%lld%lld",&n,&p,&c);
	long long C=(ksm(998244354-p,c)+998244352)*ksm(998244353-p,998244351)%998244353;
	long long ss=1;d[1]=1;
	for(long long i=2;i<=n;i++)
	{
		d[i]=d[998244353%i]*(998244353-998244353/i)%998244353;
		ss=(ss+d[i])%998244353;
	}
	printf("%lld\n",C*n%998244353*ss%998244353);
	return 0;
}
