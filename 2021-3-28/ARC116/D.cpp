#include<cstdio>
#include<cstring>
using namespace std;
long long jc[5100],fjc[5100];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
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
long long f[5100],ff[5100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	memset(f,0,sizeof(f));f[0]=1;
	for(int i=2;i<=m;i<<=1)
	{
		for(int j=0;j<=m;j++){ff[j]=f[j];f[j]=0;}
		for(int j=0;j<=n/2;j++)
		{
			for(int k=0;k<=m-i*j;k++)
			{
				f[k+i*j]=(f[k+i*j]+ff[k]*C(n,j*2))%998244353;
			}
		}
	}
	printf("%lld\n",f[m]);
	return 0;
}