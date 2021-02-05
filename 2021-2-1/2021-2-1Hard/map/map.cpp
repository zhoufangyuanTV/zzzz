#include<cstdio>
#include<cstring>
using namespace std;
int a[110000],b[110000];
long long f[1100][1024],g[1024],h[1024];
inline int mymin(int x,int y){return x<y?x:y;}
long long ksm(long long x,long long k)
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
long long w[110000],jc[110000],fjc[110000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
int main()
{
	freopen("map.in","r",stdin);
	freopen("map.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
	int A=0,B=0;
	for(int i=1;i<=n;i++)if(A<a[i])A=a[i];
	for(int i=1;i<=m;i++)if(B<b[i])B=b[i];
	if(A!=B)
	{
		puts("0");
		return 0;
	}
	if(n<=10)
	{
		for(int i=0;i<1<<n;i++)
		{
			g[i]=1;
			for(int j=1;j<=n;j++)if((i|1<<j-1)==i)g[i]=g[i]*a[j]%998244353;
			g[i]=ksm(g[i],998244351);
		}
		memset(f,0,sizeof(f));f[0][0]=1;
		for(int i=1;i<=m;i++)
		{
			int x=0;
			for(int j=1;j<=n;j++)if(a[j]<=b[i])x|=1<<j-1;
			for(int j=0;j<1<<n;j++)
			{
				h[j]=1;
				for(int k=1;k<=n;k++)
				{
					if((j|1<<k-1)==j)h[j]=h[j]*mymin(a[k],b[i])%998244353;
					else h[j]=h[j]*mymin(a[k]-1,b[i])%998244353;
				}
			}
			for(int j=0;j<1<<n;j++)
			{
				for(int k=j&x;k>0;k=k-1&j&x)
				{
					f[i][j]=(f[i][j]+f[i-1][j^k]*g[k]%998244353*h[j])%998244353;
				}
				f[i][j]=(f[i][j]+f[i-1][j]*h[j])%998244353;
			}
			x=0;
			for(int j=1;j<=n;j++)if(a[j]<=b[i]-1)x|=1<<j-1;
			for(int j=0;j<1<<n;j++)
			{
				h[j]=1;
				for(int k=1;k<=n;k++)
				{
					if((j|1<<k-1)==j)h[j]=h[j]*mymin(a[k],b[i]-1)%998244353;
					else h[j]=h[j]*mymin(a[k]-1,b[i]-1)%998244353;
				}
			}
			for(int j=0;j<1<<n;j++)
			{
				for(int k=j&x;k>0;k=k-1&j&x)
				{
					f[i][j]=(f[i][j]-f[i-1][j^k]*g[k]%998244353*h[j]%998244353+998244353)%998244353;
				}
				f[i][j]=(f[i][j]-f[i-1][j]*h[j]%998244353+998244353)%998244353;
			}
		}
		printf("%lld\n",f[m][(1<<n)-1]);
		return 0;
	}
	if(A<=2&&B<=2)
	{
		A=0;B=0;
		for(int i=1;i<=n;i++)if(a[i]==2)A++;
		for(int i=1;i<=m;i++)if(b[i]==2)B++;
		n=A;m=B;
		for(int i=0;i<=n;i++)w[i]=ksm(ksm(2,i)+998244352,m);
		jc[0]=1;
		for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
		fjc[n]=ksm(jc[n],998244351);
		for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
		long long ss=0;
		for(int i=0;i<=n;i++)
		{
			if((n-i)%2==0)ss=(ss+C(n,i)*w[i])%998244353;
			else ss=(ss-C(n,i)*w[i]%998244353+998244353)%998244353;
		}
		printf("%lld\n",ss);
	}
	return 0;
}