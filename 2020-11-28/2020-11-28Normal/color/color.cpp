#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int p[11000],s;
int n,m,col[11000];
void dfs(int k)
{
	if(k==n+1)
	{
		printf("%d\n",m);
		for(int i=1;i<n;i++)
		{
			printf("%d ",col[i]);
		}
		printf("%d\n",col[n]);
		exit(0);
	}
	else
	{
		for(int i=1;i<=m;i++)
		{
			bool bk=true;
			for(int j=1;j<=s&&p[j]<k;j++)
			{
				if(col[k-p[j]]==i){bk=false;break;}
			}
			if(bk)col[k]=i,dfs(k+1);
		}
	}
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d",&n);
	s=0;
	for(int i=1;i<=n;i++)
	{
		int sss=0;
		for(int j=1;j<=i;j++)if(i%j==0)sss++;
		if(sss==2)p[++s]=i;
	}
	m=1;
	dfs(1);
	m=2;
	dfs(1);
	m=3;
	dfs(1);
	printf("4\n");
	for(int i=1;i<n;i++)printf("%d ",(i-1)%4+1);
	printf("%d\n",(n-1)%4+1);
	return 0;
}