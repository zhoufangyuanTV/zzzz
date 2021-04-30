#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct point
{
	long double x,y;
	int p;
}a[4100];
inline bool cmp(point x,point y){return x.x<y.x;}
int c[4100];
int main(int argc,char* argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	srand(time(0));
	int n;scanf("%d",&n);
	for(int i=1;i<=n*2;i++)
	{
		scanf("%Lf%Lf",&a[i].x,&a[i].y);
		a[i].p=i;
	}
	int t=10000;
	long long ss=0;
	while(t--)
	{
		long double theta=2*M_PI*rand()/RAND_MAX;
		for(int i=1;i<=n*2;i++)
		{
			long double xx=a[i].x,yy=a[i].y;
			a[i].x=xx*cos(theta)+yy*sin(theta);
			a[i].y=-xx*sin(theta)+yy*cos(theta);
		}
		sort(a+1,a+n*2+1,cmp);
		long long s=0;
		for(int i=1;i<=n;i++)
		{
			s=s+sqrt((a[i*2-1].x-a[i*2].x)*(a[i*2-1].x-a[i*2].x)+(a[i*2-1].y-a[i*2].y)*(a[i*2-1].y-a[i*2].y));
		}
		if(ss<s)
		{
			ss=s;
			for(int i=1;i<=n;i++)
			{
				c[a[i*2-1].p]=a[i*2].p;
				c[a[i*2].p]=a[i*2-1].p;
			}
		}
	}
	for(int i=1;i<n*2;i++)printf("%d ",c[i]);
	printf("%d\n",c[n*2]);
	return 0;
}
