#include<cstdio>
#include<cstring>
using namespace std;
long double f[210];
int main()
{
	freopen("lol.in","r",stdin);
	freopen("lol.out","w",stdout);
	int x;scanf("%d",&x);
	f[x]=1;
	long double ss=0;
	for(int i=1;i<=300000;i++)
	{
		int j;
		for(j=x;j<=99;j+=x)ss=ss+0.01*j*f[j];
		ss=ss+f[j];
		long double s=1;
		for(;j>=2*x;j-=x)
		{
			f[j]=f[j-x]*(100-j+x)*0.01;
			s=s-f[j];
		}
		f[x]=s;
	}
	printf("%.15Lf\n",ss/300000);
	return 0;
}