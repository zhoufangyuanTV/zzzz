#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
using namespace std;
struct node
{
	int x,y,next;
}a[610000];int len,last[310000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fa[310000],dep[310000],son[310000],tot[310000];
void dfs(int x)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
int top[310000];
void dfs(int x,int tp)
{
	top[x]=tp;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])dfs(y,y==son[x]?tp:y);
	}
}
struct Query{int x,p;};
int Ans[310000];
vector<Query> Q1[310000],Q2[310000],Q3[310000],Q4[310000];
map<int,int> M1,M2;
void QA(int x)
{
	M1[dep[x]+x]++;
	M2[dep[x]-x]++;
	for(vector<Query>::iterator it=Q1[x].begin();it!=Q1[x].end();it++)
	{
		int c=it->x;
		map<int,int>::iterator jt=M1.find(c);
		if(jt!=M1.end())Ans[it->p]+=jt->second;
	}
	for(vector<Query>::iterator it=Q2[x].begin();it!=Q2[x].end();it++)
	{
		int c=it->x;
		map<int,int>::iterator jt=M2.find(c);
		if(jt!=M2.end())Ans[it->p]+=jt->second;
	}
	for(vector<Query>::iterator it=Q3[x].begin();it!=Q3[x].end();it++)
	{
		int c=it->x;
		map<int,int>::iterator jt=M1.find(c);
		if(jt!=M1.end())Ans[it->p]-=jt->second;
	}
	for(vector<Query>::iterator it=Q4[x].begin();it!=Q4[x].end();it++)
	{
		int c=it->x;
		map<int,int>::iterator jt=M2.find(c);
		if(jt!=M2.end())Ans[it->p]-=jt->second;
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])QA(y);
	}
	if(--M1[dep[x]+x]==0)M1.erase(dep[x]+x);
	if(--M2[dep[x]-x]==0)M2.erase(dep[x]-x);
}
int main()
{
	freopen("query.in","r",stdin);
	freopen("query.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	dfs(1,1);
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		int xx=x,yy=y;
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]])y=fa[top[y]];
			else x=fa[top[x]];
		}
		int lca=dep[x]<dep[y]?x:y;
		x=xx;y=yy;
		int L=dep[x]+dep[y]-dep[lca]*2;
		Q1[x].push_back((Query){dep[x],i});
		Q2[y].push_back((Query){dep[y]-L,i});
		if(lca!=1)Q3[fa[lca]].push_back((Query){dep[x],i});
		Q4[lca].push_back((Query){dep[y]-L,i});
	}
	memset(Ans,0,sizeof(Ans));
	QA(1);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}