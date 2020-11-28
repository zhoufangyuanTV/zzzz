#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int m,a[210000];
long long n,k,D;
long long s;
long long pand(long long x)
{
	long long ss=x*k+x*m,gg=x*s;
	for(int i=1;i<=m;i++)
	{
		if(gg==D)break;
		if(x==n)break;
		if(gg+(n-x)*a[i]<D)
		{
			ss=ss+n-x;
			gg=gg+(n-x)*a[i];
		}
		else
		{
			long long C=(D-gg)/a[i];
			ss=ss+C;
			break;
		}
	}
	return ss;
}
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%d%lld%lld",&n,&m,&k,&D);
		s=0;
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&a[i]);
			s=s+a[i];
		}
		sort(a+1,a+m+1);
		long long l=0,r=D/s,ss=0;
		if(n<r)r=n;
		while(r-l>3)
		{
			long long lmid=(l*2+r)/3,rmid=(l+r*2)/3;
			long long ls=pand(lmid),rs=pand(rmid);
			if(ls>ss)ss=ls;
			if(rs>ss)ss=rs;
			if(ls<rs)l=lmid;
			else r=rmid;
		}
		for(long long i=l;i<=r;i++)
		{
			long long si=pand(i);
			if(si>ss)ss=si;
		}
		printf("%lld\n",ss);
	}
	return 0;
}