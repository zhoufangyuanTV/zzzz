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
	long long a[4096];
	void ntt(int);
}S,A;int len;
int r[4096];
long long w[4096];
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
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	long long n,m;scanf("%lld%lld",&n,&m);
	A.a[1]=1;S.a[0]=1;
	long long k=n*m;
	len=1;int t=-1;
	while(len<m*2)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	long long flen=ksm(len,p-2);
	while(k>0)
	{
		A.ntt(1);
		if(k&1)
		{
			S.ntt(1);
			for(int i=0;i<len;i++)S.a[i]=S.a[i]*A.a[i]%p;
			S.ntt(-1);
			for(int i=0;i<len;i++)S.a[i]=S.a[i]*flen%p;
			for(int i=2*m-2;i>=m;i--)
			{
				S.a[i-m+1]=plus(S.a[i-m+1],S.a[i]);
				S.a[i-m]=plus(S.a[i-m],S.a[i]);
				S.a[i]=0;
			}
		}
		for(int i=0;i<len;i++)A.a[i]=A.a[i]*A.a[i]%p;
		A.ntt(-1);
		for(int i=0;i<len;i++)A.a[i]=A.a[i]*flen%p;
		for(int i=2*m-2;i>=m;i--)
		{
			A.a[i-m+1]=plus(A.a[i-m+1],A.a[i]);
			A.a[i-m]=plus(A.a[i-m],A.a[i]);
			A.a[i]=0;
		}
		k>>=1;
	}
	printf("%lld\n",plus(S.a[0],S.a[m-1]));
	return 0;
}