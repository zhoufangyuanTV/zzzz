#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int x,y,xx,yy;scanf("%d%d%d%d",&x,&y,&xx,&yy);
	yy=-yy;
	printf("%.6lf\n",x+1.0*y/(y-yy)*(xx-x));
	return 0;
}