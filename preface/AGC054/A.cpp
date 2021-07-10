#include<cstdio>
#include<cstring>
using namespace std;
char a[110000];
int main()
{
	int n;scanf("%d%s",&n,a+1);
	if(a[1]!=a[n])
	{
		puts("1");
		return 0;
	}
	for(int i=2;i<n;i++)
	{
		if(a[i]!=a[1]&&a[i+1]!=a[n])
		{
			puts("2");
			return 0;
		}
	}
	puts("-1");
	return 0;
}