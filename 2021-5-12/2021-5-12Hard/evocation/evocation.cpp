#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[110000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool v[110000];
int n,fa[110000],dep[110000],son[110000],tot[110000];
void dfs(int x)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		dep[y]=dep[x]+1;
		dfs(y);
		if(tot[son[x]]<tot[y])son[x]=y;
		tot[x]+=tot[y];
	}
}
int z,ys[110000],yss[110000],top[110000];
void dfs(int x,int tp)
{
	ys[x]=++z;yss[z]=x;top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=son[x])dfs(y,y);
	}
}
int block,blk[110000],bl[330],br[330];
int c[110000],cc[330],cnt[330][210000];
void pushdown(int B)
{
	for(int i=bl[B];i<=br[B];i++)
	{
		cnt[B][n+c[i]]=0;
		c[i]+=cc[B];
	}
	cc[B]=0;
}
void update(int B)
{
	for(int i=bl[B];i<=br[B];i++)if(v[yss[i]])cnt[B][n+c[i]]++;
}
int inc(int l,int r)
{
	int re=0;
	if(blk[l]==blk[r])
	{
		pushdown(blk[l]);
		for(int i=l;i<=r;i++)
		{
			if(v[yss[i]]&&c[i]==0)re++;
			c[i]++;
		}
		update(blk[l]);
	}
	else
	{
		pushdown(blk[l]);
		for(int i=l;i<=br[blk[l]];i++)
		{
			if(v[yss[i]]&&c[i]==0)re++;
			c[i]++;
		}
		update(blk[l]);
		pushdown(blk[r]);
		for(int i=bl[blk[r]];i<=r;i++)
		{
			if(v[yss[i]]&&c[i]==0)re++;
			c[i]++;
		}
		update(blk[r]);
		for(int i=blk[l]+1;i<blk[r];i++)
		{
			re+=cnt[i][n-cc[i]];
			cc[i]++;
		}
	}
	return re;
}
int dec(int l,int r)
{
	int re=0;
	if(blk[l]==blk[r])
	{
		pushdown(blk[l]);
		for(int i=l;i<=r;i++)
		{
			c[i]--;
			if(v[yss[i]]&&c[i]==0)re++;
		}
		update(blk[l]);
	}
	else
	{
		pushdown(blk[l]);
		for(int i=l;i<=br[blk[l]];i++)
		{
			c[i]--;
			if(v[yss[i]]&&c[i]==0)re++;
		}
		update(blk[l]);
		pushdown(blk[r]);
		for(int i=bl[blk[r]];i<=r;i++)
		{
			c[i]--;
			if(v[yss[i]]&&c[i]==0)re++;
		}
		update(blk[r]);
		for(int i=blk[l]+1;i<blk[r];i++)
		{
			cc[i]--;
			re+=cnt[i][n-cc[i]];
		}
	}
	return re;
}
int solve(int x,bool bk)
{
	int s=0;
	while(x>0)
	{
		if(bk)s+=inc(ys[top[x]],ys[x]);
		else s+=dec(ys[top[x]],ys[x]);
		x=fa[top[x]];
	}
	return s;
}
int main()
{
	freopen("evocation.in","r",stdin);
	freopen("evocation.out","w",stdout);
	int id;scanf("%d",&id);
	int m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	fa[1]=0;
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa[i]);
		ins(fa[i],i);
	}
	dep[1]=1;dfs(1);
	z=0;dfs(1,1);
	memset(v,true,sizeof(v));
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		c[ys[i]]=-x;
	}
	block=sqrt(n);
	for(int i=1;i<=n;i++)blk[i]=(i-1)/block+1;
	memset(cc,0,sizeof(cc));
	for(int i=1;i<=n;i++)cnt[blk[i]][n+c[i]]++;
	for(int i=1;i<=blk[n];i++)bl[i]=(i-1)*block+1,br[i]=i*block;
	br[blk[n]]=n;
	int ss=0;
	for(int i=1;i<=m;i++)
	{
		int x;scanf("%d",&x);
		if(v[x])cnt[blk[ys[x]]][n+c[ys[x]]]--;
		else cnt[blk[ys[x]]][n+c[ys[x]]]++;
		if(c[ys[x]]+cc[blk[ys[x]]]>0)
		{
			if(v[x])ss--;
			else ss++;
		}
		v[x]=!v[x];
		if(v[x])ss-=solve(x,false);
		else ss+=solve(x,true);
		printf("%d%c",ss,i==m?'\n':' ');
	}
	return 0;
}
