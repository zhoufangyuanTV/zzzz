#include<cstdio>
#include<cstring>
using namespace std;
int p;
long long ksm(long long x,long long k)
{
	x=x%p;
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("uno.in","r",stdin);
	freopen("uno.out","w",stdout);
	long long n;scanf("%lld%d",&n,&p);
	printf("%lld\n",((ksm(16,n)-3*ksm(7,n)-4*ksm(9,n)+12*ksm(6,n)-6*ksm(5,n)+4*(ksm(8,n)-3*ksm(5,n)+2*ksm(4,n))+6*(ksm(4,n)-ksm(3,n))+4*(ksm(2,n)-1)+1)%p+p)%p);
	return 0;
}