#include<cstdio>
#include<cstring>
using namespace std;
int p;
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
int main()
{
	freopen("dtree.in","r",stdin);
	freopen("dtree.out","w",stdout);
	int n;scanf("%d%d",&n,&p);
	long long f,g=0,jc=1;
	for(int i=2;i<=n;i++)
	{
		f=(2*jc*g+jc*(i-2)%p*(i+1)%p*(p+1)/2)%p;
		jc=jc*i%p;
		g=(g+f*ksm(jc,p-2))%p;
	}
	printf("%lld\n",f);
	return 0;
}