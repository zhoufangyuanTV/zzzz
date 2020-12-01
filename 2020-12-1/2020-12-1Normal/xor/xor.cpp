#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<1<<n;i++)
	{
		for(int j=1;j<1<<m;j++)
		{
			putchar((i+j)&1?'0':'1');
		}
		putchar('\n');
	}
	return 0;
}
