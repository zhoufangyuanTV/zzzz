#include<cstdio>
#include<cstring>
#include<algorithm>
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
int z,in[110000],out[110000],yss[110000],top[110000];
void dfs(int x,int tp)
{
	in[x]=++z;
	top[x]=tp;
	yss[z]=x;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
	}
	out[x]=z;
}
int fx,fy;
int lca(int x,int y)
{
	bool bx=false,by=false;
	int tx=top[x],ty=top[y];
	while(tx!=ty)
	{
		if(dep[tx]<dep[ty])
		{
			if(by==false)fy=fa[y];
			by=true;
			if(bx==false)fx=ty;
			y=fa[ty];ty=top[y];
		}
		else
		{
			if(bx==false)fx=fa[x];
			bx=true;
			if(by==false)fy=tx;
			x=fa[tx];tx=top[x];
		}
	}
	if(x==y)return x;
	else
	{
		if(dep[x]<dep[y])
		{
			if(by==false)fy=fa[y];
			by=true;
			if(bx==false)fx=yss[in[x]+1];
			return x;
		}
		else
		{
			if(bx==false)fx=fa[x];
			bx=true;
			if(by==false)fy=yss[in[y]+1];
			return y;
		}
	}
}
struct trnode
{
	int l,r,lc,rc,c,cc;
}tr[210000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=tr[now].cc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
inline int mymax(int x,int y){return x>y?x:y;}
void change(int now,int l,int r,int c)
{
	if(tr[now].l==l&&tr[now].r==r){tr[now].c+=c;tr[now].cc+=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c+=tr[now].cc;tr[lc].cc+=tr[now].cc;
	tr[rc].c+=tr[now].cc;tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	tr[now].c=mymax(tr[lc].c,tr[rc].c);
}
int findmax(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c+=tr[now].cc;tr[lc].cc+=tr[now].cc;
	tr[rc].c+=tr[now].cc;tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)return findmax(lc,l,r);
	else if(l>=mid+1)return findmax(rc,l,r);
	else return mymax(findmax(lc,l,mid),findmax(rc,mid+1,r));
}
struct Query
{
	int l,r,c,p;
}Q[2010000];int qlen;
inline bool cmp(Query x,Query y){return x.p<y.p;}
int g[110000],gg[110000];
int main()
{
	freopen("score.in","r",stdin);
	freopen("score.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	z=0;dfs(1,1);
	qlen=0;
	int ss=0;
	memset(g,0,sizeof(g));
	for(int i=1;i<=m;i++)
	{
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		if(x==y)
		{
			ss=ss+w;
			g[x]-=w;
		}
		else
		{
			int r=lca(x,y);
			if(r!=x&&r!=y)
			{
				Q[++qlen]=(Query){in[y],out[y],w,in[x]};
				Q[++qlen]=(Query){in[y],out[y],-w,out[x]+1};
			}
			else
			{
				if(r==x)
				{
					if(in[fx]>1)Q[++qlen]=(Query){in[y],out[y],w,1};
					if(in[fx]>1)Q[++qlen]=(Query){in[y],out[y],-w,in[fx]};
					Q[++qlen]=(Query){in[y],out[y],w,out[fx]+1};
				}
				else
				{
					if(in[fy]>1)Q[++qlen]=(Query){1,in[fy]-1,w,in[x]};
					if(in[fy]>1)Q[++qlen]=(Query){1,in[fy]-1,-w,out[x]+1};
					if(out[fy]<n)Q[++qlen]=(Query){out[fy]+1,n,w,in[x]};
					if(out[fy]<n)Q[++qlen]=(Query){out[fy]+1,n,-w,out[x]+1};
				}
			}
		}
	}
	memset(gg,0,sizeof(gg));
	for(int i=1;i<=n;i++)
	{
		if(g[i]!=0)
		{
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(y!=fa[i])gg[y]+=g[i];
			}
			if(in[i]>1)Q[++qlen]=(Query){1,in[i]-1,g[i],1};
			if(in[i]>1)Q[++qlen]=(Query){1,in[i]-1,-g[i],in[i]};
			if(in[i]>1)Q[++qlen]=(Query){1,in[i]-1,g[i],out[i]+1};
			if(out[i]<n)Q[++qlen]=(Query){out[i]+1,n,g[i],1};
			if(out[i]<n)Q[++qlen]=(Query){out[i]+1,n,-g[i],in[i]};
			if(out[i]<n)Q[++qlen]=(Query){out[i]+1,n,g[i],out[i]+1};
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(gg[i]!=0)
		{
			Q[++qlen]=(Query){in[i],out[i],gg[i],in[i]};
			Q[++qlen]=(Query){in[i],out[i],-gg[i],out[i]+1};
		}
	}
	sort(Q+1,Q+qlen+1,cmp);
	int j=1,sm=0xc0c0c0c0;
	bt(1,n);
	for(int i=1;i<=n;i++)
	{
		while(j<=qlen&&Q[j].p==i)
		{
			change(1,Q[j].l,Q[j].r,Q[j].c);
			j++;
		}
		sm=mymax(sm,findmax(1,1,n));
	}
	printf("%d\n",sm+ss);
	return 0;
}