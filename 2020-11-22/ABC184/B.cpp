#include<cstdio>
#include<cstring>
using namespace std;
char s[210000];
int main()
{
	int n,x;scanf("%d%d%s",&n,&x,s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='x')
		{
			if(x>0)x--;
		}
		else x++;
	}
	printf("%d\n",x);
	return 0;
}