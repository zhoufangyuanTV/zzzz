#include<cstdio>
#include<cstring>
using namespace std;
int a[110000];
long long c[110000];
int sta[110000],top;
int main()
{
	freopen("way.in","r",stdin);
	freopen("way.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,q;scanf("%d%d",&n,&q);
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		a[n]=0;
		memset(c,63,sizeof(c));
		int i;
		for(i=0;i<n;i++)if(a[i]==n+1)break;
		if(i<n)
		{
			top=1;sta[1]=i;
			for(int j=i+1;j!=i;j=(j+1)%n)
			{
				if(a[j]==n-1)
				{
					if(top>0)
					{
						int x=sta[top--];
						c[j]=c[x]=(j-x+n+1)%(n+1);
					}
				}
				else if(a[j]==n+1)sta[++top]=j;
			}
			for(int j=i+1;j!=i;j=(j+1)%n)
			{
				if(c[j]==0x3f3f3f3f3f3f3f3fll&&a[j]==n-1)
				{
					if(top>0)
					{
						int x=sta[top--];
						c[j]=c[x]=(j-x+n+1)%(n+1);
					}
				}
				else if(c[j]==0x3f3f3f3f3f3f3f3fll&&a[j]==n+1)sta[++top]=j;
			}
		}
		while(q--)
		{
			long long x;scanf("%lld",&x);
			if(a[x%n]==n-1&&x/n<c[x%n])printf("%d",n-1);
			else if(a[x%(n+1)]==n+1&&x/n<c[x%(n+1)])printf("%d",n+1);
			else printf("%d",n);
			if(q==0)printf("\n");
			else printf(" ");
		}
	}
	return 0;
}