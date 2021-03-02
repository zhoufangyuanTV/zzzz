#include<cstdio>
#include<cstring>
using namespace std;
double alpha[1100],beta[1100],p[1100];
int main()
{
	double w,h;int n;scanf("%lf%lf%d",&w,&h,&n);
	double k=h/w;
	double phi=(1-k*k)/2;
	alpha[1]=0;beta[1]=phi;
	for(int i=2;i<=n;i++)alpha[i]=phi*alpha[i-1]/(1-phi*beta[i-1]),beta[i]=phi/(1-phi*beta[i-1]);
	p[n+1]=w;
	for(int i=n;i>=1;i--)p[i]=alpha[i]+beta[i]*p[i+1];
	p[0]=0;
	double ss=0;
	for(int i=0;i<=n;i++)ss=ss+((k-1)*p[i]+(k+1)*p[i+1])*((k-1)*p[i]+(k+1)*p[i+1])/4;
	for(int i=1;i<=n;i++)ss=ss-p[i]*p[i]*k*k/2;
	printf("%lf\n",ss);
	if(n>10)n=10;
	for(int i=1;i<=n;i++)printf("%lf\n",p[i]);
	return 0;
}