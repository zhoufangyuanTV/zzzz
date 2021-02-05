#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int p[110000];
int main()
{
	freopen("color.in","w",stdout);
	int n=100000,m=100000;printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)p[i]=i;
	random_shuffle(p+1,p+n+1);
	for(int i=1;i<=n;i++)printf("%d %d\n",p[i],rand()%n+1);
	for(int i=1;i<=m;i++)
	{
		int l=rand()%n+1,r=rand()%n+1,u=rand()%n+1,d=rand()%n+1;
		if(l>r)l^=r^=l^=r;
		if(u>d)u^=d^=u^=d;
		printf("%d %d %d %d\n",l,r,u,d);
	}
	return 0;
}