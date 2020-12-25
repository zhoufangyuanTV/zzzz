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
int log_2[210000];
int z,st[210000][18];
int in[110000],out[110000];
int fa[110000],dep[110000];
void dfs(int x)
{
	st[++z][0]=x;
	in[x]=z;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			st[++z][0]=x;
		}
	}
	out[x]=z;
}
inline int mymin(int x,int y){return dep[x]<dep[y]?x:y;}
void bst()
{
	log_2[0]=-1;
	for(int i=1;i<=z;i++)log_2[i]=log_2[i/2]+1;
	for(int j=1;j<=log_2[z];j++)
	{
		for(int i=1;i<=z-(1<<j)+1;i++)
		{
			st[i][j]=mymin(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
inline int lca(int x,int y)
{
	int l=out[x],r=in[y];
	if(l>r)l^=r^=l^=r;
	int lr=log_2[r-l+1];
	return mymin(st[l][lr],st[r-(1<<lr)+1][lr]);
}
int root[110000];
struct trnode
{
	int l,r,lc,rc,c,cc;
}tr[10010000];int trlen;
inline int new_node(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=tr[now].cc=0;
	if(l==r)tr[now].c=l;
	return now;
}
void change(int now,int x,int c)
{
	if(tr[now].l==tr[now].r){tr[now].cc+=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)
	{
		if(lc==-1)lc=tr[now].lc=new_node(tr[now].l,mid);
		change(lc,x,c);
	}
	else
	{
		if(rc==-1)rc=tr[now].rc=new_node(mid+1,tr[now].r);
		change(rc,x,c);
	}
	tr[now].cc=0xc0c0c0c0;
	if(lc!=-1&&tr[now].cc<tr[lc].cc)tr[now].c=tr[lc].c,tr[now].cc=tr[lc].cc;
	if(rc!=-1&&tr[now].cc<tr[rc].cc)tr[now].c=tr[rc].c,tr[now].cc=tr[rc].cc;
}
int merge(int x,int y)
{
	if(x==-1||y==-1)return x+y+1;
	tr[++trlen]=tr[x];x=trlen;
	if(tr[x].l==tr[x].r){tr[x].cc+=tr[y].cc;return x;}
	int lc=tr[x].lc=merge(tr[x].lc,tr[y].lc);
	int rc=tr[x].rc=merge(tr[x].rc,tr[y].rc);
	tr[x].cc=0xc0c0c0c0;
	if(lc!=-1&&tr[x].cc<tr[lc].cc)tr[x].c=tr[lc].c,tr[x].cc=tr[lc].cc;
	if(rc!=-1&&tr[x].cc<tr[rc].cc)tr[x].c=tr[rc].c,tr[x].cc=tr[rc].cc;
	return x;
}
void hebing(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			hebing(y);
			root[x]=merge(root[x],root[y]);
		}
	}
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	z=0;fa[1]=0;dep[1]=1;dfs(1);bst();
	trlen=0;
	for(int i=1;i<=n;i++)root[i]=new_node(1,100000);
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		int f=lca(x,y);
		change(root[x],c,1);
		change(root[y],c,1);
		change(root[f],c,-1);
		if(f!=1)change(root[fa[f]],c,-1);
	}
	hebing(1);
	for(int i=1;i<=n;i++)printf("%d\n",tr[root[i]].cc<=0?0:tr[root[i]].c);
	return 0;
}