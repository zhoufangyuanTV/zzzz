#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int ds[5100][5100],db[5100][5100];
void dfs(int x,int fa,int d)
{
	ds[x][d]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			db[(k+1)/2][d]++;
			dfs(y,x,d+1);
		}
	}
}
int dest;
int fa[1010000],dep[1010000];
void dfs(int x)
{
	if(dep[dest]<dep[x])dest=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
		}
	}
}
int li;
int cc(int x,int fa,int d)
{
	if(d>li)return 0;
	int re=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			re+=cc(y,x,d+1);
		}
	}
	return re;
}
int main()
{
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	int n,m,d;scanf("%d%d%d",&n,&m,&d);
	len=0;memset(last,0,sizeof(last));
	for(int i=2;i<=n;i++)
	{
		int fi;scanf("%d",&fi);
		ins(fi,i);ins(i,fi);
	}
	if(n==m)
	{
		dest=1;dep[1]=0;fa[1]=0;dfs(1);
		int rt=dest;dep[rt]=0;fa[rt]=0;dfs(rt);
		if(dep[dest]%2==0)
		{
			if(dep[dest]/2>d)
			{
				puts("0");
				return 0;
			}
			int x=dest;
			for(int i=1;i<=dep[dest]/2;i++)x=fa[x];
			li=d-dep[dest]/2;
			printf("%d\n",cc(x,0,0));
		}
		else
		{
			if(dep[dest]/2+1>d)
			{
				puts("0");
				return 0;
			}
			int x=dest;
			for(int i=1;i<=dep[dest]/2;i++)x=fa[x];
			int y=fa[x];
			li=d-dep[dest]/2-1;
			printf("%d\n",cc(x,y,0)+cc(y,x,0));
		}
		return 0;
	}
	for(int i=1;i<=n;i++)dfs(i,0,0);
	for(int i=1;i<=n;i++)for(int j=1;j<n;j++)ds[i][j]+=ds[i][j-1],db[i][j]+=db[i][j-1];
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		int l=0,r=n-1;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(m<=ds[i][mid])r=mid;
			else l=mid+1;
		}
		if(r<=d&&ss<ds[i][d-r])ss=ds[i][d-r];
	}
	for(int i=1;i<n;i++)
	{
		int x=a[i*2].x,y=a[i*2].y;
		int l=0,r=n-1;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(m<=db[i][mid])r=mid;
			else l=mid+1;
		}
		if(r<d&&ss<db[i][d-r-1])ss=db[i][d-r-1];
	}
	printf("%d\n",ss);
	return 0;
}