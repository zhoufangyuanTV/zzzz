#include<cstdio>
#include<cstring>
using namespace std;
long long jc[100000007],fjc[100000007];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%100000007;
		x=x*x%100000007;
		k>>=1;
	}
	return s;
}
long long C(long long m,long long n)
{
	if(m<n)return 0;
	if(m<100000007)return jc[m]*fjc[m-n]%100000007*fjc[n]%100000007;
	return C(m/100000007,n/100000007)*C(m%100000007,n%100000007)%100000007;
}
int main()
{
	freopen("final.in","r",stdin);
	freopen("final.out","w",stdout);
	jc[0]=1;
	for(register int i=1;i<=100000006;i++)jc[i]=jc[i-1]*i%100000007;
	fjc[100000006]=ksm(jc[100000006],100000005);
	for(register int i=100000005;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%100000007;
	long long n,m;scanf("%lld%lld",&n,&m);
	printf("%lld\n",C(2*m,2*n));
	return 0;
}