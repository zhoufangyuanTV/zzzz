#include<cstdio>
using namespace std;
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int x,m;scanf("%d%d",&x,&m);
		int s=0;
		for(int i=1;i<=2*x&&i<=m;i++)
		{
			if(i!=x)
			{
				if(x%(x^i)==0||i%(x^i)==0)s++;
			}
		}
		printf("%d\n",s);
	}
	return 0;
}