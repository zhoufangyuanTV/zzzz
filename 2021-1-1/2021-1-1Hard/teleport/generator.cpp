#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("teleport.in","w",stdout);
	int n=1000,m=1000;printf("%d %d\n",n,m);
	for(int i=2;i<=1000;i++)
	{
		printf("%d %d\n",i-1-(i&1),(rand()<<15|rand())%1000000000+1);
	}
	return 0;
}