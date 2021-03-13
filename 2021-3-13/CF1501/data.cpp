#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	int n=200000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",(rand()<<15|rand())%2500000+1);
	}
	return 0;
}