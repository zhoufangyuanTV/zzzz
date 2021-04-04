#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		printf("%lld\n",(x*2+m)*499122177ll%998244353);
	}
	return 0;
}