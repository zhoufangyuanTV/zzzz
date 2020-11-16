#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	long long s=1;
	printf("{1");
	for(int i=1;i<=490000000;i++)
	{
		s=s*(2*i-1)%998244353;
		if(i%10000000==0)printf(",%lld",s);
	}
	printf("}\n");
	return 0;
}