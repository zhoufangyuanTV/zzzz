#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,fa[210000],dep[210000],son[210000],h[210000],tot[210000];
void dfs1(int x)
{
	son[x]=0;h[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs1(y);
			if(h[son[x]]<h[y])son[x]=y;
			if(h[x]<h[y]+1)h[x]=h[y]+1;
			tot[x]+=tot[y];
		}
	}
}
int z,ys[210000],yss[210000];
void dfs2(int x)
{
	ys[x]=++z;yss[z]=x;
	if(son[x]!=0)dfs2(son[x]);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs2(y);
	}
}
struct trnode
{
	int l,r,lc,rc,c;
}tr[410000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=-1061109568;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
inline int mymax(int x,int y){return x>y?x:y;}
void da(int now,int l,int r,int c)
{
	if(c<=tr[now].c)return ;
	if(tr[now].l==l&&tr[now].r==r){tr[now].c=mymax(tr[now].c,c);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)da(lc,l,r,c);
	else if(l>=mid+1)da(rc,l,r,c);
	else da(lc,l,mid,c),da(rc,mid+1,r,c);
}
int qu(int now,int x)
{
	if(tr[now].l==tr[now].r){int re=tr[now].c;tr[now].c=-1061109568;return re;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c=mymax(tr[lc].c,tr[now].c);
	tr[rc].c=mymax(tr[rc].c,tr[now].c);
	tr[now].c=-1061109568;
	if(x<=mid)return qu(lc,x);
	else return qu(rc,x);
}
int Ans[210000];
int f[210000];
void dfs3(int x)
{
	if(son[x]!=0)dfs3(son[x]);
	f[ys[x]]=tot[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			dfs3(y);
			for(int i=0;i<=h[y];i++)
			{
				int l=0,r=h[x];
				while(l<r)
				{
					int mid=(l+r+1)/2;
					if(f[ys[y]+i]<=f[ys[x]+mid])l=mid;
					else r=mid-1;
				}
				if(l>0)Ans[f[ys[y]+i]]=mymax(Ans[f[ys[y]+i]],l+i+2);
				if(l<h[x])da(1,ys[x]+l+1,ys[x]+h[x],i-dep[x]+2);
			}
			for(int i=0;i<=h[y];i++)
			{
				if(f[ys[x]+i+1]<f[ys[y]+i])
				{
					int q=qu(1,ys[x]+i+1)+dep[yss[ys[x]+i+1]];
					Ans[f[ys[x]+i+1]]=mymax(Ans[f[ys[x]+i+1]],q);
					f[ys[x]+i+1]=f[ys[y]+i];
				}
				int q=qu(1,ys[y]+i)+dep[yss[ys[y]+i]];
				Ans[f[ys[y]+i]]=mymax(Ans[f[ys[y]+i]],q);
			}
		}
	}
	if(x==1)
	{
		for(int i=0;i<=h[x];i++)
		{
			int q=qu(1,ys[x]+i)+dep[yss[ys[x]+i]];
			Ans[f[ys[x]+i]]=mymax(Ans[f[ys[x]+i]],q);
		}
	}
	else
	{
		if(tot[x]<n-tot[x])da(1,ys[x],ys[x]+h[x],2-dep[x]);
		else
		{
			int l=0,r=h[x];
			while(l<r)
			{
				int mid=(l+r+1)/2;
				if(n-tot[x]<=f[ys[x]+mid])l=mid;
				else r=mid-1;
			}
			Ans[n-tot[x]]=mymax(Ans[n-tot[x]],l+2);
			if(l<h[x])da(1,ys[x]+l+1,ys[x]+h[x],2-dep[x]);
		}
	}
}
int main()
{
	scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	h[0]=-1;
	fa[1]=0;dep[1]=1;dfs1(1);
	z=0;dfs2(1);
	trlen=0;bt(1,z);
	for(int i=1;i<=n/2;i++)Ans[i]=1;
	dfs3(1);
	for(int i=n/2-1;i>=1;i--)Ans[i]=mymax(Ans[i],Ans[i+1]);
	for(int i=1;i<=n;i++)
	{
		if(i&1)puts("1");
		else printf("%d\n",Ans[i/2]);
	}
	return 0;
}