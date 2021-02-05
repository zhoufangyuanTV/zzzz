#include<cstdio>
#include<cstring>
using namespace std;
unsigned a[210000];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%u",&a[i]);
	int t;scanf("%d",&t);
	while(t--)
	{
		unsigned d,p1,p2;scanf("%u%u%u",&d,&p1,&p2);
		unsigned long long s=(unsigned long long)(d-1)*d/2;
		unsigned ss=d*d*s;
		ss=ss*(d*2+1+a[p2]);
		ss=ss+a[p1]*d*d*d;
		printf("%u\n",ss);
	}
	return 0;
}