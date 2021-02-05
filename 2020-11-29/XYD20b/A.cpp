#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int k;
		double v1,v2,x;scanf("%d%lf%lf%lf",&k,&v1,&v2,&x);
		if(k==1)
		{
			printf("%lf\n",x/(v1+v2)*v1);
			continue;
		}
		if(v2-v1>-1e-6)
		{
			if(k&1)printf("%lf\n",x/(v1+v2)*v1);
			else printf("%lf\n",(200-x)/(v1+v2)*v1);
		}
		else if(100/v1-(100-x)/v2>-1e-6)
		{
			if(k&1)printf("%lf\n",x/(v1+v2)*v1);
			else printf("%lf\n",(200-x)/(v1+v2)*v1);
		}
		else
		{
			k--;
			x=x/(v1+v2)*v1;
			bool bk=false;
			while(k>0)
			{
				x=x+x/v1*v2;
				x=x/(v1-v2)*v1;
				k--;
				if(200/(v1+v2)*v2+x-100>-1e-6)break;
			}
			if(k&1)printf("%lf\n",200-200/(v1+v2)*v2-x);
			else printf("%lf\n",x);
		}
	}
	return 0;
}