#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
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
int n,fa[1010000],dep[1010000],son[1010000],tot[1010000];
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
int top[1010000];
void dfs(int x,int tp)
{
	top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
	}
}
bool ff[1010000];
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])y=fa[top[y]];
		else x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int m,col[1010000];
vector<int> c[110000];
bool b[110000];int cnt;
int f[1010000];
inline int mymax(int x,int y){return x>y?x:y;}
void tr(int x,bool bk)
{
	if(b[col[x]]!=bk){b[col[x]]=bk;cnt++;}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])tr(y,bk);
	}
}
void dfs(int x,bool bk)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			dfs(y,false);
			if(f[y]!=-1)f[x]=mymax(f[x],f[y]+1);
		}
	}
	if(son[x]!=0)
	{
		dfs(son[x],true);
		f[x]=mymax(f[x],f[son[x]]+1);
	}
	if(!b[col[x]]){cnt++;b[col[x]]=true;}
	if(cnt==m)f[x]=mymax(f[x],1);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])tr(y,true);
	}
	if(!bk){tr(x,false);cnt=0;}
}
int ss=0;
void treedp(int x,int fd)
{
	if(fd!=-1)fd++;
	if()ss=mymax(ss)
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{}
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",col[i]);
		c[col[i]].push_back(i);
	}
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs(1);dfs(1,1);
	memset(ff,true,sizeof(ff));
	for(int i=1;i<=m;i++)
	{
		int grand=c[i][0];
		for(int j=1;j<c[i].size();j++)grand=lca(grand,c[i][j]);
		for(;grand>0&&ff[grand];grand=fa[grand])ff[grand]=false;
	}
	dfs(1,false);
	return 0;
}