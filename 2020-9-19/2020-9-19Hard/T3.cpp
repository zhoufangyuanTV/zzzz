#include<cstdio>
#include<cstring>
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x;
		x=x*x;
		k>>=1;
	}
	return s;
}
int main()
{
	int n;scanf("%d",&n);
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		ss=ss+ksm(17,n/gcd(i,n));
	}
	printf("%lld\n",ss/n);
	return 0;
}