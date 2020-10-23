#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	srand(time(0));
	int n=5;
	printf("%d\n",n);
	for(int i=1;i<n;i++)printf("%d ",rand()%100);
	printf("%d\n",rand()%100);
	return 0;
}