#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[210000];
int fa[210000];
int c,cnt[210000];
long long Ans[210000],to[210000];
void dfs(int k)
{
	if(k==n+1)
	{
		int s=0,x=n;
		while(x!=1)x=fa[x],s++;
		long long ss=0;
		int sg=s;
		for(int i=c;i>=1;i--)
		{
			if(sg<=cnt[i])
			{
				ss=ss+to[i]*sg;
				break;
			}
			else
			{
				ss=ss+cnt[i]*to[i];
				sg-=cnt[i];
			}
		}
		if(Ans[s]<ss)Ans[s]=ss;
	}
	else
	{
		for(int i=1;i<=c;i++)
		{
			if(k<=to[i])break;
			if(cnt[i]>0)
			{
				cnt[i]--;
				fa[k]=to[i];
				dfs(k+1);
				cnt[i]++;
			}
		}
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n*2-2;i++)scanf("%d",&a[i]);
	sort(a+1,a+n*2-1);
	c=0;a[0]=0;
	for(int i=1;i<=n*2-2;i++)
	{
		if(a[i-1]<a[i])to[++c]=a[i];
		cnt[c]++;
	}
	memset(Ans,-1,sizeof(Ans));
	dfs(2);
	for(int i=1;i<n-1;i++)printf("%lld ",Ans[i]);
	printf("%lld\n",Ans[n-1]);
	return 0;
}