#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
void read(int &x)
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
int top[1010000],p[1010000],s[1010000];
int m,f[1010000],pf[1010000],sf[1010000],c[1010000];
map<int,int> G[1010000];
inline int mymax(int x,int y){return x>y?x:y;}
void dfs(int x,int tp)
{
	top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			dfs(y,y);
			for(map<int,int>::iterator it=G[y].begin();it!=G[y].end();it++)G[tp][it->first]+=it->second;
		}
	}
	G[tp][c[x]]++;
	f[x]=m==G[tp].size()?1:-1;
	int z=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			pf[y]=f[y]==-1?-1:f[y]+1;
			if(z!=0)
			{
				p[y]=z;s[z]=y;
				pf[y]=mymax(pf[y],pf[z]);
			}
			z=y;
		}
	}
	int y=0;
	while(z>0)
	{
		sf[z]=f[z]==-1?-1:f[z]+1;
		if(y!=0)sf[z]=mymax(sf[z],sf[y]);
		y=z;z=p[z];
	}
}
void dfs(int x,int F,map<int,int> H)
{
	map<int,int> M;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			for(map<int,int>::iterator it=G[y].begin();it!=G[y].end();it++)
			{
				if((G[top[x]][it->first]-=it->second)==0)G[top[x]].erase(it->first);
				M[it->first]+=it->second;
			}
			int ff=F;
			if(p[y]!=0)ff=mymax(ff,pf[p[y]]);
			if(s[y]!=0)ff=mymax(ff,sf[s[y]]);
			dfs(y,ff,G[top[x]]);
			for(map<int,int>::iterator it=G[y].begin();it!=G[y].end();it++)G[top[x]][it->first]+=it->second;
		}
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	return 0;
}