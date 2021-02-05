#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int a,b,x,y;scanf("%d%d%d%d",&a,&b,&x,&y);
	if(2*x<y)y=2*x;
	if(a==b)printf("%d\n",x);
	else if(a<b)printf("%d\n",y*(b-a)+x);
	else if(a>b)printf("%d\n",y*(a-b-1)+x);
	return 0;
}