#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[6100];int len,last[3100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fa[3100],z,in[3100],out[3100],tot[3100];
void dfs(int x)
{
	in[x]=++z;
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dfs(y);
			tot[x]+=tot[y];
		}
	}
	out[x]=z;
}
bool ori[110][110],ne[110][110];
int ban;
bool b[110];
void dfs1(int x)
{
	if(x==ban)return ;
	b[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]==false)dfs1(y);
	}
}
int xx,yy;
void dfs2(int x)
{
	if(x==ban)return ;
	b[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]==false)dfs2(y);
	}
	if(x==xx&&b[yy]==false)dfs2(yy);
}
int main()
{
	freopen("dominator.in","r",stdin);
	freopen("dominator.out","w",stdout);
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);
	}
	if(m==n-1)
	{
		z=0;fa[1]=0;dfs(1);
		for(int i=1;i<=q;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			if(x!=y)
			{
				if(in[x]<=in[y]&&in[y]<=out[x])
				{
					if(fa[y]==x)puts("0");
					else printf("%d\n",tot[y]);
				}
				else if(in[y]<=in[x]&&in[x]<=out[y])puts("0");
				else
				{
					int f=fa[y];
					if(in[f]<=in[x]&&in[x]<=out[f])puts("0");
					else printf("%d\n",tot[y]);
				}
			}
			else puts("0");
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		ban=i;
		memset(b,false,sizeof(b));
		dfs1(1);
		for(int j=1;j<=n;j++)ori[i][j]=!b[j];
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&xx,&yy);
		for(int i=1;i<=n;i++)
		{
			ban=i;
			memset(b,false,sizeof(b));
			dfs2(1);
			for(int j=1;j<=n;j++)ne[i][j]=!b[j];
		}
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			bool bk=false;
			for(int j=1;j<=n;j++)if(ne[j][i]!=ori[j][i]){bk=true;break;}
			ss+=bk;
		}
		printf("%d\n",ss);
	}
	return 0;
}
