#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("T1.in","w",stdout);
	int n=30000;printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		printf("%d ",rand()%30000);
	}
	printf("\n");
	int m=30000;printf("%d\n",m);
	for(int i=1;i<=m;i++)
	{
		int opt=rand()%3;
		if(opt==0)
		{
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)l^=r^=l^=r;
			printf("A %d %d %d\n",l,r,rand()%30000);
		}
		else if(opt==0)
		{
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)l^=r^=l^=r;
			printf("M %d %d %d\n",l,r,rand()%30000);
		}
		else
		{
			printf("Q %d\n",rand()%n+1);
		}
	}
	return 0;
}