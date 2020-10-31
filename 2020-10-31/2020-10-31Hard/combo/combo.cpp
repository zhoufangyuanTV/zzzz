#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210];int len,last[110];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int p,dp;
int n,fa[110],son[110];
void dfs(int x,int d)
{
	if(dp<d)p=x,dp=d;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])fa[y]=x,dfs(y,d+1);
	}
}
int g,u[110];
int sp,pp[210];
void dfs(int x)
{
	pp[++sp]=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			dfs(y);
			u[++g]=x;pp[++sp]=n+g;
		}
	}
	if(son[x]!=0)dfs(son[x]);
}
int main()
{
	freopen("combo.in","r",stdin);
	freopen("combo.out","w",stdout);
	scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	dp=0;fa[1]=0;dfs(1,0);
	int st=p;dp=0;fa[p]=0;dfs(p,0);
	while(fa[p]!=0)son[fa[p]]=p,p=fa[p];
	g=0;sp=0;dfs(st);
	printf("%lld\n",g);
	for(int i=1;i<g;i++)printf("%d ",u[i]);
	printf("%d\n",u[g]);
	for(int i=1;i<sp;i++)printf("%d ",pp[i]);
	printf("%d\n",pp[sp]);
	return 0;
}