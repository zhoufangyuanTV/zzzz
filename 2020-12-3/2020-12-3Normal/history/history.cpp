#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void read(long long &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
long long a[2010000];
long long f[510][510];
long long g[2010000];
long long fc[2010000];
int main()
{
	freopen("history.in","r",stdin);
	freopen("history.out","w",stdout);
	int n;read(n);a[0]=0;
	bool bk=true;
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		if(a[i]!=1)bk=false;
		a[i]=(a[i]+a[i-1])%998244353;
	}
	fc[1]=1;
	for(int i=2;i<=n;i++)fc[i]=(998244353-fc[998244353%i])*(998244353/i)%998244353;
	if(bk)
	{
		long long ss=0,v=0;
		for(int i=1;i<n;i++)
		{
			if(i&1)v=(v+fc[i])%998244353;
			ss=(ss+v)%998244353;
		}
		printf("%lld\n",ss);/*
		g[1]=0;
		for(int i=2;i<=n;i++)
		{
			g[i]=0;
			for(int j=1;j<=i/2;j++)g[i]=(g[i]+fc[i-1]*(g[j]+g[i-j]+a[j]))%998244353;
			for(int j=i/2+1;j<i;j++)g[i]=(g[i]+fc[i-1]*(g[j]+g[i-j]+a[i]-a[j]))%998244353;
		}
		printf("%lld\n",g[n]);*/
		return 0;
	}
	for(int i=1;i<=n;i++)f[i][i]=0;
	for(int j=2;j<=n;j++)
	{
		for(int i=j-1;i>=1;i--)
		{
			f[i][j]=0;
			for(int k=i;k<j;k++)
			{
				long long s;
				if((k-i+1)<=(j-k))s=a[k]-a[i-1]+998244353;
				else s=a[j]-a[k]+998244353;
				f[i][j]=(f[i][j]+fc[j-i]*(f[i][k]+f[k+1][j]+s))%998244353;
			}
		}
	}
	printf("%lld\n",f[1][n]);
	return 0;
}
