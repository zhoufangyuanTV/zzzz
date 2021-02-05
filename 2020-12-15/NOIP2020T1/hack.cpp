#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
bool b[110];
int main()
{
	freopen("water.in","w",stdout);
	srand(time(0));
	printf("60 5\n");
	for(int i=1;i<=60;i++)
	{
		if(i>55){puts("0");continue;}
		int g=i%5==0?5:i%5;
		printf("%d",g);
		memset(b,false,sizeof(b));
		for(int j=1;j<=g;j++)
		{
			int x=((i-1)/5+1)*5+rand()%5+1;
			while(b[x])x=((i-1)/5+1)*5+rand()%5+1;
			b[x]=true;
			printf(" %d",x);
		}
		putchar('\n');
	}
	return 0;
}