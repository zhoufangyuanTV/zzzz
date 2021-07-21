#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("sample.in","w",stdout);
	srand(time(0));
	int n=90000,m=89999,A=999999999,B=1000000000;
	int S=rand()%n+1,T=rand()%n+1;
	printf("%d %d %d %d %d %d\n",n,m,A,B,S,T);
	for(int i=1;i<n;i++)
	{
		printf("%d %d\n",i,rand()%i);
	}
	return 0;
}
