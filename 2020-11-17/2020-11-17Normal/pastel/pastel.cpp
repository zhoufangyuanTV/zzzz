#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
namespace SegmentTree
{
	struct node
	{
		int l,r,lc,rc;
		unsigned w,wc;
	}tr[610000];int len;
	void bt(int l,int r)
	{
		len++;int now=len;
		tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].w=tr[now].wc=0;
		if(l<r)
		{
			int mid=(l+r)/2;
			tr[now].lc=len+1;bt(l,mid);
			tr[now].rc=len+1;bt(mid+1,r);
		}
	}
	void change(int now,int l,int r,unsigned w)
	{
		if(tr[now].l==l&&tr[now].r==r)
		{
			tr[now].w+=w;
			tr[now].wc+=w*(tr[now].r-tr[now].l+1);
			return ;
		}
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		tr[lc].w+=tr[now].w;
		tr[lc].wc+=tr[now].w*(tr[lc].r-tr[lc].l+1);
		tr[rc].w+=tr[now].w;
		tr[rc].wc+=tr[now].w*(tr[rc].r-tr[rc].l+1);
		tr[now].w=0;
		if(r<=mid)change(lc,l,r,w);
		else if(l>=mid+1)change(rc,l,r,w);
		else change(lc,l,mid,w),change(rc,mid+1,r,w);
		tr[now].wc=tr[lc].wc+tr[rc].wc;
	}
	unsigned sum(int now,int l,int r)
	{
		if(tr[now].l==l&&tr[now].r==r)return tr[now].wc;
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		tr[lc].w+=tr[now].w;
		tr[lc].wc+=tr[now].w*(tr[lc].r-tr[lc].l+1);
		tr[rc].w+=tr[now].w;
		tr[rc].wc+=tr[now].w*(tr[rc].r-tr[rc].l+1);
		tr[now].w=0;
		if(r<=mid)return sum(lc,l,r);
		else if(l>=mid+1)return sum(rc,l,r);
		else return sum(lc,l,mid)+sum(rc,mid+1,r);
	}
	inline void change(int now,int x,unsigned w){change(now,x,x,w);}
	inline unsigned sum(int now,int x){return sum(now,x,x);}
}
namespace treap
{
	struct node
	{
		int f,l,r,c,randc;
		unsigned w,wc,key,size;
	}tr[310000];
	inline void update(int x)
	{
		if(tr[x].l!=0)tr[tr[x].l].f=x;
		if(tr[x].r!=0)tr[tr[x].r].f=x;
		tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
		tr[x].wc=tr[tr[x].l].wc+tr[tr[x].r].wc+tr[x].key;
	}
	inline void pushdown(int x)
	{
		if(tr[x].w==0)return ;
		SegmentTree::change(1,tr[x].c,tr[x].w*(1-tr[x].size));
		if(tr[x].l!=0)
		{
			SegmentTree::change(1,tr[tr[x].l].c,tr[x].w*tr[tr[x].l].size);
			tr[tr[x].l].w+=tr[x].w;
			tr[tr[x].l].wc+=tr[x].w*tr[tr[x].l].size;
			tr[tr[x].l].key+=tr[x].w;
		}
		if(tr[x].r!=0)
		{
			SegmentTree::change(1,tr[tr[x].r].c,tr[x].w*tr[tr[x].r].size);
			tr[tr[x].r].w+=tr[x].w;
			tr[tr[x].r].wc+=tr[x].w*tr[tr[x].r].size;
			tr[tr[x].r].key+=tr[x].w;
		}
		tr[x].w=0;
	}
	void split(int now,int c,int &x,int &y)
	{
		if(now==0)x=y=0;
		else
		{
			pushdown(now);
			if(c<tr[now].c)
			{
				y=now;split(tr[now].l,c,x,tr[y].l);
			}
			else
			{
				x=now;split(tr[now].r,c,tr[x].r,y);
			}
			update(now);
		}
	}
	int merge(int x,int y)
	{
		if(x==0||y==0)return x+y;
		if(tr[x].randc<tr[y].randc)
		{
			pushdown(x);
			tr[x].r=merge(tr[x].r,y);
			update(x);
			return x;
		}
		else
		{
			pushdown(y);
			tr[y].l=merge(x,tr[y].l);
			update(y);
			return y;
		}
	}
	inline int findroot(int x)
	{
		while(tr[x].f!=0)x=tr[x].f;
		return x;
	}
}
struct node
{
	int x,y,next;
}a[310000];int len,last[310000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int z,in[310000],out[310000];
void dfs(int x)
{
	in[x]=++z;
	treap::tr[x]=(treap::node){0,0,0,z,rand(),0,0,0,1};
	if(x!=1)treap::merge(1,x);
	for(int k=last[x];k>0;k=a[k].next)dfs(a[k].y);
	out[x]=z;
}
int fi[310000],col[310000];
int main()
{
	freopen("pastel.in","r",stdin);
	freopen("pastel.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fi[i]);
		ins(fi[i],i);
	}
	SegmentTree::bt(1,n);
	z=0;dfs(1);
	memset(col,0,sizeof(col));col[1]=1;
	for(int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if(opt==1)
		{
			int x;scanf("%d",&x);
			int a,b,c,d;
			treap::split(treap::findroot(x),in[x],a,b);
			treap::tr[a].f=treap::tr[b].f=0;
			treap::split(a,in[x]-1,c,d);
			treap::tr[c].f=treap::tr[d].f=0;
			printf("%u\n",SegmentTree::sum(1,in[x]));
			treap::merge(c,treap::merge(d,b));
		}
		else if(opt==2)
		{
			int x;unsigned w;scanf("%d%u",&x,&w);
			int rt=treap::findroot(x);
			SegmentTree::change(1,in[rt],w*treap::tr[rt].size);
			treap::tr[rt].w+=w;
			treap::tr[rt].wc+=w*treap::tr[rt].size;
			treap::tr[rt].key+=w;
		}
		else if(opt==3)
		{
			int x;scanf("%d",&x);
			int a,b,c,d;
			treap::split(treap::findroot(x),out[x],a,b);
			treap::tr[a].f=treap::tr[b].f=0;
			treap::split(a,in[x]-1,c,d);
			treap::tr[c].f=treap::tr[d].f=0;
			printf("%u\n",SegmentTree::sum(1,in[x],out[x]));
			treap::merge(c,treap::merge(d,b));
		}
		else if(opt==4)
		{
			int x;unsigned w;scanf("%d%u",&x,&w);
			SegmentTree::change(1,in[x],out[x],w);
			if(col[x]==0)
			{
				int a,b,c,d;
				treap::split(treap::findroot(x),out[x],a,b);
				treap::tr[a].f=treap::tr[b].f=0;
				treap::split(a,in[x]-1,c,d);
				treap::tr[c].f=treap::tr[d].f=0;
				int rt=treap::findroot(c);
				SegmentTree::change(1,in[rt],-w*treap::tr[rt].size);
				treap::tr[rt].w-=w;
				treap::tr[rt].wc-=w*treap::tr[rt].size;
				treap::tr[rt].key-=w;
				treap::merge(c,treap::merge(d,b));
			}
		}
		else if(opt==5)
		{
			int x;scanf("%d",&x);col[x]=1;
			int a,b,c,d;
			treap::split(treap::findroot(x),out[x],a,b);
			treap::tr[a].f=treap::tr[b].f=0;
			treap::split(a,in[x]-1,c,d);
			treap::tr[c].f=treap::tr[d].f=0;
			treap::merge(c,b);
		}
		else
		{
			int x;scanf("%d",&x);col[x]=0;
			int a,b;
			treap::split(treap::findroot(fi[x]),out[fi[x]],a,b);
			treap::tr[a].f=treap::tr[b].f=0;
			treap::merge(treap::merge(a,treap::findroot(x)),b);
		}
	}
	return 0;
}