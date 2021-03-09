#include<cstdio>
#include<cstring>
#include<list>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fa[1010000],dep[1010000],son[1010000],tot[1010000];
void dfs1(int x)
{
	tot[x]=1;son[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs1(y);
			if(tot[son[x]]<tot[y])son[x]=y;
			if(tot[x]<tot[y]+1)tot[x]=tot[y]+1;
		}
	}
}
long long ss=0;
list<long long> f[1010000],g[1010000];
void dfs2(int x)
{
	f[x].push_back(1);
	if(son[x]!=0)
	{
		dfs2(son[x]);
		f[x].splice(f[x].end(),f[son[x]]);
		if(!g[son[x]].empty())
		{
			g[son[x]].pop_front();
			if(!g[son[x]].empty())ss+=g[son[x]].front();
		}
		g[x].splice(g[x].end(),g[son[x]]);
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			dfs2(y);
			f[y].push_front(0);
			if(!g[y].empty())g[y].pop_front();
			list<long long>::iterator it=f[x].begin(),jt=f[y].begin(),kt=g[x].begin(),lt=g[y].begin();
			while(jt!=f[y].end()||lt!=g[y].end())
			{
				if(it==f[x].end())it=f[x].insert(it,0);
				if(kt==g[x].end())kt=g[x].insert(kt,0);
				long long fi=*it,gi=*kt;
				if(jt!=f[y].end())
				{
					*it+=*jt;
					*kt+=fi**jt;
					ss+=gi**jt;
					jt++;
				}
				if(lt!=g[y].end())
				{
					*kt+=*lt;
					ss+=fi**lt;
					lt++;
				}
				it++;kt++;
			}
		}
	}
}
int main()
{
	freopen("zh.in","r",stdin);
	freopen("zh.out","w",stdout);
	int n;read(n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs1(1);
	dfs2(1);
	printf("%lld\n",ss);
	return 0;
}