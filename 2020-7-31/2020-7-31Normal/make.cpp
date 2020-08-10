#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	//freopen("cheese.in","w",stdout);
	srand(time(0));
	int n=6;printf("%d\n",n);
	for(int i=2;i<=n;i++)
	{
		int f=rand()%(i-1)+1;
		printf("%d %d %d\n",f,i,rand()%100+1);
	}
	return 0;
}