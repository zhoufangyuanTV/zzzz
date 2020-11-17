#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[310000];
int main()
{
	freopen("cuvelia.in","r",stdin);
	freopen("cuvelia.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	long long ss=0,s=0;
	for(int i=1;i<=n;i++)
	{
		if(i%2==0)s=s+a[n-i/2+1]-a[i/2];
		ss=ss+s;
		printf("%lld\n",ss);
	}
	return 0;
}