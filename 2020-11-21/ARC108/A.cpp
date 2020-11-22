#include<cstdio>
using namespace std;
int main()
{
	long long a,b;scanf("%lld%lld",&a,&b);
	for(long long i=1;i*i<=b;i++)
	{
		if(b%i==0)
		{
			long long j=b/i;
			if(i+j==a)
			{
				printf("Yes\n");
				return 0;
			}
		}
	}
	printf("No\n");
	return 0;
}