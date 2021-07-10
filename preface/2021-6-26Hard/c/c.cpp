#include<cstdio>
#include<cstring>
using namespace std;
#define p 998244353
#define g 3
inline long long ksm(long long x,long long k)
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
long long jc[1010000],fjc[1010000];
inline long long f(int n){return jc[n-1]*fjc[n]%p;}
struct node
{
	long long a[2097152];
	void ntt(int);
}Z,A,AA;int len;
int r[2097152];
long long w[2097152];
inline long long plus(long long x,long long y){return x+y<p?x+y:x+y-p;}
inline long long jian(long long x,long long y){return x<y?x-y+p:x-y;}
void node::ntt(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	w[0]=1;
	for(int i=1;i<len;i<<=1)
	{
		long long wi=ksm(g,p-1+type*(p-1)/i/2);
		for(int j=i-2;j>=2;j-=2)w[j]=w[j>>1];
		for(int j=1;j<i;j+=2)w[j]=w[j-1]*wi%p;
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long ak=a[j+k],awk=w[k]*a[i+j+k]%p;
				a[j+k]=plus(ak,awk);a[i+j+k]=jian(ak,awk);
			}
		}
	}
}
void dfs(int n)
{
	if(n==1)
	{
		Z.a[0]=ksm(A.a[0],p-2);
		return ;
	}
	dfs((n+1)/2);
	len=1;int t=-1;
	while(len<2*n)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	Z.ntt(1);
	for(int i=0;i<n;i++)AA.a[i]=A.a[i];
	for(int i=n;i<len;i++)AA.a[i]=0;
	AA.ntt(1);
	for(int i=0;i<len;i++)Z.a[i]=(2*Z.a[i]-AA.a[i]*Z.a[i]%p*Z.a[i]%p+p)%p;
	Z.ntt(-1);
	long long flen=ksm(len,p-2);
	for(int i=0;i<n;i++)Z.a[i]=Z.a[i]*flen%p;
	for(int i=n;i<len;i++)Z.a[i]=0;
}
void ln(int n)
{
	dfs(n);
	len=1;int t=-1;
	while(len<2*n)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	Z.ntt(1);
	for(int i=1;i<n;i++)AA.a[i-1]=A.a[i]*i%p;
	for(int i=n-1;i<len;i++)AA.a[i]=0;
	AA.ntt(1);
	for(int i=0;i<len;i++)Z.a[i]=Z.a[i]*AA.a[i]%p;
	Z.ntt(-1);
	long long flen=ksm(len,p-2);
	for(int i=n-1;i>=1;i--)Z.a[i]=Z.a[i-1]*f(i)%p*flen%p;
	Z.a[0]=0;
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	int n;scanf("%d",&n);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	fjc[n]=ksm(jc[n],p-2);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	A.a[0]=1;
	for(int i=1;i<=n;i++)
	{
		long long x=1ll*i*(i-1)/2;
		A.a[i]=ksm(2,x)*fjc[i]%p;
	}
	ln(n+1);
	long long S1=Z.a[n]*jc[n]%p,S2=jc[n-1];
	if(n%2==0)S2=jian(0,S2);
	printf("%lld\n",jian(S1,S2)*499122177%p);
	return 0;
}
