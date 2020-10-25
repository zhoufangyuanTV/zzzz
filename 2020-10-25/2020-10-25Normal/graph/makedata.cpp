#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
bool map[410][410];
int main()
{
	srand(time(0));
	freopen("graph.in","w",stdout);
	int n=400,m=rand()%(n*(n-1)/64-n+2)+n-1,s=rand()%n+1,t=rand()%n+1;
	printf("%d %d %d %d\n",n,m,s,t);
	memset(map,false,sizeof(map));
	for(int i=1;i<=m;i++)
	{
		int x=rand()%n+1,y=rand()%n+1;
		while(x==y||map[x][y]==true)x=rand()%n+1,y=rand()%n+1;
		map[x][y]=map[y][x]=true;
		printf("%d %d\n",x,y);
	}
	return 0;
}