#include<cstdio>
#include<cstring>
#include<random>
using namespace std;
int main(int argc,char* argv[])
{
	unsigned seed;
	sscanf(argv[1],"%u",&seed);
	mt19937 r(seed);
	int n=r()%15+1,m=r()%(n*3+1);
	printf("%d %d\n",n,n+m);
	for(int i=1;i<n;i++)printf("%d ",(int)r()&1);
	printf("%d\n",(int)r()&1);
	for(int i=1;i<n;i++)printf("%d ",(int)r()&1);
	printf("%d\n",(int)r()&1);
	for(int i=0;i<n;i++)
	{
		int y=r()%n;
		printf("%d %d\n",i,y);
	}
	for(int i=0;i<m;i++)
	{
		int x=r()%n,y=r()%n;
		printf("%d %d\n",x,y);
	}
	return 0;
}