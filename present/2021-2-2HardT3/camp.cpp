#include<cstdio>
#include<cstring>
using namespace std;
int c[1100];
int n,a[1100],ss=0;
void dfs(int k)
{
	if(k>ss+1)
	{
		ss=k-1;
		for(int i=1;i<ss;i++)printf("%d ",c[i]=a[i]);
		printf("%d\n",c[ss]=a[ss]);
	}
	for(int i=1;i<=n;i++)
	{
		bool bk=true;
		for(int j=1;j<k;j++)
		{
			if(a[j]==i&&a[k-j]==i){bk=false;break;}
		}
		if(bk){a[k]=i;dfs(k+1);}
	}
}
int main()
{
	scanf("%d",&n);
	dfs(1);
	return 0;
}