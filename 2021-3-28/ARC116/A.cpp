#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		long long n;scanf("%lld",&n);
		if(n%2==1)puts("Odd");
		else if(n%4!=0)puts("Same");
		else puts("Even");
	}
	return 0;
}