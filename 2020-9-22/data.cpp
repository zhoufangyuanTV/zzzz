#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
bool b[11000];
int main()
{
	srand(time(0));
	int k=11,p=10007;printf("%d %d\n",k,p);
	int n=rand()%3+2;printf("%d\n",n);
	for(int i=1;i<=n;i++)printf("%d\n",rand()%10);
	int m=rand()%4;printf("%d\n",m);
	memset(b,false,sizeof(b));
	for(int i=1;i<=m;i++)
	{
		int j=rand()%(k-n+2)+n;
		while(b[j]==true)j=rand()%(k-n+2)+n;
		b[j]=true;
		int v=rand()%10;
		printf("%d %d\n",j,v);
	}
	return 0;
}