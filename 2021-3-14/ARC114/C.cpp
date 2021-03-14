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
long long a[5100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	long long p=n,s=0,np=ksm(m,998244351);
	for(int i=0;i<=m;i++)a[i]=1;
	long long N=np*np%998244353;
	for(int i=2;i<=n;i++,N=N*np%998244353)
	{
		for(int j=0;j<m;j++)s=(s+a[j]*N)%998244353;
		p=(p-s+998244353)%998244353;
		for(int j=0;j<m;j++)a[j]=a[j]*j%998244353;
	}
	printf("%lld\n",p*ksm(m,n)%998244353);
	return 0;
}