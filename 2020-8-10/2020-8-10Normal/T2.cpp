#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,fa[110000],dep[110000],son[110000],tot[110000];
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
int z,ys[110000],yss[110000],top[110000];
void dfs(int x,int tp)
{
	ys[x]=++z;yss[z]=x;top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
	}
}
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
struct val{int minc,maxc,up,down;};
inline val operator+(val x,val y){return (val){mymin(x.minc,y.minc),mymax(x.maxc,y.maxc),mymax(mymax(x.up,y.up),y.maxc-x.minc),mymax(mymax(x.down,y.down),x.maxc-y.minc)};}
struct trnode
{
	int l,r,lc,rc;
	val c;
}tr[210000];int trlen;
int v[110000];
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
		tr[now].c=tr[tr[now].lc].c+tr[tr[now].rc].c;
	}
	else tr[now].c=(val){v[yss[l]],v[yss[l]],0,0};
}
val findval(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return findval(lc,l,r);
	else if(l>=mid+1)return findval(rc,l,r);
	else return findval(lc,l,mid)+findval(rc,mid+1,r);
}
int solve(int x,int y)
{
	int tx=top[x],ty=top[y];val ls=(val){100000,0,0,0},rs=(val){100000,0,0,0};
	while(tx!=ty)
	{
		if(dep[tx]<dep[ty])
		{
			val s=findval(1,ys[ty],ys[y]);
			rs=s+rs;
			y=fa[ty];ty=top[y];
		}
		else
		{
			val s=findval(1,ys[tx],ys[x]);
			s.up^=s.down^=s.up^=s.down;
			ls=ls+s;
			x=fa[tx];tx=top[x];
		}
	}
	if(dep[x]<dep[y])return (ls+findval(1,ys[x],ys[y])+rs).up;
	else
	{
		val s=findval(1,ys[y],ys[x]);
		s.up^=s.down^=s.up^=s.down;
		return (ls+s+rs).up;
	}
}
struct Question{int opt,x,y;}Q[110000];
int main()
{
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	len=0;memset(last,0,sizeof(last));
	int rt;
	for(int i=1;i<m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);rt=y;
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d",&Q[i].opt,&Q[i].x,&Q[i].y);
		if(Q[i].opt==1)ins(Q[i].x,Q[i].y),ins(Q[i].y,Q[i].x);
	}
	fa[rt]=0;dep[rt]=1;dfs(rt);
	z=0;dfs(rt,rt);
	trlen=0;bt(1,z);
	for(int i=1;i<=q;i++)
	{
		if(Q[i].opt==0)printf("%d\n",solve(Q[i].x,Q[i].y));
	}
	return 0;
}