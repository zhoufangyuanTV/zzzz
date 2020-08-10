#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int n,fa[210000],dep[210000],son[210000],tot[210000];
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
			if(tot[son[x]]<tot[y])son[x]=y,tot[x]=tot[y]+1;
		}
	}
}
int z,ys[210000],top[210000],sonc[210000];
void dfs(int x,int tp)
{
	ys[x]=++z;top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			if(y==son[x])sonc[x]=a[k].c;
			else dfs(y,y);
		}
	}
}
int c[210000];
struct key{int col,val;};
struct trnode
{
	int l,r,lc,rc;
	key c,cc;
	int ccc;
	int bk;
}tr[410000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=tr[now].cc=(key){0,(int)-1061109568};
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	if(tr[lc].c.val>tr[rc].c.val)
	{
		tr[x].c=tr[lc].c;
		if(tr[lc].c.col==tr[rc].c.col)
		{
			if(tr[lc].cc.val>tr[rc].cc.val)tr[x].cc=tr[lc].cc;
			else tr[x].cc=tr[rc].cc;
		}
		else
		{
			if(tr[lc].cc.val>tr[rc].c.val)tr[x].cc=tr[lc].cc;
			else tr[x].cc=tr[rc].c;
		}
	}
	else
	{
		tr[x].c=tr[rc].c;
		if(tr[lc].c.col==tr[rc].c.col)
		{
			if(tr[lc].cc.val>tr[rc].cc.val)tr[x].cc=tr[lc].cc;
			else tr[x].cc=tr[rc].cc;
		}
		else
		{
			if(tr[lc].c.val>tr[rc].cc.val)tr[x].cc=tr[lc].c;
			else tr[x].cc=tr[rc].cc;
		}
	}
}
inline void pushdown(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[lc].ccc+=tr[x].ccc;
	tr[lc].c.val+=tr[x].ccc;
	tr[lc].cc.val+=tr[x].ccc;
	tr[rc].ccc+=tr[x].ccc;
	tr[rc].c.val+=tr[x].ccc;
	tr[rc].cc.val+=tr[x].ccc;
	tr[x].ccc=0;
	if(tr[x].bk>0)
	{
		if(tr[lc].bk!=tr[x].bk)
		{
			tr[lc].ccc+=tr[lc].bk;
		}
		tr[lc].bk=tr[x].bk;
		if(tr[lc].c.col!=tr[x].bk)tr[lc].c.val+=c[tr[x].bk];
		tr[lc].c.col=tr[x].bk;
		tr[lc].cc=(key){0,-1061109568};
		tr[rc].bk=tr[x].bk;
		if(tr[rc].c.col!=tr[x].bk)tr[rc].c.val+=c[tr[x].bk];
		tr[rc].c.col=tr[x].bk;
		tr[rc].cc=(key){0,-1061109568};
		tr[x].bk=0;
	}
}
void change(int now,int x,key c)
{
	if(tr[now].l==tr[now].r)
	{
		if(c.val>tr[now].c.val)
		{
			if(c.col==tr[now].c.col)tr[now].c=c;
			else tr[now].cc=tr[now].c,tr[now].c=c;
		}
		else if(c.val>tr[now].cc.val&&c.col!=tr[now].c.col)tr[now].cc=c;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(x<=mid)change(lc,x,c);
	else change(rc,x,c);
	update(now);
}
void change(int now,int l,int r,int col)
{
	if(tr[now].l==l&&tr[now].r==r)
	{
		tr[now].bk=col;
		if(tr[now].c.col!=col)tr[now].c.val+=c[col];
		tr[now].c.col=col;
		tr[now].cc=(key){0,-1061109568};
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)return change(lc,l,r,col);
	else if(l>=mid+1)return change(rc,l,r,col);
	else change(lc,l,mid,col),change(rc,mid+1,r,col);
	update(now);
}
inline int mymax(int x,int y){return x>y?x:y;}
int findmax(int now,int l,int r,int col)
{
	if(tr[now].l==l&&tr[now].r==r)return mymax(tr[now].c.val+(tr[now].c.col!=col)*c[col],tr[now].cc.val+(tr[now].cc.col!=col)*c[col]);
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)return findmax(lc,l,r,col);
	else if(l>=mid+1)return findmax(rc,l,r,col);
	else return mymax(findmax(lc,l,mid,col),findmax(rc,mid+1,r,col));
}
int ss,L,R;
inline int mymin(int x,int y){return x<y?x:y;}
void solve(int x)
{
	if(son[x]!=0)solve(son[x]);
	if(tot[x]>L)ss=mymax(ss,findmax(1,ys[x]+L,ys[x]+mymin(R,tot[x]-1),sonc[x]));
	if(tot[x]>1)
	{
		change(1,ys[x]+1,ys[x]+tot[x]-1,sonc[x]);
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			solve(y);
			for(int i=1;i<=mymin(tot[y],R-1);i++)
			{
				if(tot[x]<=L-i)continue;
				int g=findmax(1,ys[y]+i-1,ys[y]+i-1,a[k].c),f=findmax(1,ys[x]+mymax(L-i,1),ys[x]+mymin(R-i,tot[x]-1),0);
				if(sonc[x]==a[k].c)ss=mymax(ss,g+f-c[a[k].c]);
				else ss=mymax(ss,g+f);
			}
			for(int i=1;i<=tot[y];i++)
			{
				int g=findmax(1,ys[y]+i-1,ys[y]+i-1,a[k].c);
				if(L<=i&&i<=R)ss=mymax(ss,g);
				change(1,ys[x]+i,(key){a[k].c,g});
			}
		}
	}
	change(1,ys[x],(key){0,0});
}
int main()
{
	freopen("8-6/journey.in","r",stdin);
	//freopen("journey.out","w",stdout);
	int m;scanf("%d%d%d%d",&n,&m,&L,&R);
	c[0]=0;for(int i=1;i<=m;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,cc;
		scanf("%d%d%d",&x,&y,&cc);
		ins(x,y,cc);ins(y,x,cc);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	z=0;dfs(1,1);
	trlen=0;bt(1,z);
	ss=-1061109568;
	solve(1);
	printf("%d\n",ss);
	return 0;
}