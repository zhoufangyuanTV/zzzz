#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
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
long long a[210000],b[210000],pa[210000],pb[210000];
inline long long mymin(long long x,long long y){return x<y?x:y;}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++)pa[i]=a[i],pb[i]=b[i];
		sort(pa+1,pa+n+1);
		sort(pb+1,pb+n+1);
		long long ss=1;
		for(int i=1;i<=n;i++)ss=ss*mymin(pa[i],pb[i])%998244353;
		printf("%lld",ss);
		for(int i=1;i<=m;i++)
		{
			int o,x;scanf("%d%d",&o,&x);
			if(o==1)
			{
				int l=1,r=n;
				while(l<r)
				{
					int mid=(l+r+1)/2;
					if(pa[mid]<=a[x])l=mid;
					else r=mid-1;
				}
				ss=ss*ksm(mymin(pa[l],pb[l]),998244351)%998244353;
				pa[l]++;a[x]++;
				ss=ss*mymin(pa[l],pb[l])%998244353;
			}
			else
			{
				int l=1,r=n;
				while(l<r)
				{
					int mid=(l+r+1)/2;
					if(pb[mid]<=b[x])l=mid;
					else r=mid-1;
				}
				ss=ss*ksm(mymin(pa[l],pb[l]),998244351)%998244353;
				pb[l]++;b[x]++;
				ss=ss*mymin(pa[l],pb[l])%998244353;
			}
			printf(" %lld",ss);
		}
		putchar('\n');
	}
	return 0;
}