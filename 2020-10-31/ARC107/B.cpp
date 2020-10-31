#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	long long ss=0;
	for(int i=2;i<=2*n;i++)
	{
		long long a=i,b=i+k;
		if(a<=n)a=a-1;
		else if(a<=2*n)a=2*n-a+1;
		else a=0;
		if(b<2)b=0;
		else if(b<=n)b=b-1;
		else if(b<=2*n)b=2*n-b+1;
		else b=0;
		ss=ss+a*b;
	}
	printf("%lld\n",ss);
	return 0;
}