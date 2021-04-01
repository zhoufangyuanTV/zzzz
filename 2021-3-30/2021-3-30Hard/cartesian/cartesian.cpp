#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("cartesian.in","r",stdin);
	freopen("cartesian.out","w",stdout);
	int n,p;scanf("%d%d",&n,&p);
	long long f=0,g=0,h=1;
	for(int i=1;i<=n;i++)
	{
		h=h*i%p;
		long long ff=(h+f)%p,gg=(h+g)%p;
		if(i==n)printf("%lld\n",ff);
		f=(f*i+ff+gg)%p;
		g=(g*i+gg)%p;
	}
	return 0;
}