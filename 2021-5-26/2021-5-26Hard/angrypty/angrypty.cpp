#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
long long n;
bool b[10010000];
int p[1010000],s;
int low[10010000],mu[10010000],mu2[10010000],two[10010000],d[10010000];
int Smu2[10010000],MU2[11000],Stwo[10010000],TWO[11000],Sd[10010000],D[11000];
inline int S1(long long x){return x<=10000000?Smu2[x]:MU2[n/x];}
inline int S2(long long x){return x<=10000000?Stwo[x]:TWO[n/x];}
inline int S3(long long x){return x<=10000000?Sd[x]:D[n/x];}
int main()
{
	freopen("angrypty.in","r",stdin);
	freopen("angrypty.out","w",stdout);
	scanf("%lld",&n);
	b[1]=true;
	low[1]=mu[1]=mu2[1]=two[1]=d[1]=1;
	for(int i=2;i<=10000000;i++)
	{
		if(!b[i])
		{
			p[++s]=i;
			low[i]=i;
			mu[i]=-1;
			mu2[i]=1;
			two[i]=2;
			d[i]=3;
		}
		for(int j=1;j<=s&&i*p[j]<=10000000;j++)
		{
			b[i*p[j]]=true;
			if(i%p[j]==0)
			{
				low[i*p[j]]=low[i]*p[j];
				two[i*p[j]]=two[i];
				d[i*p[j]]=d[i/low[i]]*(d[low[i]]+2);
				break;
			}
			else
			{
				low[i*p[j]]=p[j];
				mu[i*p[j]]=-mu[i];
				mu2[i*p[j]]=mu2[i];
				two[i*p[j]]=two[i]*2;
				d[i*p[j]]=d[i]*3;
			}
		}
	}
	for(int i=2;i<=500000;i++)mu[i]+=mu[i-1];
	for(int i=1;i<=10000000;i++)
	{
		Smu2[i]=Smu2[i-1]+mu2[i];
		Stwo[i]=Stwo[i-1]+two[i];
		Sd[i]=Sd[i-1]+d[i];
	}
	for(int i=1;i<=10000;i++)
	{
		long long N=n/i;
		long long N2=sqrt(N);
		long long s=0;
		for(int l=1;l<=N2;l++)
		{
			long long c=N/l/l;
			long long r=sqrt(N/c);
			s+=c*(mu[r]-mu[l-1]);
			l=r;
		}
		MU2[i]=(s%998244353+998244353)%998244353;
	}
	for(int i=1;i<=10000;i++)
	{
		long long N=n/i;
		long long N2=sqrt(N);
		long long s=0;
		for(int j=1;j<=N2;j++)
		{
			long long k=N/j;
			s+=S1(k)+mu2[j]*k;
		}
		TWO[i]=(s-N2*Smu2[N2]%998244353+998244353)%998244353;
	}
	for(int i=1;i<=10000;i++)
	{
		long long N=n/i;
		long long N2=sqrt(N);
		long long s=0;
		for(int j=1;j<=N2;j++)
		{
			long long k=N/j;
			s+=S2(k)+two[j]*k;
		}
		D[i]=(s-N2*Stwo[N2]%998244353+998244353)%998244353;
	}
	long long ss=0;
	long long n2=sqrt(n);
	for(int i=1;i<=n2;i++)
	{
		long long j=n/i;
		ss+=S3(j)+d[i]*j;
	}
	printf("%lld\n",(ss-n2*Sd[n2]%998244353+998244353)%998244353);
	return 0;
}