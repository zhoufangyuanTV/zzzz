#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
bool fc[510000],gr[510000];
int main()
{
	freopen("diyiti.in","w",stdout);
	srand(time(0));
	int n=500000,m=100,q=500000;
	printf("%d %d %d\n",n,m,q);
	for(int i=2;i<=n;i++)
	{
		printf("%d %d\n",rand()%(i-1)+1,i);
	}
	memset(gr,false,sizeof(gr));
	for(int i=1;i<=m;i++)
	{
		int x=rand()%n+1;
		while(gr[x])x=rand()%n+1;
		gr[x]=true;
		printf("%d ",x);
	}
	putchar('\n');
	memset(fc,false,sizeof(fc));
	for(int i=1;i<=q;i++)
	{
		int c=rand()%4;
		if(c<=1)
		{
			int x=rand()%n+1;
			if(fc[x])printf("2 %d\n",x);
			else printf("1 %d\n",x);
		}
		else if(c==2)printf("3 %d\n",rand()%n+1);
		else printf("4\n");
	}
	return 0;
}