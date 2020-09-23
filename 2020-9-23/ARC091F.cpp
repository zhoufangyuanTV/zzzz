#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n;scanf("%d",&n);
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		int x,k;scanf("%d%d",&x,&k);
		while(x%k!=0)
		{
			int dx=x/k+1;
			x=x-(x%k+dx-1)/dx*dx;
		}
		ss^=x/k;
	}
	printf(ss?"Takahashi\n":"Aoki\n");
	return 0;
}