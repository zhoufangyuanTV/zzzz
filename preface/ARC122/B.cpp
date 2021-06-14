#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110000];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	double x=a[(n+1)/2]/2.0;
	double ss=0;
	for(int i=1;i<=n;i++)
	{
		ss+=x+a[i]-min(double(a[i]),x*2);
	}
	printf("%.6lf\n",ss/n);
	return 0;
}