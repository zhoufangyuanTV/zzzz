#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("array.in","w",stdout);
	srand(time(0));
	int t=5;printf("%d\n",t);
	while(t--)
	{
		int n=100000,m=200,k=1,d=(rand()<<15|rand())%1000000000;
		printf("%d %d %d %d\n",n,m,k,d);
		for(int i=1;i<m;i++)printf("%d ",rand()%5000+1);
		printf("%d\n",rand()%5000+1);
	}
	return 0;
}