#include<cstdio>
#include<cstring>
using namespace std;
long long p;
inline long long S1(long long n){return n;}
inline long long Sid(long long n){return n*(n+1)/2%p;}
inline long long Sid2(long long n)
{
	long long a=n*(n+1)/2,b=2*n+1;
	if(n%3!=1)a/=3;
	else b/=3;
	return a%p*b%p;
}
inline long long Sid3(long long n){return Sid(n)*Sid(n)%p;}
long long n,S[3000001],SS[501];
long long Du1(long long i)
{
	int j=n/i;
	if(i<=3000000)return S[i];
	else if(SS[j]!=-1)return SS[j];
	SS[j]=Sid(i);
	for(int l=2;l<=i;l++)
	{
		int r=i/(i/l);
		SS[j]=(SS[j]-(S1(r)-S1(l-1)+p)*Du1(i/l)%p+p)%p;
		l=r;
	}
	return SS[j];
}
long long Du2(long long i)
{
	int j=n/i;
	if(i<=3000000)return S[i];
	else if(SS[j]!=-1)return SS[j];
	SS[j]=Sid2(i);
	for(int l=2;l<=i;l++)
	{
		int r=i/(i/l);
		SS[j]=(SS[j]-(Sid(r)-Sid(l-1)+p)*Du2(i/l)%p+p)%p;
		l=r;
	}
	return SS[j];
}
long long Du3(long long i)
{
	int j=n/i;
	if(i<=3000000)return S[i];
	else if(SS[j]!=-1)return SS[j];
	SS[j]=Sid3(i);
	for(int l=2;l<=i;l++)
	{
		int r=i/(i/l);
		SS[j]=(SS[j]-(Sid2(r)-Sid2(l-1)+p)*Du3(i/l)%p+p)%p;
		l=r;
	}
	return SS[j];
}
int Prime[1000001],s;
bool b[3000001];
long long phi[3000001];
void Euler()
{
	memset(b,true,sizeof(b));b[1]=false;phi[1]=1;s=0;
	for(int i=2;i<=3000000;i++)
	{
		if(b[i])Prime[++s]=i,phi[i]=(i-1);
		for(int j=1;j<=s&&i*Prime[j]<=3000000;j++)
		{
			b[i*Prime[j]]=false;
			if(i%Prime[j]==0)
			{
				phi[i*Prime[j]]=phi[i]*Prime[j]%p;
				break;
			}
			else phi[i*Prime[j]]=phi[i]*(Prime[j]-1)%p;
		}
	}
}
int main()
{
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	scanf("%lld%lld",&n,&p);
	Euler();
	for(int i=1;i<=3000000;i++)S[i]=(S[i-1]+phi[i])%p;
	memset(SS,-1,sizeof(SS));
	long long s=Du1(n);
	Euler();
	for(int i=1;i<=3000000;i++)S[i]=(S[i-1]+phi[i]*i)%p;
	memset(SS,-1,sizeof(SS));
	long long ss=Du2(n);
	Euler();
	for(int i=1;i<=3000000;i++)S[i]=(S[i-1]+phi[i]*i%p*i)%p;
	memset(SS,-1,sizeof(SS));
	long long sss=Du3(n);
	printf("%lld\n",(4*n*n%p*s%p-6*n*ss%p+2*sss+p)%p);
	return 0;
}