#include<cstdio>
#include<cstring>
using namespace std;
int a[1010000];
long long cost(int l,int r)
{
	int ma=-999999999,mi=999999999;
	for(int i=l;i<=r;i++)
	{
		if(ma<a[i])ma=a[i];
		if(a[i]<mi)mi=a[i];
	}
	return 1ll*ma*mi;
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		long long ss=0;
		for(int L=l;L<=r;L++)
		for(int R=L;R<=r;R++)
		ss=(ss+cost(L,R))%1000000007;
	}
	printf("%lld\n",ss);
	return 0;
}
