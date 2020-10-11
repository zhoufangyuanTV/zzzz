#include<cstdio>
#include<cstring>
using namespace std;
inline long long ksm(long long x,long long k,long long p)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
long long jc[1100],fjc[1100];
long long f[1100],g[1100],gg[1100],eG[1100],h[1100];
int main()
{
	freopen("xxx.in","r",stdin);
	freopen("xxx.out","w",stdout);
	int n,k;scanf("%d%d",&n,&k);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%100000007;
	fjc[n]=ksm(jc[n],100000005,100000007);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%100000007;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			f[i]=(f[i]+((i-j)&1?-1:1)*ksm(2,ksm(2,j,100000006)+100000005,100000007)*fjc[j]%100000007*fjc[i-j]%100000007+100000007)%100000007;
		}
	}
	eG[0]=1;
	for(int i=1;i<=n;i++)
	{
		g[i]=(f[i]-eG[i]+100000007)%100000007;
		for(int j=n;j>=0;j--)
		{
			for(long long jj=i,GG=g[i];j+jj<=n;jj+=i,GG=GG*g[i]%100000007)
			{
				eG[j+jj]=(eG[j+jj]+eG[j]*GG%100000007*fjc[jj/i]%100000007)%100000007;
			}
		}
	}
	h[0]=1;
	for(int i=1;i<=k;i<<=1)
	{
		if(k&i)
		{
			for(int j=n;j>=0;j--)
			{
				for(int jj=i;jj+j<=n;jj++)
				{
					h[j+jj]=(h[j+jj]+h[j]*g[jj])%100000007;
				}
				h[j]=0;
			}
		}
		for(int j=0;j<=n;j++)gg[j]=0;
		for(int j=i;j<=n;j++)
		{
			for(int jj=i;j+jj<=n;jj++)
			{
				gg[j+jj]=(gg[j+jj]+g[j]*g[jj])%100000007;
			}
		}
		for(int j=0;j<=n;j++)g[j]=gg[j];
	}
	for(int i=k;i<=n;i++)h[i]=h[i]*fjc[k]%100000007;
	long long ss=0;
	for(int i=k;i<=n;i++)ss=(ss+h[i]*jc[n]%100000007*fjc[n-i])%100000007;
	printf("%lld\n",ss);
	return 0;
}