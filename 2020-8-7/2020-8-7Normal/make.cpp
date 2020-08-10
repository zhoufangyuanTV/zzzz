#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("friend.in","w",stdout);
	int n=150,m=300000,q=50000;
	printf("%d %d %d\n",n,m,q);
	for(int i=1;i<=m;i++)printf("%d %d\n",rand()%n+1,rand()%n+1);
	for(int i=1;i<=q;i++)
	{
		int l=rand()%m+1,r=rand()%m+1;
		if(l>r)l^=r^=l^=r;
		printf("%d %d\n",l,r);
	}
	return 0;
}