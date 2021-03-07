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
void work(int);
int main()
{
	freopen("zxypb.in","r",stdin);
	freopen("zxypb.out","w",stdout);
	int n;scanf("%d",&n);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	work(n);
	for(int i=1;i<=n;i++)g[i]=f[i-1]*(n-i+1)%998244353*jc[n-i]%998244353*C(n-1,i-1)%998244353;
	g[n+1]=0;
	long long ss=0;
	for(int i=1;i<=n;i++)ss=(ss+(g[i]-g[i+1]+998244353)*i)%998244353;
	printf("%lld\n",ss*fjc[n]%998244353);
	return 0;
}
#define p 998244353
#define g 3
struct node
{
	long long a[1048576];
	void ntt(int);
}A,AA,B[2];int len;
int r[1048576];
long long w[1048576];
void node::ntt(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	w[0]=1;
	for(int i=1;i<len;i<<=1)
	{
		long long wi=ksm(g,type*(p-1)/(i<<1)+p-1);
		for(int j=i-2;j>=2;j-=2)w[j]=w[j>>1];
		for(int j=1;j<=i;j+=2)w[j]=w[j-1]*wi%p;
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long ak=a[j+k],awk=w[k]*a[i+j+k]%p;
				a[j+k]=(ak+awk)%p;a[i+j+k]=(ak-awk+p)%p;
			}
		}
	}
}
void dfs(int n,int type)
{
	if(n==1)
	{
		B[type].a[0]=ksm(A.a[0],p-2);
		return ;
	}
	dfs((n+1)/2,type^1);
	len=1;int tt=-1;
	while(len<=2*n)len<<=1,tt++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<tt;
	B[type^1].ntt(1);
	for(int i=0;i<n;i++)AA.a[i]=A.a[i];
	for(int i=n;i<len;i++)AA.a[i]=0;
	AA.ntt(1);
	for(int i=0;i<len;i++)B[type].a[i]=(2*B[type^1].a[i]-AA.a[i]*B[type^1].a[i]%p*B[type^1].a[i]%p+p)%p;
	B[type].ntt(-1);
	long long plen=ksm(len,p-2);
	for(int i=0;i<n;i++)B[type].a[i]=B[type].a[i]*plen%p;
	for(int i=n;i<len;i++)B[type].a[i]=0;
}
void work(int n)
{
	for(int i=0;i<n;i+=2)
	{
		if(i>>1&1)A.a[i]=(p-fjc[i])%p;
		else A.a[i]=fjc[i];
	}
	dfs(n,1);
	len=1;int tt=-1;
	while(len<2*n)len<<=1,tt++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<tt;
	B[0].a[0]=1;
	for(int i=1;i<n;i+=2)
	{
		if(i>>1&1)B[0].a[i]=(p-fjc[i])%p;
		else B[0].a[i]=fjc[i];
	}
	for(int i=2;i<n;i+=2)B[0].a[i]=0;
	for(int i=n;i<len;i++)B[0].a[i]=0;
	B[0].ntt(1);B[1].ntt(1);
	for(int i=0;i<len;i++)AA.a[i]=B[0].a[i]*B[1].a[i]%p;
	AA.ntt(-1);
	long long plen=ksm(len,p-2);
	for(int i=0;i<n;i++)f[i]=AA.a[i]*plen%p*jc[i]%p;
}