#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("extension.in","r",stdin);
	freopen("extension.out","w",stdout);
	int n,s=0,ss=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		if(i&1)s^=x&1;
		else
		{
			if(x%(i+1)&1)ss^=1;
			else if(x%(i+1)==i)ss^=2;
		}
	}
	puts(s^ss?"tomato fish+1s":"rainy day+1s");
	return 0;
}