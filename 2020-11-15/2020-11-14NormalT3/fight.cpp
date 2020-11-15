#include<cstdio>
#include<cstring>
using namespace std;
#define p 998244353
#define g 3
long long jc[210000],fjc[210000];
long long ksm(long long x,long long k)
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
struct node
{
	long long a[524288];
	void ntt(int);
}gA,gB,G,F;int len;
int r[524288];
long long w[524288];
void node::ntt(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	w[0]=1;
	for(int i=1;i<len;i<<=1)
	{
		long long wi=ksm(g,type*(p-1)/(i<<1)+p-1);
		for(int j=i-2;j>=0;j-=2)w[j]=w[j>>1];
		for(int j=1;j<i;j+=2)w[j]=w[j-1]*wi%p;
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
int main()
{
	freopen("fight.in","r",stdin);
	freopen("fight.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	fjc[n]=ksm(jc[n],p-2);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	len=1;int t=-1;
	while(len<=n<<1)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	int plen=ksm(len,p-2);
	gA.a[0]=0;
	for(int i=1;i<=n;i++)gA.a[i]=fjc[i]*ksm(2,i)%p*fjc[i-1]%p;
	for(int i=0;i<n;i++)gB.a[i]=(fjc[i]*(i&1?-1:1)*jc[n-i-1]%p+p)%p;
	gB.a[n]=0;
	gA.ntt(1);gB.ntt(1);
	for(int i=0;i<len;i++)G.a[i]=gA.a[i]*gB.a[i]%p;
	G.ntt(-1);
	for(int i=0;i<n;i++)G.a[i]=G.a[i+1]*plen%p*fjc[n-i-1]%p*jc[i+1]%p*jc[i+1]%p;
	G.a[n-1]=(G.a[n-1]+jc[n]*(n&1?-1:1)+p)%p;
	for(int i=0;i<n;i++)G.a[i]=G.a[i]*jc[n-i-1]%p;
	for(int i=n;i<len;i++)G.a[i]=0;
	for(int i=0;i<n;i++)F.a[i]=(fjc[i]*(i&1?-1:1)+p)%p;
	G.ntt(1);F.ntt(1);
	for(int i=0;i<len;i++)F.a[i]=G.a[i]*F.a[i]%p;
	F.ntt(-1);
	for(int i=0;i<n;i++)F.a[i]=F.a[i]*plen%p*fjc[n-i-1]%p;
	long long ss=0;
	for(int i=0;i<=m;i++)ss=(ss+F.a[i])%p;
	printf("%lld\n",ss);
	return 0;
}