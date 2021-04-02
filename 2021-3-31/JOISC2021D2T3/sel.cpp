#include<cstdio>
#include<cstring>
using namespace std;
char opt[110];
int main()
{
	freopen("result","r",stdin);
	scanf("%s",opt+1);
	if(strcmp(opt+1,"Accepted:")!=0)return 1;
	int n,m;scanf("%d%d",&n,&m);
	printf("%d %d\n",n,m);
	if(n==18&&m>300)return 1;
	return 0;
}