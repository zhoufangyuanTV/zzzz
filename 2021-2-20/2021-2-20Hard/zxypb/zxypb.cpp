#include<cstdio>
#include<cstring>
using namespace std;
long long jc[510000],fjc[510000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
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
long long f[510000],g[510000];
int main()
{
	freopen("zxypb.in","r",stdin);
	freopen("zxypb.out","w",stdout);
	int n;scanf("%d",&n);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	memset(f,0,sizeof(f));f[0]=f[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i;j++)f[i]=(f[i]+f[j-1]*f[i-j]%998244353*C(i-1,j-1))%998244353;
		f[i]=f[i]*499122177%998244353;
	}
	for(int i=1;i<=n;i++)g[i]=f[i-1]*(n-i+1)%998244353*jc[n-i]%998244353*C(n-1,i-1)%998244353;
	g[n+1]=0;
	long long ss=0;
	for(int i=1;i<=n;i++)ss=(ss+(g[i]-g[i+1]+998244353)*i)%998244353;
	printf("%lld\n",ss*fjc[n]%998244353);
	return 0;
}