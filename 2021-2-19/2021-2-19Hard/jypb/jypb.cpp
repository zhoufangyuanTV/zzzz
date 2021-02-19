#include<cstdio>
#include<cstring>
using namespace std;
inline long long ksm(long long x,long long k)
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
long long gcd(long long x,long long y){return y==0?x:gcd(y,x%y);}
inline long long plus(long long x,long long y){return x+y<998244353?x+y:x+y-998244353;}
long long f(long long x,long long y)
{
	if(x==1)return ksm(2,y-1);
	if(y==1)return plus(ksm(2,x),998244352);
	if(x<y)return f(x,y%x)*ksm(2,y/x)%998244353;
	return ((f(x%y,y)+1)*ksm(2,x/y)+998244352)%998244353;
}
int main()
{
	freopen("jypb.in","r",stdin);
	freopen("jypb.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		long long x,y;scanf("%lld%lld",&x,&y);
		long long z=gcd(x,y);x/=z;y/=z;
		printf("%lld\n",f(x,y));
	}
	return 0;
}