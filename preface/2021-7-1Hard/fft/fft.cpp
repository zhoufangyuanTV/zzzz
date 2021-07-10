#include<cstdio>
#include<cstring>
using namespace std;
long long jc[1010000],fjc[1010000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
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
long long f[1100][1100],g[1100][1100];
inline long long plus(long long x,long long y){return x+y<998244353?x+y:x+y-998244353;}
int main()
{
	freopen("fft.in","r",stdin);
	freopen("fft.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	jc[0]=1;
	for(int i=1;i<=n+m;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n+m]=ksm(jc[n+m],998244351);
	for(int i=n+m-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	memset(f,0,sizeof(f));
	for(int i=0;i<=n;i++)f[i][0]=0,g[i][0]=1;
	for(int i=0;i<=m;i++)f[0][i]=0,g[0][i]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			g[i][j]=plus(g[i-1][j],g[i][j-1]);
			f[i][j]=plus(f[i-1][j],f[i][j-1]);
			if(i<j)f[i][j]=plus(f[i][j],g[i-1][j]);
			else f[i][j]=plus(f[i][j],g[i][j-1]);
		}
	}
	printf("%lld\n",f[n][m]/**ksm(C(n+m,n),998244351)%998244353*/);
	return 0;
}
