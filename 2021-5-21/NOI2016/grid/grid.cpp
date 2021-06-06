#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
	int x,y,next;
}e[8010000];int len,last[2010000];
inline void ins(int x,int y)
{
	len++;e[len].x=x;e[len].y=y;
	e[len].next=last[x];last[x]=len;
}
bool gedian;
int z,dfn[2010000],low[2010000];
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++z;
	int sons=0;
	bool bk=true;
	for(int k=last[x];k>0;k=e[k].next)
	{
		int y=e[k].y;
		if(y!=fa)
		{
			if(dfn[y]==0)
			{
				sons++;
				dfs(y,x);
				low[x]=mymin(low[x],low[y]);
				if(dfn[x]<=low[y])bk=false;
			}
			else low[x]=mymin(low[x],dfn[y]);
		}
	}
	if(fa==0)
	{
		if(sons>1)gedian=true;
	}
	else
	{
		if(bk==false)gedian=true;
	}
}
struct node
{
	int x,y;
}a[110000];
inline bool cmp1(node x,node y){return x.x<y.x;}
inline bool cmp2(node x,node y){return x.y<y.y;}
bool b[2010000];
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m,c;scanf("%d%d%d",&n,&m,&c);
		for(int i=1;i<=c;i++)scanf("%d%d",&a[i].x,&a[i].y);
		sort(a+1,a+c+1,cmp1);
		int N=0;a[0].x=0;a[c+1].x=n+1;
		for(int i=1;i<=c+1;i++)
		{
			int delta=a[i].x-a[i-1].x;
			a[i-1].x=N;
			if(delta>3)delta=4;
			N+=delta;
		}
		N--;
		sort(a+1,a+c+1,cmp2);
		int M=0;a[0].y=0;a[c+1].y=m+1;
		for(int i=1;i<=c+1;i++)
		{
			int delta=a[i].y-a[i-1].y;
			a[i-1].y=M;
			if(delta>3)delta=4;
			M+=delta;
		}
		M--;
		swap(n,N);swap(m,M);
		for(int i=1;i<=n*m;i++)b[i]=true;
		for(int i=1;i<=c;i++)b[(a[i].x-1)*m+a[i].y]=false;
		len=0;
		for(int i=1;i<=n*m;i++)last[i]=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				int x=(i-1)*m+j;
				if(b[x])
				{
					if(i>1)
					{
						int y=(i-2)*m+j;
						if(b[y])ins(x,y),ins(y,x);
					}
					if(j>1)
					{
						int y=(i-1)*m+j-1;
						if(b[y])ins(x,y),ins(y,x);
					}
				}
			}
		}
		for(int i=1;i<=n*m;i++)dfn[i]=0;
		z=0;
		int cnt=0;gedian=false;
		for(int i=1;i<=n*m;i++)
		{
			if(b[i])
			{
				if(dfn[i]==0)
				{
					cnt++;
					if(cnt>1)break;
					dfs(i,0);
				}
			}
		}
		if(cnt>1)puts("0");
		else
		{
			if(1ll*N*M-c<=2)puts("-1");
			else if(gedian)puts("1");
			else puts("2");
		}
	}
	return 0;
}
