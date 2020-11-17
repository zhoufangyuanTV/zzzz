#include<cstdio>
#include<algorithm>
#define ls id*2
#define rs id*2+1
using namespace std;
const int N=1e6+10;
int n,m,k,head[N],fa[N],size[N],dfn[N],old[N],cnt;
struct edge{
	int next,to;
}e[N];
struct tree{
	int l,r,pos;
	unsigned int sum,lazy;
}t[N*4];
void add(int u,int v)
{
	e[++k]=(edge){head[u],v};
	head[u]=k;
}
void pushdown(int id)
{
	t[ls].sum+=t[id].lazy*(t[ls].r-t[ls].l+1);
	t[rs].sum+=t[id].lazy*(t[rs].r-t[rs].l+1);
	t[ls].lazy+=t[id].lazy;
	t[rs].lazy+=t[id].lazy;
	t[id].lazy=0;
}
void build(int id,int l,int r)
{
	t[id].l=l,t[id].r=r;
	if(t[id].l==t[id].r)return ;
	int mid=(t[id].l+t[id].r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
}
void update(int id,int l,int r,unsigned int c)
{
	if(t[id].l==l&&t[id].r==r)
	{
		t[id].sum+=c*(t[id].r-t[id].l+1);
		t[id].lazy+=c;
		return ;
	}
	if(t[id].lazy)pushdown(id);
	int mid=(t[id].l+t[id].r)/2;
	if(r<=mid)update(ls,l,r,c);
	else if(l>mid)update(rs,l,r,c);
	else update(ls,l,mid,c),update(rs,mid+1,r,c);
	t[id].sum=t[ls].sum+t[rs].sum;
}
unsigned int query(int id,int l,int r)
{
	if(t[id].l==l&&t[id].r==r)
	return t[id].sum;
	if(t[id].lazy)pushdown(id);
	int mid=(t[id].l+t[id].r)/2;
	if(r<=mid)return query(ls,l,r);
	else if(l>mid)return query(rs,l,r);
	else return query(ls,l,mid)+query(rs,mid+1,r);
}
void change(int id,int pos,int val)
{
	if(t[id].l==t[id].r)
	{
		if(val==1)t[id].pos=pos;
		else t[id].pos=0;
		return ;
	}
	int mid=(t[id].l+t[id].r)/2;
	if(pos<=mid)change(ls,pos,val);
	else change(rs,pos,val);
	if(t[ls].pos)t[id].pos=t[ls].pos;
	else t[id].pos=t[rs].pos;
}
int find(int id,int l,int r)
{
	if(t[id].l==l&&t[id].r==r)return t[id].pos;
	int mid=(t[id].l+t[id].r)/2;
	if(r<=mid)return find(ls,l,r);
	else if(l>mid)return find(rs,l,r);
	else 
	{
		int pos=find(ls,l,mid);
		if(!pos)return find(rs,mid+1,r);
		else return pos;
	}
}
void dfs(int u)
{
	dfn[u]=++cnt;
	old[cnt]=u;
	size[u]=1;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v!=fa[u]){
			dfs(v);
			size[u]+=size[v];
		}
	}
}
void solve1(int x)
{
	int y;scanf("%u",&y);
	int l=dfn[x],r=dfn[x]+size[x]-1;
	update(1,l,r,y);l++;
	while(l<=r)
	{
		int p=find(1,l,r);
		if(!p)break;
		l=p+size[old[p]];
		update(1,p,l-1,0-y);
	}
}
void solve2(int x)
{
	int y;scanf("%u",&y);
	int l=dfn[x],r=dfn[x]+size[x]-1;
	while(l<=r)
	{
		int p=find(1,l,r);
		if(!p)break;
		l=p+size[old[p]];
		update(1,p,l-1,y);
	}	
}
int main()
{
	freopen("pastel.in","r",stdin);
	freopen("pastel.ans","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa[i]);
		add(fa[i],i);
		add(i,fa[i]);
	}
	dfs(1),build(1,1,n),change(1,1,1);
	for(int i=1,opt,x,l,r;i<=m;i++)
	{
		unsigned int y;
		scanf("%d%d",&opt,&x);
		if(opt==1)printf("%u\n",query(1,dfn[x],dfn[x]));
		else if(opt==2)solve1(x);
		else if(opt==3)printf("%u\n",query(1,dfn[x],dfn[x]+size[x]-1));
		else if(opt==4)solve2(x);
		else if(opt==5)change(1,dfn[x],1);
		else if(opt==6)change(1,dfn[x],0);
	}
	return 0;
}