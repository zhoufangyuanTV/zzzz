#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[110];
int main()
{
	srand(time(0));
	int n=10+rand()%2,m=100;printf("%d %d\n",n,m);
	int g=rand()%(n+1);
	for(int i=1;i<=g;i++)printf("%d ",a[i]=i);
	for(int i=g+1;i<=n;i++)printf("%d ",a[i]=50+i);
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		bool bk=rand()%2;
		printf("%d ",bk?2*a[i]:2*m-2*a[i]);
	}
	return 0;
}