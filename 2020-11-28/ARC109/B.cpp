#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	long long n;scanf("%lld",&n);
	long long a=sqrt(n*2+2);
	long long l=a-2,r=a+2;
	if(l<1)l=1;
	if(r>n)r=n;
	for(long long i=r;i>=l;i--)
	{
		if(i*(i+1)/2<=n+1)
		{
			printf("%lld\n",n-i+1);
			return 0;
		}
	}
	return 0;
}