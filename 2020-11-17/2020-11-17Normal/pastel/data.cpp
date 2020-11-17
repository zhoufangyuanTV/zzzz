#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int col[110];
int main()
{
	freopen("pastel.in","w",stdout);
	srand(time(0));
	int n=6,m=15;printf("%d %d\n",n,m);
	for(int i=2;i<=n;i++)printf("%d ",rand()%(i-1)+1);
	putchar('\n');
	int i,mg=rand()%4;
	memset(col,0,sizeof(col));col[1]=1;
	for(i=1;i<=mg;i++)
	{
		int x=rand()%(n-1)+2;
		while(col[x]==1)x=rand()%(n-1)+2;
		printf("5 %d\n");
	}
	for(;i<=m;i++)
	{
		int opt=rand()%4+1;
		printf("%d ",opt);
		if(opt==1)printf("%d\n",rand()%n+1);
		else if(opt==2)
		{
			int x=rand()%n+1;
			while(col[x]!=1)x=rand()%n+1;
			printf("%d %d\n",x,rand()%100+1);
		}
		else if(opt==3)printf("%d\n",rand()%n+1);
		else printf("%d %d\n",rand()%n+1,rand()%100+1);
	}
	return 0;
}