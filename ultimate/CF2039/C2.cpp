#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int x;long long m;scanf("%d%lld",&x,&m);
		int g=1;
		while(g<=x)g*=2;
		long long s=0;
		for(int i=1;i<g&&i<=m;i++)
		{
			if((x^i)%x==0||(x^i)%i==0)s++;
		}
		long long st=(g-1)/x+1,ed=m/x-1;
		if(st<ed)
		{
			s+=ed-st;
			if((((st-1)*x)^x)>=g)s++;
			if(((st*x)^x)>=g)s++;
			if((((ed+1)*x)^x)<=m)s++;
			if((((ed+2)*x)^x)<=m)s++;
		}
		else
		{
			for(int i=g;i<=m;i++)
			{
				if((x^i)%x==0||(x^i)%i==0)s++;
			}
		}
		printf("%lld\n",s);
	}
	return 0;
}