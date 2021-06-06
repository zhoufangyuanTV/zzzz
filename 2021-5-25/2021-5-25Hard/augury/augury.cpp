#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("augury.in","r",stdin);
	freopen("augury.out","w",stdout);
	int t;scanf("%*d%d",&t);
	while(t--)
	{
		long double pL,pD,p;scanf("%Lf%Lf%Lf",&pL,&pD,&p);
		long double Alpha=0,Beta=0,Omega;
		for(int i=2999999;i>=1;i--)
		{
			Omega=1+(p-1)*(1-pL-pD+pD*Alpha);
			Alpha=(1-p)*pL/Omega;
			Beta=(1-p)*pD*Beta/Omega;
		}
		Omega=1+(p-1)*(1-pL-pD+pD*Alpha);
		long double a1=(1-p)*pL/Omega,b1=(pL+(1-p)*pD*Beta)/Omega;
		Alpha=0;Beta=1/p;
		for(int i=3000000;i>=2;i--)
		{
		    Omega=1+(p-1)*(1-pL-pD+pL*Alpha);
			Alpha=(1-p)*pD/Omega;
			Beta=(1+(1-p)*pL*Beta)/Omega;
		}
		Omega=1+(p-1)*(1-pL-pD+pL*Alpha);
		long double a2=(1-p)*pD/Omega,b2=(1-pD+(1-p)*pL*Beta)/Omega;
		printf("%.10Lf\n",(a1*b2+b1)/(1-a1*a2));
	}
	return 0;
}
