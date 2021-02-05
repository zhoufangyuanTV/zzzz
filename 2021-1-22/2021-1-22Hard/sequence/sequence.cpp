#include<cstdio>
#include<cstring>
using namespace std;
int p;
int n,a1,ar,a[110];
long long ss=0;
inline int mymin(int x,int y){return x<y?x:y;}
void dfs1(int k)
{
	if(k==n+1)
	{
		long long s=1;
		for(int i=1;i<=n;i++)s=s*(a[i-1]-a[i]+1)%p;
		ss=(ss+s)%p;
	}
	else
	{
		for(int i=mymin(a[k-1],ar);i>=0;i--)
		{
			a[k]=i;ar-=i;dfs1(k+1);ar+=i;
		}
	}
}
void dfs2(int k)
{
	if(k==n+1)
	{
		long long s=a[n]+1;
		for(int i=1;i<=n;i++)s=s*(a[i-1]-a[i]+1)%p;
		ss=(ss+s)%p;
	}
	else
	{
		for(int i=mymin(a[k-1],ar);i>=0;i--)
		{
			a[k]=i;ar-=i;dfs2(k+1);ar+=i;
		}
	}
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&p);
	if(n%2==1)
	{
		int ng=n;n=n/2;
		for(a1=1;a1<=ng;a1++)
		{
			a[0]=ng-a1;ar=a1-1;
			dfs1(1);
		}
	}
	else
	{
		int ng=n;n=n/2-1;
		for(a1=1;a1<=ng;a1++)
		{
			a[0]=ng-a1;ar=a1-1;
			dfs2(1);
		}
	}
	printf("%lld\n",ss);
	return 0;
}