#include<cstdio>
#include<cstring>
using namespace std;
long long jc[1010000],fjc[1010000];
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
inline long long C(long long n,long long m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
int main()
{
	freopen("derivative.in","r",stdin);
	freopen("derivative.out","w",stdout);
	long long n,k,a,b;scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
	if(n*k<=1000000)
	{
		jc[0]=1;
		for(int i=1;i<=1000000;i++)jc[i]=jc[i-1]*i%998244353;
		fjc[1000000]=ksm(jc[1000000],998244351);
		for(int i=999999;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
		a=a*ksm(b,k)%998244353;
		b=1;
		long long ss=0;
		for(int i=0;i<=n;i++,b=b*a%998244353)ss=(ss+b*C(n*k,i*k))%998244353;
		printf("%lld\n",ss);
		return 0;
	}
	if(k==1)
	{
		printf("%lld\n",ksm((a*b+1)%998244353,n));
		return 0;
	}
	return 0;
}