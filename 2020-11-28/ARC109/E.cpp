#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("E.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		long long x;scanf("%lld",&x);
		long long a=x*262144%998244353;
		printf("%lld/262144\n",a);
	}
	return 0;
}