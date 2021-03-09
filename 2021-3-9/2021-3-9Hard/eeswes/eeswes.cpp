#include<cstdio>
#include<cstring>
using namespace std;
bool b[6010000];
int f[6010000],g[6010000];
int low[6010000],mu[6010000],phi[6010000],d[6010000];
int p[1010000],s;
inline void plus(int &x,int y){x+y<998244353?x+=y:x+=y-998244353;}
int main()
{
	freopen("eeswes.in","r",stdin);
	freopen("eeswes.out","w",stdout);
	int n;scanf("%d",&n);
	memset(b,true,sizeof(b));s=0;
	b[1]=false;low[1]=mu[1]=phi[1]=d[1]=1;
	for(int i=2;i<=n*n;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			low[i]=i;
			mu[i]=-1;
			phi[i]=i-1;
			d[i]=2;
		}
		for(int j=1;j<=s&&i*p[j]<=n*n;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				low[i*p[j]]=low[i]*p[j];
				mu[i*p[j]]=0;
				phi[i*p[j]]=phi[i]*p[j];
				d[i*p[j]]=d[i/low[i]]*(d[low[i]]+1);
				break;
			}
			else
			{
				low[i*p[j]]=p[j];
				mu[i*p[j]]=-mu[i];
				phi[i*p[j]]=phi[i]*(p[j]-1);
				d[i*p[j]]=d[i]*2;
			}
		}
	}
	int ss=0;
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=n;i++)
		{
			f[i]=mu[i]*phi[i*j];
			if(f[i]<0)f[i]+=998244353;
		}
		for(int k=1;k<=n;k++)
		{
			g[k]=mu[k]*d[j*k];
			if(g[k]<0)g[k]+=998244353;
		}
		for(int t=1;t<=s&&p[t]<=n;t++)
		{
			for(int tt=n/p[t];tt>=1;tt--)
			{
				plus(f[tt],f[p[t]*tt]);
				plus(g[tt],g[p[t]*tt]);
			}
		}
		long long s=0;
		for(int t=1;t<=n;t++)s=(s+1ll*f[t]*g[t]%998244353*mu[t]+998244353)%998244353;
		plus(ss,int(s));
	}
	printf("%d\n",ss);
	return 0;
}