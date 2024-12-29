#include<cstdio>
#include<cstring>
using namespace std;
int a[210];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		bool bk=false;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(i>1&&a[i-1]*2>a[i]&&a[i]*2>a[i-1])bk=true;
		}
		puts(bk?"YES":"NO");
	}
	return 0;
}