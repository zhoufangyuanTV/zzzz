#include<cstdio>
#include<cstring>
using namespace std;
int a[5100];
int main()
{
	freopen("orz.in","r",stdin);
	freopen("orz.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int l,r,x;scanf("%d%d%d",&l,&r,&x);
		double ss=1;
		for(int j=l;j<=r;j++)ss=ss*(x-a[j])/x;
		printf("%.10lf\n",1-ss);
	}
	return 0;
}