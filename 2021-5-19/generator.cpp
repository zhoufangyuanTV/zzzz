#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("M.in","w",stdout);
	srand(time(0));
	int t=10;printf("%d\n",t);
	while(t--)
	{
		int n=rand()%9+3,m=rand()%9+3;
		int cnt1=rand()%(n*m-2)+1;
		int cnt2=rand()%(n*m-cnt1-1)+1;
		int cnt3=n*m-cnt1-cnt2;
		printf("%d %d\n%d %d %d\n",n,m,cnt1,cnt2,cnt3);
		int x1=rand()%n+1,y1=rand()%m+1;
		printf("%d %d\n",x1,y1);
		int x2=rand()%n+1,y2=rand()%m+1;
		while(x2==x1&&y2==y1)x2=rand()%n+1,y2=rand()%m+1;
		printf("%d %d\n",x2,y2);
		int x3=rand()%n+1,y3=rand()%m+1;
		while(x3==x1&&y3==y1||x3==x2&&y3==y2)x3=rand()%n+1,y3=rand()%m+1;
		printf("%d %d\n",x3,y3);
	}
	return 0;
}