#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n,m,stx,sty,edx,edy;scanf("%d%d%d%d%d%d",&n,&m,&stx,&sty,&edx,&edy);
	if(stx==edx&&abs(edy-sty)==1||sty==edy&&abs(stx-edx)==1)
	{
		printf("-1\n");
		return 0;
	}
	if(edx<=2&&n-1<=edx&&edy<=2&&m-1<=edy)
	{
		printf("1\n");
		return 0;
	}
	if(n==2&&abs(edy-sty)>1||m==2&&abs(stx-edx)>1)
	{
		printf("2\n");
		return 0;
	}
	int ss=0;
	if(edx<=2)ss++;
	if(edy<=2)ss++;
	if(n-1<=edx)ss++;
	if(m-1<=edy)ss++;
	if(ss==3)
	{
		printf("2\n");
		return 0;
	}
	if(ss==2&&!((stx+1==edx||stx-1==edx)&&(sty+1==edy||sty-1==edy)))
	{
		printf("2\n");
		return 0;
	}
	printf("3\n");
	return 0;
}