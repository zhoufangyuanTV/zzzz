#include<cstdio>
#include<cstring>
using namespace std;
#define p 998244353
#define g 3
long long ny[32767],W[32767];
inline long long plus(long long x,long long y){return x+y<p?x+y:x+y-p;}
inline long long sub(long long x,long long y){return x<y?x-y+p:x-y;}
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
struct node
{
	long long a[32768];
	void ntt();
	void ttn();
}A,AA,B[2],C[2],D;int len;
int r[32768];
void node::ntt()
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	for(int i=1;i<len;i<<=1)
	{
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long ak=a[j+k],awk=W[16384/i*k]*a[i+j+k]%p;
				a[j+k]=plus(ak,awk);a[i+j+k]=sub(ak,awk);
			}
		}
	}
}
void node::ttn()
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	for(int i=1;i<len;i<<=1)
	{
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long ak=a[j+k],awk=W[32768-16384/i*k]*a[i+j+k]%p;
				a[j+k]=plus(ak,awk);a[i+j+k]=sub(ak,awk);
			}
		}
	}
}
void dfs(int n,int type)
{
	if(n==1)
	{
		B[type].a[0]=1;
		return ;
	}
	dfs((n+1)/2,type^1);
	len=1;int t=-1;
	while(len<2*n)len<<=1,t++;
	r[0]=0;
	for(int i=0;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	for(int i=(n+1)/2;i<len;i++)B[type^1].a[i]=0;
	B[type^1].ntt();
	for(int i=0;i<n;i++)AA.a[i]=A.a[i];
	for(int i=n;i<len;i++)AA.a[i]=0;
	AA.ntt();
	for(int i=0;i<len;i++)B[type].a[i]=(2*B[type^1].a[i]-B[type^1].a[i]*B[type^1].a[i]%p*AA.a[i]%p+p)%p;
	B[type].ttn();
	long long flen=ny[len];
	for(int i=0;i<n;i++)B[type].a[i]=B[type].a[i]*flen%p;
}
void ln(int n,int type)
{
	dfs(n,type^1);
	len=1;int t=-1;
	while(len<2*n)len<<=1,t++;
	r[0]=0;
	for(int i=0;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	for(int i=n;i<len;i++)B[type^1].a[i]=0;
	B[type^1].ntt();
	for(int i=1;i<n;i++)AA.a[i-1]=A.a[i]*i%p;
	for(int i=n-1;i<len;i++)AA.a[i]=0;
	AA.ntt();
	for(int i=0;i<len;i++)B[type].a[i]=AA.a[i]*B[type^1].a[i]%p;
	B[type].ttn();
	long long flen=ny[len];
	for(int i=n-1;i>=1;i--)B[type].a[i]=B[type].a[i-1]*flen%p*ny[i]%p;
	B[type].a[0]=0;
}
void exp(int n,int type)
{
	if(n==1)
	{
		C[type].a[0]=1;
		return ;
	}
	exp((n+1)/2,type^1);
	for(int i=0;i<(n+1)/2;i++)A.a[i]=C[type^1].a[i];
	for(int i=(n+1)/2;i<n;i++)A.a[i]=0;
	ln(n,0);
	len=1;int t=-1;
	while(len<2*n)len<<=1,t++;
	r[0]=0;
	for(int i=0;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	for(int i=n;i<len;i++)A.a[i]=0;
	A.ntt();
	for(int i=0;i<n;i++)B[0].a[i]=sub(D.a[i],B[0].a[i]);
	B[0].a[0]=plus(B[0].a[0],1);
	for(int i=n;i<len;i++)B[0].a[i]=0;
	B[0].ntt();
	for(int i=0;i<len;i++)C[type].a[i]=A.a[i]*B[0].a[i]%p;
	C[type].ttn();
	long long flen=ny[len];
	for(int i=0;i<n;i++)C[type].a[i]=C[type].a[i]*flen%p;
}
int a[110];
int main()
{
	//freopen("elegance.in","r",stdin);
	//freopen("elegance.out","w",stdout);
	for(int i=1;i<=32768;i++)ny[i]=ksm(i,p-2);
	W[0]=1;W[1]=ksm(g,30464);
	for(int i=2;i<=32768;i++)W[i]=W[i-1]*W[1]%p;
	int n,m;scanf("%d%d",&n,&m);
	int M=m,la=0;
	for(int i=2;i*i<=M;i++)
	{
		if(M%i==0)
		{
			a[la++]=i;
			while(M%i==0)M/=i;
		}
	}
	if(M>1)a[la++]=M;
	long long ss=0;
	for(int i=0;i<1<<la;i++)
	{
		M=m;long long k=1;
		for(int j=0;j<la;j++)if((i|1<<j)==i)M/=a[j],k=-k;
		D.a[0]=0;
		for(int j=1;j<=n;j++)
		{
			if(M%j==0)D.a[j]=ny[j];
			else D.a[j]=0;
		}
		exp(n+1,0);
		ss=(ss+k*C[0].a[n]+p)%p;
	}
	for(int i=1;i<=n;i++)ss=ss*i%p;
	printf("%lld\n",ss);
	return 0;
}