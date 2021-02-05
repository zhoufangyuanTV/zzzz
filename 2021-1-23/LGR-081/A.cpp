#include<cstdio>
#include<cstring>
using namespace std;
int a[110000];
inline long long mymin(long long x,long long y){return x<y?x:y;}
int main()
{
	int n;long long A,B,s;
	scanf("%d%lld%lld%lld",&n,&A,&B,&s);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	long long ss=0x3f3f3f3f3f3f3f3fll;
	for(long long i=0;1ll<<i-1ll<=s;i++)
	{
		long long sr=s>>i;
		if(s%(1ll<<i)!=0)sr++;
		long long l=0,r=2000000001;
		while(l<r)
		{
			int mid=(l+r)/2;
			long long bk=false;
			long long sss=0;
			for(int j=1;j<=n;j++)
			{
				if(sss<0)sss=0;
				sss=sss+a[j]+mid;
				if(sr<=sss){bk=true;break;}
			}
			if(bk)r=mid;
			else l=mid+1;
		}
		ss=mymin(ss,A*r+B*i);
	}
	printf("%lld\n",ss);
	return 0;
}