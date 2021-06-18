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
inline long long plus(long long x,long long y){return x+y<p?x+y:x+y-p;}
inline long long jian(long long x,long long y){return x<y?x-y+p:x-y;}
struct node
{
	long long a[131072];
	void ntt(int);
};int len;
int r[131072];
long long w[131072];
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
node Z,A,AA;
void dfs(int n)
{
	if(n==1)
	{
		Z.a[0]=ksm(A.a[0],p-2);
		return ;
	}
	dfs((n+1)/2);
	len=1;int t=-1;
	while(len<n*2)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	long long flen=ksm(len,p-2);
	Z.ntt(1);
	for(int i=0;i<n;i++)AA.a[i]=A.a[i];
	for(int i=n;i<len;i++)AA.a[i]=0;
	AA.ntt(1);
	for(int i=0;i<len;i++)Z.a[i]=(Z.a[i]*2-Z.a[i]*Z.a[i]%p*AA.a[i]%p+p)%p;
	Z.ntt(-1);
	for(int i=0;i<n;i++)Z.a[i]=Z.a[i]*flen%p;
	for(int i=n;i<len;i++)Z.a[i]=0;
}
void ln(int n)
{
	dfs(n);
	len=1;int t=-1;
	while(len<n*2)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	long long flen=ksm(len,p-2);
	Z.ntt(1);
	for(int i=0;i<n;i++)AA.a[i]=A.a[i+1]*(i+1)%p;
	for(int i=n;i<len;i++)AA.a[i]=0;
	AA.ntt(1);
	for(int i=0;i<len;i++)Z.a[i]=Z.a[i]*AA.a[i]%p;
	Z.ntt(-1);
	for(int i=n-1;i>=1;i--)Z.a[i]=Z.a[i-1]*flen%p*ksm(i,p-2)%p;
	Z.a[0]=0;
	for(int i=n;i<len;i++)Z.a[i]=0;
}
node C,B,BB;
void exp(int n)
{
	if(n==1)
	{
		C.a[0]=1;
		return ;
	}
	exp((n+1)/2);
	for(int i=0;i<(n+1)/2;i++)A.a[i]=C.a[i];
	ln(n);
	for(int i=0;i<(n+1)/2;i++)A.a[i]=0;
	len=1;int t=-1;
	while(len<n*2)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	long long flen=ksm(len,p-2);
    C.ntt(1);
	Z.ntt(1);
	for(int i=0;i<n;i++)BB.a[i]=B.a[i];
	for(int i=n;i<len;i++)BB.a[i]=0;
	BB.ntt(1);
	for(int i=0;i<len;i++)C.a[i]=(C.a[i]-C.a[i]*Z.a[i]%p+BB.a[i]*C.a[i]+p)%p;
	C.ntt(-1);
	for(int i=0;i<len;i++)Z.a[i]=0;
	for(int i=0;i<n;i++)C.a[i]=C.a[i]*flen%p;
	for(int i=n;i<len;i++)C.a[i]=0;
}
int prime[1010000],s;
bool b[10010000];
int f[10010000];
int cnt[51000];
node F;
int main()
{
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	memset(cnt,0,sizeof(cnt));
	memset(b,true,sizeof(b));b[1]=false;
	s=0;
	for(int i=2;i<=m;i++)
	{
		if(b[i])
		{
			prime[++s]=i;
			if(i==2)f[i]=1;
			else
			{
				f[i]=f[i-1];
				if(f[i]<n)cnt[f[i]]++;
			}
		}
		for(int j=1;j<=s&&i*prime[j]<=m;j++)
		{
			b[i*prime[j]]=false;
			f[i*prime[j]]=f[i]+f[prime[j]];
			if(i%prime[j]==0)break;
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=i;j<n;j+=i)
		{
			B.a[j]=(B.a[j]+i*ksm(j,p-2)%p*cnt[i])%p;
		}
	}
	exp(n);
	len=1;int t=-1;
	while(len<n*2)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	long long flen=ksm(len,p-2);
	C.ntt(1);
	F.a[1]=2;
	for(int i=2;i<n;i++)F.a[i]=1;
	F.ntt(1);
	for(int i=0;i<len;i++)F.a[i]=F.a[i]*C.a[i]%p;
	F.ntt(-1);
	for(int i=0;i<n;i++)F.a[i]=F.a[i]*flen%p;
	F.a[0]=plus(F.a[0],1);
	F.a[1]=jian(F.a[1],1);
	long long ss=0;
	for(int i=0;i<n;i++)
	{
		ss=plus(ss,F.a[i]);
		printf("%lld\n",ss);
	}
	return 0;
}
