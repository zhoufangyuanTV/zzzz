#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int f[51000],siz[51000];
inline int find(int x)
{
	while(x!=f[x])x=f[x];
	return x;
}
int Ans[51000];
namespace Alice
{
	struct edge
	{
		int x,y;
	}e[51000];
	struct node
	{
		int x,y,next;
	}a[110000];int len,last[51000];
	inline void ins(int x,int y)
	{
		len++;a[len].x=x;a[len].y=y;
		a[len].next=last[x];last[x]=len;
	}
	int block,blk[51000],ce[51000],cnt;
	int fa[51000];
	int sta[51000],top;
	void dfs(int x)
	{
		int t=top;
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa[x])
			{
				fa[y]=x;
				dfs(y);
				if(block<=top-t)
				{
					ce[++cnt]=x;
					while(top>t)blk[sta[top--]]=cnt;
				}
			}
		}
		sta[++top]=x;
	}
	int p[110000],plen,c[110000];
	inline void clean(int pp){for(int i=plen;i>pp;i--)f[p[i]]=p[i],siz[p[i]]=c[i];plen=pp;}
	int solve(int x,int y,bool bk)
	{
		int ss=0;
		int pp=plen;
		while(y!=x)
		{
			int fx=find(e[y].x),fy=find(e[y].y);
			if(fx!=fy)
			{
				ss++;
				plen++;p[plen]=fx;c[plen]=siz[fx];
				plen++;p[plen]=fy;c[plen]=siz[fy];
				if(siz[fx]<siz[fy])
				{
					f[fx]=fy;
					siz[fy]+=siz[fx];
				}
				else
				{
					f[fy]=fx;
					siz[fx]+=siz[fy];
				}
			}
			y=fa[y];
		}
		if(bk)clean(pp);
		return ss;
	}
}
namespace Bruno
{
	struct edge
	{
		int x,y;
	}e[51000];
	struct node
	{
		int x,y,next;
	}a[110000];int len,last[51000];
	inline void ins(int x,int y)
	{
		len++;a[len].x=x;a[len].y=y;
		a[len].next=last[x];last[x]=len;
	}
	int B,ss;
	void dfs(int x,int fa)
	{
		int fx=find(e[x].x),fy=find(e[x].y);
		int sx=siz[fx],sy=siz[fy];
		if(fx!=fy)
		{
			ss++;
			if(siz[fx]<siz[fy])
			{
				f[fx]=fy;
				siz[fy]+=siz[fx];
			}
			else
			{
				f[fy]=fx;
				siz[fx]+=siz[fy];
			}
		}
		if(B==Alice::blk[x])Ans[x]=ss+Alice::solve(Alice::ce[B],x,true);
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa)dfs(y,x);
		}
		if(fx!=fy)ss--;
		f[fx]=fx;f[fy]=fy;
		siz[fx]=sx;siz[fy]=sy;
	}
}
int main()
{
	freopen("camphor.in","r",stdin);
	freopen("camphor.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,m;scanf("%d%d",&n,&m);
		Alice::len=Bruno::len=0;
		for(int i=1;i<=n;i++)Alice::last[i]=Bruno::last[i]=0;
		for(int i=1;i<=m;i++)f[i]=i,siz[i]=1;
		for(int i=1;i<=n;i++)scanf("%d%d",&Alice::e[i].x,&Alice::e[i].y);
		for(int i=1;i<n;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			Alice::ins(x,y);Alice::ins(y,x);
		}
		for(int i=1;i<=n;i++)scanf("%d%d",&Bruno::e[i].x,&Bruno::e[i].y);
		for(int i=1;i<n;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			Bruno::ins(x,y);Bruno::ins(y,x);
		}
		Alice::block=2*sqrt(n);
		Alice::cnt=Alice::top=0;
		Alice::fa[1]=0;
		Alice::dfs(1);
		Alice::ce[++Alice::cnt]=0;
		while(Alice::top>0)Alice::blk[Alice::sta[Alice::top--]]=Alice::cnt;
		for(Bruno::B=1;Bruno::B<=Alice::cnt;Bruno::B++)
		{
			Alice::plen=0;
			Bruno::ss=Alice::solve(0,Alice::ce[Bruno::B],false);
			Bruno::dfs(1,0);
			Alice::clean(0);
		}
		for(int i=1;i<=n;i++)printf("%d\n",m-Ans[i]);
	}
	return 0;
}