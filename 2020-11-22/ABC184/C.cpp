#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	int x,y,xx,yy;scanf("%d%d%d%d",&x,&y,&xx,&yy);
	if(x==xx&&y==yy)puts("0");
	else if(abs(x-xx)+abs(y-yy)<=3)puts("1");
	else if(abs(x-xx)==abs(y-yy))puts("1");
	else if((x+y)%2==(xx+yy)%2)puts("2");
	else
	{
		for(int i=-3;i<=3;i++)
		{
			for(int j=-3;j<=3;j++)
			{
				if(abs(i)+abs(j)>3)continue;
				int xr=x+i,yr=y+j;
				if(abs(xr-xx)==abs(yr-yy)||abs(xr-xx)+abs(yr-yy)<=3)
				{
					puts("2");
					return 0;
				}
			}
		}
		puts("3");
	}
	return 0;
}