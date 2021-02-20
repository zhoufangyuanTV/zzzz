#include<cstdio>
#include<cstring>
using namespace std;
long long jc[510000],fjc[510000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
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
long long f(int n,int k)
{
	long long s=0;
	for(int i=0;i<k&&i<=n-k;i++)s=(s+C(n-k,i)*C(k,i+1))%998244353;
	return s*jc[n-k+1]%998244353;
}
int main()
{
	freopen("pk.in","r",stdin);
	freopen("pk.out","w",stdout);
	int L,R,s,type;scanf("%d%d%d%d",&L,&R,&s,&type);
	jc[0]=1;
	for(int i=1;i<=R;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[R]=ksm(jc[R],998244351);
	for(int i=R-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	long long ss=0;
	for(int i=L;i<=R;i++)
	{
		if(type==2&&(i+s)%2==0)continue;
		ss=(ss+f(i+s,i))%998244353;
	}
	printf("%lld\n",ss);
	return 0;
}