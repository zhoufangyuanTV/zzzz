#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
long long Ans=0;
struct node
{
	int x,y,next;
}a[2100];int len,last[1100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int z,dfn[1100],low[1100];
int cnt;vector<int> E[1100];
int sta[1100],top;
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++z;sta[++top]=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(dfn[y]==0)
			{
				dfs(y,x);
				if(dfn[x]<=low[y])
				{
					cnt++;
					while(sta[top]!=y)
					{
						E[cnt].push_back(sta[top]);
						E[sta[top]].push_back(cnt);
						top--;
					}
					top--;
					E[cnt].push_back(y);
					E[y].push_back(cnt);
					E[cnt].push_back(x);
					E[x].push_back(cnt);
				}
				else low[x]=mymin(low[x],low[y]);
			}
			else low[x]=mymin(low[x],dfn[y]);
		}
	}
}
inline int lowbit(int x){return x&-x;}
int n,f[1100];
void change(int x,int c)
{
	while(x<=n)
	{
		f[x]=(f[x]+c)%998244353;
		x=x+lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s=(s+f[x])%998244353;
		x=x-lowbit(x);
	}
	return s;
}
int g[1100],ff[1100],fff[1100];
void treedp(int x,int fa)
{
	if(x>n)
	{
		int i,m=E[x].size();
		for(i=0;i<m;i++)if(E[x][i]==fa)break;
		for(int j=(i+1)%m;j!=i;j=(j+1)%m)g[E[x][j]]=sum(E[x][j]);
		for(int j=(i-1+m)%m;j!=i;j=(j-1+m)%m)
		{
			int y=E[x][j];
			ff[y]=sum(y);
			change(y,ff[y]);
		}
		for(int j=(i-1+m)%m;j!=i;j=(j-1+m)%m)change(E[x][j],998244353-ff[E[x][j]]);
		for(int j=(i+1)%m;j!=i;j=(j+1)%m)
		{
			int y=E[x][j];
			fff[y]=sum(y);
			change(y,fff[y]);
		}
		for(int j=(i-1+m)%m;j!=i;j=(j-1+m)%m)
		{
			int y=E[x][j];
			Ans=(Ans+ff[y]+fff[y]-g[y]+998244353)%998244353;
			change(y,(ff[y]-g[y]+998244353)%998244353);
			treedp(y,x);
			change(y,(g[y]-fff[y]+998244353)%998244353);
		}
		for(int j=(i-1+m)%m;j!=i;j=(j-1+m)%m)change(E[x][j],998244353-ff[E[x][j]]);
	}
	else
	{
		for(int i=0;i<E[x].size();i++)
		{
			int y=E[x][i];
			if(y!=fa)
			{
				if(y<=n)
				{
					g[y]=sum(y);
					Ans=(Ans+g[y])%998244353;
					change(y,g[y]);
				}
				treedp(y,x);
				if(y<=n)change(y,998244353-g[y]);
			}
		}
	}
}
int main()
{
	freopen("algebra.in","r",stdin);
	freopen("algebra.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(dfn,0,sizeof(dfn));
	z=top=0;cnt=n;dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		change(i,1);
		Ans=(Ans+1)%998244353;
		treedp(i,0);
	}
	printf("%lld\n",Ans);
	return 0;
}