#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	srand(time(0));
	int t=5;printf("%d\n",t);
	while(t--)
	{
		int n=100000;printf("%d\n",n);
		for(int i=1;i<n;i++)printf("%d ",((rand()%(1<<10))<<10)+(rand()%(1<<10)));
		printf("%d\n",((rand()%(1<<10))<<10)+(rand()%(1<<10)));
		for(int i=2;i<=n;i++)printf("%d %d\n",rand()%(i-1)+1,i);
	}
}