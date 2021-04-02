#include<cstdio>
#include<cstring>
using namespace std;
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
long long f[2100][2100],g[2100][2100],h[2100][2100];
int main()
{
	freopen("interwoven.in","r",stdin);
	freopen("interwoven.out","w",stdout);
	int n,m,x;scanf("%d%d%d",&n,&m,&x);
	if(m==2&&x>n/2)
	{
		long long ss=0;
		for(int i=x+1;i<n;i++)
		{
			long long s=((n-i-1)*ksm(2,n-i-2)+2*ksm(2,n-i-1))%998244353;
			ss=(ss+s*(i-x))%998244353;
		}
		ss=(ss+n-x)*2%998244353;
		printf("%lld\n",ss);
		return 0;
	}
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++)
	{
		f[i][i]=m;
		for(int j=1;j<i;j++)
		{
			f[i][i-j]=(f[i][i-j]+(m-1)*g[j][i-j])%998244353;
			f[i][j]=(f[i][j]+(m-1)*(h[i-1][j]-h[i-j][j]+998244353))%998244353;
		}
		for(int j=1;j<=n;j++)
		{
			g[i][j]=(f[i][j]+g[i][j-1])%998244353;
			h[i][j]=(f[i][j]+h[i-1][j])%998244353;
		}
	}
	long long ss=0;
	for(int i=x+1;i<=n;i++)ss=(ss+(i-x)*f[n][i])%998244353;
	printf("%lld\n",ss);
	return 0;
}