#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("brick.in","w",stdout);
	int n=200000,m=1;printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("1 ");
	putchar('\n');
	for(int i=1;i<=m;i++)printf("1 200000 200000 1000000000 1000000000 1000000000\n");
	return 0;
}
