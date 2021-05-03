#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define p 998244353
#define g 3
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
long long jc[4100],fjc[4100];
struct node
{
	int x;
	bool bk;
}a[4100];
inline bool cmp(node x,node y){return x.x<y.x;}
struct poly
{
	long long a[4096];
	void ntt(int);
}G,A,B;int len;
int r[4096];
long long w[4096];
void poly::ntt(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	w[0]=1;
	for(int i=1;i<len;i<<=1)
	{
		long long wi=ksm(g,type*(p-1)/i/2+p-1);
		for(int j=i-2;j>=2;j-=2)w[j]=w[j>>1];
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
int n,m;
long long Ans[4100];
void calc(int s1,int s2,long long x,int type)
{
	int N=n-s1-s2;
	long long xx=1;
	for(int i=N+1;i>=0;i--)
	{
		A.a[i]=xx*fjc[N-i+1]%p;
		xx=xx*x%p;
	}
	for(int i=0;i<=N;i++)B.a[i]=G.a[i]*jc[i]%p;
	len=1;int t=-1;
	while(len<=N*2+1)len<<=1,t++;
	r[0]=0;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<t;
	for(int i=N+2;i<len;i++)A.a[i]=0;
	for(int i=N+1;i<len;i++)B.a[i]=0;
	A.ntt(1);B.ntt(1);
	for(int i=0;i<len;i++)A.a[i]=A.a[i]*B.a[i]%p;
	A.ntt(-1);
	long long flen=ksm(len,p-2);
	long long mm=1;
	for(int i=N;i<=N*2;i++)
	{
		B.a[N*2-i]=A.a[i]*flen%p*mm%p*fjc[i-N]%p;
		mm=mm*m%p;
	}
	for(int i=0;i<=N;i++)B.a[i]=B.a[i]*jc[i]%p;
	for(int i=N+1;i<len;i++)B.a[i]=0;
	for(int i=0;i<=N;i++)
	{
		A.a[i]=fjc[N-i];
		if((N-i)&1)A.a[i]=(p-A.a[i])%p;
	}
	for(int i=N+1;i<len;i++)A.a[i]=0;
	A.ntt(1);B.ntt(1);
	for(int i=0;i<len;i++)A.a[i]=A.a[i]*B.a[i]%p;
	A.ntt(-1);
	for(int i=N;i<=N*2;i++)Ans[i-N+1+s2]=(Ans[i-N+1+s2]+A.a[i]*flen%p*fjc[i-N]%p*type+p)%p;
}
int main()
{
	scanf("%d%d",&n,&m);
	long long fm=ksm(m,p-2);
	jc[0]=1;
	for(int i=1;i<=n+1;i++)jc[i]=jc[i-1]*i%p;
	fjc[n+1]=ksm(jc[n+1],p-2);
	for(int i=n;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i*2-1].x);
		a[i*2-1].bk=false;a[i*2].bk=true;
		a[i*2].x=a[i*2-1].x+m;
	}
	sort(a+1,a+n*2+1,cmp);
	int s1=n,s2=0;
	G.a[0]=1;
	for(int t=1;t<=n*2;t++)
	{
		calc(s1,s2,a[t].x,1);
		if(t==n*2)break;
		if(a[t].bk==false)
		{
			int N=n-s1-s2;
			for(int i=N;i>=0;i--)
			{
				G.a[i+1]=(G.a[i+1]+G.a[i]*fm)%p;
				G.a[i]=G.a[i]*fm%p*(p-a[t].x)%p;
			}
			s1--;
		}
		else
		{
			int N=n-s1-s2;
			for(int i=N;i>=1;i--)
			{
				G.a[i-1]=(G.a[i-1]+G.a[i]*(a[t].x-m))%p;
				G.a[i]=G.a[i]*m%p;
			}
			for(int i=0;i<N;i++)G.a[i]=G.a[i+1];
			G.a[N]=0;
			s2++;
		}
		calc(s1,s2,a[t].x,-1);
	}
	Ans[0]=0;
	for(int i=1;i<=n;i++)
	{
		Ans[i]=(Ans[i]+Ans[i-1])%p;
		printf("%lld\n",Ans[i]);
	}
	return 0;
}