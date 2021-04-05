#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int L2[110000];
int fa[110000][20],l[110000][20],r[110000][20];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
int d[110000],dep[110000];
void dfs(int x)
{
	for(int i=1;i<=L2[dep[x]];i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
		l[x][i]=mymin(l[x][i-1],l[fa[x][i-1]][i-1]);
		r[x][i]=mymax(r[x][i-1],r[fa[x][i-1]][i-1]);
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0])
		{
			fa[y][0]=1;
			dep[y]=dep[x]+1;
			d[y]=d[x]^a[k].c;
			l[y][0]=(k+1)/2;
			r[y][0]=(k+1)/2;
			dfs(y);
		}
	}
}
void lca(int x,int y)
{
	if(dep[x]<dep[y])x^=y^=x^=y;
	for(int i=L2[dep[x]-dep[y]];i>=0;i--)
	{
		if(1<<i<=dep[x]-dep[y])
		{
			x=fa[x][i];
		}
	}
	if(x==y)return x;
	for(int i=L2[dep[x]];i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
void l(int x,int k)
{
	int s=0x3f3f3f3f;
	for(int i=L2[k];i>=0;i--)
	{
		if((k|1<<i)==k)
		{
			x=fa[x][i];
		}
	}
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	return 0;
}
