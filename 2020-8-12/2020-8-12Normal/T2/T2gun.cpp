#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
inline int longrand(){return (rand()&1)<<30|rand()<<15|rand();}
int main()
{
	srand(time(0));
	int n=250000;printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		printf("%d %d %d\n",longrand()%2000000001-1000000000,longrand()%2000000001-1000000000,rand()%2);
	}
	return 0;
}