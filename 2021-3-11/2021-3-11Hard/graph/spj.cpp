#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
bool map[1100][1100];
int a[1100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		map[x][y]=map[y][x]=true;
	}
	int L;scanf("%d",&L);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(abs(a[i]-a[j])>=L/2)
			{
				if(map[i][j]==false)
				{
					printf("%d %d\n",i,j);
					return 0;
				}
			}
			else
			{
				if(map[i][j]==true)
				{
					printf("%d %d\n",j,i);
					return 0;
				}
			}
		}
	}
	printf("AC\n");
	return 0;
}