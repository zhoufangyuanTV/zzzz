#include<cstdio>
#include<cstring>
using namespace std;
long long ksm(long long x,long long k)
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
long long jc[10010000],fjc[10010000];
long long F[10010000],Ans[10010000];
int main()
{
	freopen("power.in","r",stdin);
	freopen("power.out","w",stdout);
	jc[0]=1;
	for(int i=1;i<=10000000;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[10000000]=ksm(jc[10000000],998244351);
	for(int i=9999999;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	F[0]=1;Ans[0]=F[1];
	for(int i=1;i<=5100;i++)
	{
		for(int j=5100;j>=0;j--)F[j]=(F[j]+F[j-1]+F[j-2])%998244353;
		Ans[i]=F[i+1];
	}
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		if(n<=5000)printf("%lld\n",Ans[n]);
		else
		{
			long long ss=0;
			for(int i=0;i<=(n-1)/2;i++)ss=(ss+jc[n]*fjc[i+1]%998244353*fjc[i]%998244353*fjc[n-1-2*i]%998244353)%998244353;
			printf("%lld\n",ss);
		}
	}
	return 0;
}