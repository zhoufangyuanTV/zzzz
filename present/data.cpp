#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("journey.in","w",stdout);
	srand(time(0));
	int n=10,t=rand()%(n/2)+1,l=rand()%(n/3)+1,r=l+rand()%(n/2);
	printf("%d %d %d %d\n",n,t,l,r);
	for(int i=1;i<=t;i++)printf("%d ",rand()%20-10);printf("\n");
	for(int i=2;i<=n;i++)
	{
		printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%t+1);
	}
	return 0;
}