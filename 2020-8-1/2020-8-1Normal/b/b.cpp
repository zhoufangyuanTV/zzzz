#include<cstdio>
#include<cstring>
using namespace std;
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
long long jc[210000],fjc[210000];
long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
int p[110000],s;
bool b[110000];
long long low[110000],g[110000];
void Euler(int n,long long t)
{
	memset(b,true,sizeof(b));b[1]=false;low[1]=1;g[1]=1;s=0;
	for(int i=2;i<=n;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			for(long long j=i,k=1;j<=n;j=j*i,k++)low[j]=j,g[j]=C(k+t-1,t-1);
		}
		for(int j=1;j<=s&&i*p[j]<=n;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				low[i*p[j]]=low[i]*p[j];
				g[i*p[j]]=g[i/low[i]]*g[low[i]*p[j]]%1000000007;
				break;
			}
			else low[i*p[j]]=p[j],g[i*p[j]]=g[i]*t%1000000007;
		}
	}
}
long long f[110000],h[110000];
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	int tt;scanf("%d",&tt);
	while(tt--)
	{
		int n;long long t;scanf("%d%lld",&n,&t);
		jc[0]=1;
		for(int i=1;i<=n+t;i++)jc[i]=jc[i-1]*i%1000000007;
		fjc[n+t]=ksm(jc[n+t],1000000005);
		for(int i=n+t-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
		Euler(n,t);
		for(int i=1;i<=n;i++)scanf("%lld",&f[i]);
		memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)
		{
			for(int j=1;i*j<=n;j++)
			{
				h[i*j]=(h[i*j]+f[i]*g[j])%1000000007;
			}
		}
		for(int i=1;i<n;i++)printf("%lld ",h[i]);
		printf("%lld\n",h[n]);
	}
	return 0;
}