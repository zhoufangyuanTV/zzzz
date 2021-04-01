#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("g.in","w",stdout);
	srand(time(0));
	int n=10,k=7;printf("1\n%d %d\n",n,k);
	for(int i=0;i<=k;i++)printf("%d %d\n",rand()%(n-2)+1,rand()%(n-2)+1);
	return 0;
}