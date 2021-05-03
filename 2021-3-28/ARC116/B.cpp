#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[210000];
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	long long ss=0,s=0;
	for(int i=1;i<=n;i++)s=(s+a[i]*ksm(2,n-i))%998244353;
	for(int i=n;i>=1;i--)
	{
		s=(s-a[i]+998244353)*499122177%998244353;
		ss=(ss+a[i]*(s+a[i]))%998244353;
	}
	printf("%lld\n",ss);
	return 0;
}