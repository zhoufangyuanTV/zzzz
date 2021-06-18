#include<cstdio>
#include<cstring>
using namespace std;
long long f[1048576],a[510],c[510][510];
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
int p[510],plen;
long long h[510];
int main()
{
	freopen("tournament.in","r",stdin);
	freopen("tournament.out","w",stdout);
	int n;scanf("%d",&n);
	bool bk=true;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		if(a[i]!=1)bk=false;
	}
	if(bk)
	{
		h[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(i&1)
			{
				long long ss=0;
				for(int j=1;j<=i/2;j++)
				{
					h[j]=h[j]*ksm(i-j*2+1,998244351)%998244353*(i-j*2)%998244353;
					if(j==1)ss=(ss+h[j])%998244353;
					else ss=(ss+h[j]*2)%998244353;
				}
				h[i/2+1]=(998244354-ss)*499122177%998244353;
			}
			else
			{
				long long ss=0;
				for(int j=1;j<i/2;j++)
				{
					h[j]=h[j+1]*ksm(i-j*2,998244351)%998244353*(i-j*2-1)%998244353;
					ss=(ss+h[j])%998244353;
				}
				h[i/2]=(1497366530-ss)%998244353;
			}
		}
		if(n&1)
		{
			for(int i=n/2+1;i>=1;i--)printf("%lld\n",h[i]);
			for(int i=2;i<=n/2+1;i++)printf("%lld\n",h[i]);
		}
		else
		{
			for(int i=n/2;i>=1;i--)printf("%lld\n",h[i]);
			for(int i=1;i<=n/2;i++)printf("%lld\n",h[i]);
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			long long g=ksm(a[i]+a[j],998244351);
			c[i][j]=a[i]*g%998244353;
			c[j][i]=a[j]*g%998244353;
		}
	}
	memset(f,0,sizeof(f));f[(1<<n)-1]=1;
	for(int i=(1<<n)-1;i>=1;i--)
	{
		plen=0;
		for(int j=1;j<=n;j++)if(i>>j-1&1)p[++plen]=j;
		if(plen>1)
		{
			long long g=f[i]*ksm(plen-1,998244351)%998244353;
			for(int j=1;j<plen;j++)
			{
				f[i^1<<p[j+1]-1]=(f[i^1<<p[j+1]-1]+g*c[p[j]][p[j+1]])%998244353;
				f[i^1<<p[j]-1]=(f[i^1<<p[j]-1]+g*c[p[j+1]][p[j]])%998244353;
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",f[1<<i-1]);
	return 0;
}
