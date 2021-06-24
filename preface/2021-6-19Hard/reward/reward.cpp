#include<cstdio>
#include<cstring>
using namespace std;
long long f[2010000];
int g[2010000],a[2010000];
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline long long mymin(long long x,long long y){return x<y?x:y;}
int main()
{
	freopen("reward.in","r",stdin);
	freopen("reward.out","w",stdout);
	int n,m,k;read(n);read(m);read(k);
	for(int i=1;i<=n;i++)read(a[i]);
	long long l=-1000000000,r=1000000000;
	long long ss=0x3f3f3f3f3f3f3f3fll;
	while(l<=r)
	{
		long long mid=(l+r)/2;
		f[0]=g[0]=0;
		for(int i=1;i<=n;i++)
		{
			f[i]=f[i-1];g[i]=g[i-1];
			if(i<m)
			{
				if(f[i]<a[i]-mid)
				{
					f[i]=a[i]-mid;g[i]=1;
				}
			}
			else
			{
				if(f[i]<f[i-m]+a[i]-mid)
				{
					f[i]=f[i-m]+a[i]-mid;g[i]=g[i-m]+1;
				}
			}
		}
		ss=mymin(ss,f[n]+mid*k);
		if(g[n]==k)break;
		else if(g[n]<k)r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ss);
	return 0;
}