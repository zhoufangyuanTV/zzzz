#include<cstdio>
#include<cstring>
using namespace std;
long long a[110000],c[110000];
int main()
{
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,w;scanf("%d%d",&n,&w);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)c[i]=1ll<<w;
		long long ss=(1ll<<w)-1;
		for(int i=w-1;i>=0;i--)
		{
			long long s=0;
			ss-=1ll<<i;
			for(int j=1;j<=n;j++)
			{
				long long A=a[j],C=c[j];
				while((A&ss)!=A)A>>=1,C>>=1;
				s+=C;
				if(1ll<<w<=s)s=1ll<<w;
			}
			if(s<1ll<<w)ss+=1ll<<i;
			else
			{
				for(int j=1;j<=n;j++)
				{
					while((a[j]&ss)!=a[j])a[j]>>=1,c[j]>>=1;
				}
			}
		}
		printf("%lld\n",ss);
	}
	return 0;
}
