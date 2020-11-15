#include<cstdio>
#include<cstring>
using namespace std;
long long a[210000];
int main()
{
	int n,w;scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++)
	{
		int s,t,p;scanf("%d%d%d",&s,&t,&p);
		a[s]+=p;a[t]-=p;
	}
	if(a[0]>w)
	{
		printf("No\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		a[i]=a[i-1]+a[i];
		if(a[i]>w){printf("No\n");return 0;}
	}
	printf("Yes\n");
	return 0;
}