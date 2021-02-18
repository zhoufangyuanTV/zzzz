#include<cstdio>
#include<cstring>
using namespace std;
int f[25000];
int main()
{
	freopen("fib.in","r",stdin);
	freopen("fib.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&f[0],&f[1]);
		int p=-1;
		for(int j=0;j<=24*(m+1);j++)
		{
			if(j>=2)f[j]=(f[j-1]+f[j-2])%m;
			if(f[j]==0){p=j;break;}
		}
		printf("%d\n",p);
	}
	return 0;
}
