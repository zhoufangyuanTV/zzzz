#include<cstdio>
#include<cstring>
using namespace std;
int p;
long long jc[1100],fjc[1100];
inline long long C(long long n,long long m){return jc[n]*fjc[n-m]%p*fjc[m]%p;}
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
long long g[1100];
int main()
{
	freopen("abracadabra.in","r",stdin);
	freopen("abracadabra.out","w",stdout);
    long long n,m;scanf("%*d%lld%lld%d",&n,&m,&p);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	fjc[n]=ksm(jc[n],p-2);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	g[0]=1;g[1]=(m+1)%p;
	for(int i=2;i<=n;i++)g[i]=(ksm(i,m+1)+p-1)*ksm(i-1,p-2)%p;
	long long ss=0,sss=0;
	for(int i=1;i<=n;i++)ss+=g[i];
	ss%=p;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(i-j&1)sss=(sss-C(i,j)*g[j]%p+p)%p;
			else sss=(sss+C(i,j)*g[j])%p;
		}
	}
	printf("%lld\n",(ss-sss+p)%p);
	return 0;
}
