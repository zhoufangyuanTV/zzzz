#include<cstdio>
#include<cstring>
using namespace std;
int zx[310000];
inline int fzx(int x){return x==zx[x]?x:zx[x]=fzx(zx[x]);}
struct node
{
	int x,y,p,next;
}a[610000];int len,last[310000];
inline void ins(int x,int y,int p)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].p=p;
	a[len].next=last[x];last[x]=len;
}
int v,c[310000];
long long f[310000];
int head[310000],tail[310000],p[610000];
void dfs(int x,int fa)
{
	f[x]=c[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			f[x]+=f[y]-v;
		}
	}
}
int main()
{
	int n,m;scanf("%d%d%d",&n,&m,&v);
	long long s=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		s+=c[i];
	}
	if(s/v<n-1)
	{
		puts("NO");
		return 0;
	}
	for(int i=1;i<=n;i++)zx[i]=i;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		int fx=fzx(x),fy=fzx(y);
		if(fx!=fy)
		{
			zx[fx]=fy;
			ins(x,y,i);ins(y,x,i);
		}
	}
	return 0;
}