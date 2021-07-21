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
struct poly
{
	long long a[65536];
	void ntt(int);
}Z,A,AA;int len;
int r[65536];
long long w[65536];
void poly::ntt(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	w[0]=1;
	for(int i=1;i<len;i<<=1)
	{
		long long wi=ksm(g,p-1+type*(p-1)/i/2);
		for(int j=i-2;j>0;j-=2)w[j]=w[j>>1];
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
	for(int i=0;i<len;i++)Z.a[i]=(2*Z.a[i]-Z.a[i]*Z.a[i]%p*AA.a[i]%p+p)%p;
	Z.ntt(-1);
	long long flen=ksm(len,p-2);
	for(int i=0;i<n;i++)Z.a[i]=Z.a[i]*flen%p;
	for(int i=n;i<len;i++)Z.a[i]=0;
}
struct matrix
{
	int n,m;
	long long a[64][64];
	matrix& operator*=(const matrix&);
}S,M;
long long c[64];
inline matrix& matrix::operator*=(const matrix &x)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<x.m;j++)
		{
			c[j]=0;
			for(int k=0;k<m;k++)c[j]=(c[j]+a[i][k]*x.a[k][j])%p;
		}
		for(int j=0;j<x.m;j++)a[i][j]=c[j];
	}
	m=x.m;
	return *this;
}
long long Ans[64][21000];
int cnt[64];
int main()
{
	freopen("bai.in","r",stdin);
	freopen("bai.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	M.n=n;M.m=n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%lld",&M.a[i][j]);
		}
	}
	S.n=n;S.m=n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)S.a[i][j]=i==j;
	}
	for(int i=1;i<=m;i++)
	{
		S*=M;
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				int f=j&k;
				for(int l=f;l>0;l=(l-1)&f)Ans[l][i]=plus(Ans[l][i],S.a[j][k]);
				Ans[0][i]=plus(Ans[0][i],S.a[j][k]);
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		A.a[0]=1;
		for(int j=1;j<=m;j++)A.a[j]=jian(0,Ans[i][j]);
		dfs(m+1);
		Z.a[0]=0;
		for(int j=1;j<=m;j++)
		{
			Ans[i][j]=Z.a[j];
			Z.a[j]=0;
		}
	}
	cnt[0]=0;
	for(int i=1;i<n;i++)cnt[i]=cnt[i>>1]+(i&1);
	long long ss=0;
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=j+1;k<n;k++)
			{
				if(j==(j&k))
				{
					if(cnt[j^k]&1)Ans[j][i]=jian(Ans[j][i],Ans[k][i]);
					else Ans[j][i]=plus(Ans[j][i],Ans[k][i]);
				}
			}
			ss^=Ans[j][i];
		}
	}
	printf("%lld\n",ss);
	return 0;
}
