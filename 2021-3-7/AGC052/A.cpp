#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d%*s%*s%*s",&n);
		for(int i=1;i<=n;i++)putchar('0');
		for(int i=1;i<=n;i++)putchar('1');
		puts("0");
	}
	return 0;
}