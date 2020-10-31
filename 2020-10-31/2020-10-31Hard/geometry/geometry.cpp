#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
#define pi 3.14159265358979323846
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	int n;scanf("%d",&n);
	long double x=0,y=0;
	for(int i=1;i<=n;i++)
	{
		long double theta;scanf("%Lf",&theta);
		x=x+cos(theta/1000000000*pi)*1.5/n;y=y+sin(theta/1000000000*pi)*1.5/n;
	}
	printf("%.15Lf %.15Lf\n",x,y);
	return 0;
}