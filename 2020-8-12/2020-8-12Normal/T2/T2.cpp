#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c;
}a[251000];
inline bool cmp(node x,node y){return x.x<y.x;}
inline bool cmp0(node x,node y){return x.y<y.y;}
inline long long dis(node x,node y){return x.c==y.c?0:1ll*(x.x-y.x)*(x.x-y.x)+1ll*(x.y-y.y)*(x.y-y.y);}
inline long long mymax(long long x,long long y){return x>y?x:y;}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].c);
	sort(a+1,a+n+1,cmp);
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=99&&j<=n;j++)
		{
			ss=mymax(ss,dis(a[i],a[j]));
		}
		for(int j=mymax(1,n-99);j<=n;j++)
		{
			ss=mymax(ss,dis(a[i],a[j]));
		}
		for(int j=i+1;j<=i+99&&j<=n;j++)
		{
			ss=mymax(ss,dis(a[i],a[j]));
		}
	}
	sort(a+1,a+n+1,cmp0);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=99&&j<=n;j++)
		{
			ss=mymax(ss,dis(a[i],a[j]));
		}
		for(int j=mymax(1,n-99);j<=n;j++)
		{
			ss=mymax(ss,dis(a[i],a[j]));
		}
		for(int j=i+1;j<=i+99&&j<=n;j++)
		{
			ss=mymax(ss,dis(a[i],a[j]));
		}
	}
	printf("%lld\n",ss);
	return 0;
}