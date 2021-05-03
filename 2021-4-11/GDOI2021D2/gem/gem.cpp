#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int p[51000],A[210000];
struct node
{
	int x,y,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
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
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
int z,ys[210000],yss[210000],top[210000];
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
int m;
struct trnode
{
	int l,r,lc,rc;
	map<int,int> c,cc;
}tr[410000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		int lc=tr[now].lc=trlen+1;bt(l,mid);
		int rc=tr[now].rc=trlen+1;bt(mid+1,r);
		tr[now].c=tr[lc].c;
		for(map<int,int>::iterator it=tr[now].c.begin();it!=tr[now].c.end();it++)
		{
			int y=it->second;
			if(y<m)
			{
				map<int,int>::iterator yt=tr[rc].c.find(y+1);
				if(yt!=tr[rc].c.end())it->second=yt->second;
			}
		}
		for(map<int,int>::iterator it=tr[rc].c.begin();it!=tr[rc].c.end();it++)
		{
			if(tr[now].c.find(it->first)==tr[now].c.end())tr[now].c[it->first]=it->second;
		}
		tr[now].cc=tr[rc].cc;
		for(map<int,int>::iterator it=tr[now].cc.begin();it!=tr[now].cc.end();it++)
		{
			int y=it->second;
			if(y<m)
			{
				map<int,int>::iterator yt=tr[lc].cc.find(y+1);
				if(yt!=tr[lc].cc.end())it->second=yt->second;
			}
		}
		for(map<int,int>::iterator it=tr[lc].cc.begin();it!=tr[lc].cc.end();it++)
		{
			if(tr[now].cc.find(it->first)==tr[now].cc.end())tr[now].cc[it->first]=it->second;
		}
	}
	else
	{
		if(A[yss[l]]!=-1)
		{
			tr[now].c[A[yss[l]]]=A[yss[l]];
			tr[now].cc[A[yss[l]]]=A[yss[l]];
		}
	}
}
int search1(int now,int l,int r,int c)
{
	if(c==m)return c;
	if(tr[now].l==l&&tr[now].r==r)
	{
		map<int,int>::iterator it=tr[now].c.find(c+1);
		if(it==tr[now].c.end())return c;
		else return it->second;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return search1(lc,l,r,c);
	else if(l>=mid+1)return search1(rc,l,r,c);
	else return search1(rc,mid+1,r,search1(lc,l,mid,c));
}
int search2(int now,int l,int r,int c)
{
	if(c==m)return c;
	if(tr[now].l==l&&tr[now].r==r)
	{
		map<int,int>::iterator it=tr[now].cc.find(c+1);
		if(it==tr[now].cc.end())return c;
		else return it->second;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return search2(lc,l,r,c);
	else if(l>=mid+1)return search2(rc,l,r,c);
	else return search2(lc,l,mid,search2(rc,mid+1,r,c));
}
int rt[210000];
struct Q
{
	int l,r;
}ast[210000],bst[210000];
int solve(int x,int y)
{
	int at=0,bt=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			bst[++bt]=(Q){ys[top[y]],ys[y]};
			y=fa[top[y]];
		}
		else
		{
			ast[++at]=(Q){ys[x],ys[top[x]]};
			x=fa[top[x]];
		}
	}
	if(dep[x]<dep[y])bst[++bt]=(Q){ys[x],ys[y]};
	else ast[++at]=(Q){ys[x],ys[y]};
	int c=0;
	for(int i=1;i<=at;i++)c=search2(rt[ast[i].r],ast[i].r,ast[i].l,c);
	for(int i=bt;i>=1;i--)c=search1(rt[bst[i].l],bst[i].l,bst[i].r,c);
	return c;
}
int main()
{
	freopen("gem.in","r",stdin);
	freopen("gem.out","w",stdout);
	read(n);read(m);read(m);
	memset(p,-1,sizeof(p));
	for(int i=1;i<=m;i++)
	{
		int x;read(x);
		p[x]=i;
	}
	for(int i=1;i<=n;i++)
	{
		read(A[i]);
		A[i]=p[A[i]];
	}
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	z=0;dfs(1,1);
	trlen=0;
	for(int i=1;i<=z;i++)
	{
		if(top[yss[i]]==yss[i])
		{
			int l=i;
			while(i<z&&top[yss[i+1]]==yss[l])i++;
			int r=i;
			for(int j=l;j<=r;j++)rt[j]=trlen+1;
			bt(l,r);
		}
	}
	int q;read(q);
	while(q--)
	{
		int x,y;read(x);read(y);
		printf("%d\n",solve(x,y));
	}
	return 0;
}
