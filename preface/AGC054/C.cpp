#include<cstdio>
#include<cstring>
using namespace std;
int a[5100];
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	long long ss=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		int s=0;
		for(int j=1;j<i;j++)if(a[j]>a[i])s++;
		if(s==k)
		{
			ss=ss*(n-i+1)%998244353;
		}
	}
	printf("%lld\n",ss);
	return 0;
}