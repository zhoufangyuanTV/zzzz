#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n,t;scanf("%d%d",&n,&t);
	long long v=100ll*t;
	long long s=v/n;
	if(v%n!=0)s++;
	printf("%lld\n",s+t-1);
	return 0;
}