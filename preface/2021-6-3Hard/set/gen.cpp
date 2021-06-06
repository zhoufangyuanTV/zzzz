#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[210000];
int main()
{
	freopen("set.in","w",stdout);
	srand(time(0));
	int n=200000,k=200000;
	printf("%d %d\n",n,k);
	for(int i=1;i<=n;i++)printf("%d\n",rand()%/*10000000*/5+1);
	return 0;
}
