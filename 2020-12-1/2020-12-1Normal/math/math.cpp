#include<cstdio>
#include<cstring>
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
int p[3010000],s;
bool b[10010000];
int phi[10010000],mu[10010000];
void Euler(int n)
{
	memset(b,true,sizeof(b));s=0;
	phi[1]=mu[1]=1;b[1]=false;
	for(int i=2;i<=n;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=1;j<=s&&i*p[j]<=n;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				phi[i*p[j]]=phi[i]*p[j];
				mu[i*p[j]]=0;
				break;
			}
			else
			{
				phi[i*p[j]]=phi[i]*(p[j]-1);
				mu[i*p[j]]=-mu[i];
			}
		}
	}
}
long long f[10010000],F[10010000];
long long fc[10010000],phii[10010000];
int main()
{
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	int minn,maxx;
	if(n<m)minn=n,maxx=m;
	else minn=m,maxx=n;
	Euler(maxx);
	fc[1]=1;
	for(int i=2;i<=maxx;i++)fc[i]=(998244353-fc[998244353%i])*(998244353/i)%998244353;
	for(long long i=1;i<=maxx;i++)phii[i]=i*phi[i]%998244353;
	for(int d=1;d<=minn;d++)
	{
		long long r=0,i;
		for(i=d;i<=minn;i+=d)r=r+phii[i];
		F[d]=r%998244353;
		for(;i<=maxx;i+=d)r=r+phii[i];
		F[d]=r%998244353*F[d]%998244353;
	}
	for(int d=1;d<=minn;d++)
	{
		f[d]=0;
		for(int i=1;i*d<=minn;i++)f[d]=f[d]+F[i*d]*mu[i];
		f[d]=(f[d]%998244353+998244353)%998244353;
	}
	long long ss=1;
	for(int i=1;i<=minn;i++)
	{
		ss=(ss+ksm(i,n+1)*fc[phi[i]]%998244353*f[i])%998244353;
	}
	printf("%lld\n",ss*499122177%998244353);
	return 0;
}
