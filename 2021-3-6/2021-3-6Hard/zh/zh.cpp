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
			if(tot[son[x]]<tot[y])son[x]=y;
			if(tot[x]<tot[y]+1)tot[x]=tot[y]+1;
		}
	}
}
long long ss=0;
list<long long> f[1010000],g[1010000];
void dfs2(int x)
{}
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
	return 0;
}