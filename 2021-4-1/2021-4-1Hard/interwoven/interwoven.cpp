#include<cstdio>
#include<cstring>
using namespace std;
long long jc[1010000],fjc[1010000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
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
int n,K;
inline long long h(int p,int s)
{
	long long ss=0;
	for(int i=0;i<=p/s;i++)
	{
		ss=(ss+ksm(998244354-K,i)*ksm(K,p-i*s)%998244353*C(i+p-i*s,i))%998244353;
	}
	return ss;
}
inline long long f(int s)
{
	return (h(n,s)-h(n-s,s)+998244353)%998244353;
}
long long ful;
inline long long g(int s)
{
	return (ful-f(s)+998244353)%998244353;
}
int main()
{
	freopen("interwoven.in","r",stdin);
	freopen("interwoven.out","w",stdout);
	int x;scanf("%d%d%d",&n,&K,&x);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	long long ss=0;
	ful=ksm(K,n);
	for(int i=x+1;i<=n;i++)ss=(ss+g(i))%998244353;
	printf("%lld\n",ss);
	return 0;
}