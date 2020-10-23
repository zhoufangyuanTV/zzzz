#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	srand(time(0));
	int n=3,k=rand()%(n<<1);
	printf("%d %d\n",n,k);
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<1<<i;j++)putchar(rand()%2+'0');
		putchar('\n');
	}
	return 0;
}