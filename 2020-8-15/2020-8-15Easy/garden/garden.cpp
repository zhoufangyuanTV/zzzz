#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int log2[110000];int fx,fy,fc;
int fa[110000][18],dep[110000],dis[110000];
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x)
{
	for(int i=1;i<=log2[dep[x]];i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0]&&dep[y]!=-1&&dis[y]+a[k].c<dis[x])fx=x,fy=y,fc=a[k].c;
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0]&&dep[y]==-1)
		{
			fa[y][0]=x;
			dep[y]=dep[x]+1;
			dis[y]=dis[x]+a[k].c;
			dfs(y);
		}
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])x^=y^=x^=y;
	for(int i=log2[dep[x]-dep[y]];i>=0;i--)if(1<<i<=dep[x]-dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=log2[dep[x]];i>=0;i--)
	{
		if(1<<i<=dep[x]&&fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}
inline int d(int x,int y){return dis[x]+dis[y]-2*dis[lca(x,y)];}
int main()
{
	freopen("garden.in","r",stdin);
	freopen("garden.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	log2[0]=-1;fx=1;fy=1;fc=0;
	for(int i=1;i<=n;i++)log2[i]=log2[i/2]+1;
	memset(dep,-1,sizeof(dep));
	fa[1][0]=-1;dep[1]=0;dis[1]=0;dfs(1);
	int t;scanf("%d",&t);
	while(t--)
	{
		int x,y;scanf("%d%d",&x,&y);
		printf("%d\n",mymin(d(x,y),mymin(d(x,fx)+d(fy,y),d(x,fy)+d(fx,y))+fc));
	}
	return 0;
}