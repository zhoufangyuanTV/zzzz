#include<cstdio>
#include<cstring>
using namespace std;
inline long long ksm(long long x,long long k)
{
	register long long s=1;
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
int phi[10010000];
long long ncifang[10010000],nn;
void Euler(int n)
{
	memset(b,true,sizeof(b));s=0;
	phi[1]=ncifang[1]=1;b[1]=false;
	for(register int i=2;i<=n;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			phi[i]=i-1;
			ncifang[i]=ksm(i,nn+1);
		}
		for(register int j=1;j<=s&&i*p[j]<=n;j++)
		{
			b[i*p[j]]=false;
			ncifang[i*p[j]]=ncifang[i]*ncifang[p[j]]%998244353;
			if(i%p[j]==0)
			{
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}
long long fc[10010000];
long long f[10010000],g[10010000];
int main()
{
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	int m;scanf("%lld%d",&nn,&m);
	int minn,maxx;
	if(nn<m)minn=nn,maxx=m;
	else minn=m,maxx=nn;
	Euler(maxx);
	fc[1]=1;
	for(register int i=2;i<=maxx;i++)fc[i]=(998244353-fc[998244353%i])*(998244353/i)%998244353;
	for(register long long i=1;i<=maxx;i++)f[i]=g[i]=i*phi[i]%998244353;
	for(register int i=1;i<=s;i++)
	{
		for(register int j=minn/p[i];j>=1;j--)f[j]+=f[p[i]*j];
		for(register int j=maxx/p[i];j>=1;j--)g[j]+=g[p[i]*j];
	}
	for(register int d=1;d<=minn;d++)f[d]=f[d]%998244353*(g[d]%998244353)%998244353;
	for(register int i=1;i<=s;i++)
	{
		for(register int j=1;p[i]*j<=minn;j++)f[j]-=f[p[i]*j];
	}
	long long ss=1;
	for(register int i=1;i<=minn;i++)
	{
		ss=(ss+ncifang[i]*fc[phi[i]]%998244353*(f[i]%998244353+998244353))%998244353;
	}
	printf("%lld\n",ss*499122177%998244353);
	return 0;
}