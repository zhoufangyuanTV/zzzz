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
	if(n>m)
	{
		n^=m^=n^=m;
		stx^=sty^=stx^=sty;
		edx^=edy^=edx^=edy;
	}
	if(n==1)
	{
		printf("2\n");
		return 0;
	}
	if(n==2)
	{
		printf("%d",m==2?1:2);
		return 0;
	}
	if(n==3)
	{
		if(m==3&&stx==2&&sty==2)
		{
			printf("%d",1);
			return 0;
		}
	}
	int ss=4;
	if(abs(stx-edx)==1&&abs(sty-edy)==1)ss++;
	if(edx==1||edx==2)ss--;
	if(edx==n-1||edx==n)ss--;
	if(edy==1||edy==2)ss--;
	if(edy==m-1||edy==m)ss--;
	if(ss<2)ss=2;
	if(stx==1&&sty==1||stx==1&&sty==m||stx==n&&sty==1||stx==n&&sty==m)
	{
		if(3<ss)ss=3;
	}
	if(n<ss)ss=n;
	printf("%d\n",ss);
	return 0;
}