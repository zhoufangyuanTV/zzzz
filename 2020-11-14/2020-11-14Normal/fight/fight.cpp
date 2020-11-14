#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110];
int main()
{
	freopen("fight.in","r",stdin);
	freopen("fight.out","w",stdout);
	int n,k;scanf("%d%d",&n,&k);
	if(k==1&&n!=2)
	{
		printf("%lld\n",1ll*(n-2+998244353)*6%998244353);
		return 0;
	}
	for(int i=1;i<=n;i++)a[i]=i;
	int ss=0;
	do
	{
		int s=0;
		for(int i=1;i<n;i++)
		{
			if(a[i]+1!=a[i+1]&&a[i]-1!=a[i+1])s++;
		}
		if(s<=k)ss++;
	}while(next_permutation(a+1,a+n+1));
	printf("%d\n",ss);
	return 0;
}