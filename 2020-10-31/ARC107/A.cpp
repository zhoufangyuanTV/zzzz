#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	long long a,b,c;scanf("%lld%lld%lld",&a,&b,&c);
	a=a*(a+1)/2%998244353;
	b=b*(b+1)/2%998244353;
	c=c*(c+1)/2%998244353;
	printf("%lld\n",a*b%998244353*c%998244353);
	return 0;
}