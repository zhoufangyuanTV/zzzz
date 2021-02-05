#include<cstdio>
#include<cstring>
using namespace std;
long long a[1100];
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
long long G[710][710];
void Gauss(int n)
{
	for(int i=0;i<n;i++)
	{
		if(G[i][i]==0)
		{
			for(int j=i+1;j<n;j++)
			{
				if(G[j][i]!=0)
				{
					for(int k=0;k<=n;k++)G[i][k]^=G[j][k]^=G[i][k]^=G[j][k];
					break;
				}
			}
		}
		long long K=ksm(998244353-G[i][i],998244351);
		for(int j=0;j<n;j++)
		{
			if(i==j)continue;
			long long Ik=G[j][i]*K%998244353;
			for(int k=0;k<=n;k++)G[j][k]=(G[j][k]+G[i][k]*Ik)%998244353;
		}
	}
	for(int i=0;i<n;i++)G[i][n]=G[i][n]*ksm(G[i][i],998244351)%998244353;
}
struct poly{long long a[1100],len;};
inline poly operator*(poly x,poly y)
{
	poly z;z.len=x.len+y.len;
	for(int i=0;i<=z.len;i++)
	{
		z.a[i]=0;
		for(int j=0;j<=i;j++)z.a[i]=(z.a[i]+x.a[j]*y.a[i-j])%998244353;
	}
	return z;
}
inline poly operator%(poly x,poly y)
{
	for(int i=x.len;i>=y.len;i--)
	{
		for(int j=1;j<=y.len;j++)x.a[i-j]=(x.a[i-j]+x.a[i]*y.a[j])%998244353;
		x.a[i]=0;
	}
	x.len=y.len-1;
	return x;
}
poly ksm(poly x,poly p,long long k)
{
	poly s;s.len=0;s.a[0]=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("poker.in","r",stdin);
	freopen("poker.out","w",stdout);
	int n;long long m,k;scanf("%d%lld%lld",&n,&m,&k);
	long long A=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		A+=a[i];
	}
	A=ksm(A,998244351);
	for(int i=1;i<=n;i++)a[i]=a[i]*A%998244353;
	poly F;F.len=n+1;
	F.a[1]=(a[1]+1)%998244353;
	for(int i=2;i<=n;i++)F.a[i]=(a[i]-a[i-1]+998244353)%998244353;
	F.a[n+1]=(998244353-a[n])%998244353;
	poly x,ss;x.len=1;x.a[0]=0;x.a[1]=1;
	if(m-n-1<=k)
	{
		ss=ksm(x,F,m-1);
		ss.a[]
	}
	poly ss=ksm(x,F,n+k);
	ss.a[ss.len--]=0;
	ss=ss*ksm()
	memset(G,0,sizeof(G));
	Gauss(m);
	printf("%lld\n",G[0][m]);
	return 0;
}