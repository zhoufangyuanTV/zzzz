#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct node
{
	int t,c,size;bool G,bk;
	union
	{
		struct{int gl,gr;};
		struct{int l,r,key;};
	};
}tr[60010000];
int sta[60010000],top;
inline int new_node()
{
	if(top==0)fputs("lxlxlxlxlxlxl",stderr);
	int re=sta[top--];
	if(tr[re].G)
	{
		if(tr[re].l>0&&tr[re].t==tr[tr[re].l].t)sta[++top]=tr[re].l;
		if(tr[re].r>0&&tr[re].t==tr[tr[re].r].t)sta[++top]=tr[re].r;
	}
	memset(tr+re,0,sizeof(node));
	return re;
}
inline void update(int x)
{
	if(tr[x].G)tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
}
inline void G(int x)
{
	if(!tr[x].G)
	{
		tr[x].G=true;
		int l=tr[x].gl,r=tr[x].gr;
		int mid=(l+r)/2;
		if(l<mid)
		{
			tr[x].l=new_node();
			tr[tr[x].l].t=tr[x].t;
			tr[tr[x].l].gl=l;tr[tr[x].l].gr=mid-1;
			tr[tr[x].l].c=rand();tr[tr[x].l].size=mid-l;
		}
		else tr[x].l=0;
		if(mid<r)
		{
			tr[x].r=new_node();
			tr[tr[x].r].t=tr[x].t;
			tr[tr[x].r].gl=mid+1;tr[tr[x].r].gr=r;
			tr[tr[x].r].c=rand();tr[tr[x].r].size=r-mid;
		}
		else tr[x].r=0;
		tr[x].key=mid;
	}
}
inline void pushdown(int x)
{
	if(tr[x].bk)
	{
		if(tr[x].l>0&&tr[x].t!=tr[tr[x].l].t)
		{
			int l=new_node();
			tr[l]=tr[tr[x].l];
			tr[l].t=tr[x].t;
			tr[x].l=l;
		}
		if(tr[x].r>0&&tr[x].t!=tr[tr[x].r].t)
		{
			int r=new_node();
			tr[r]=tr[tr[x].r];
			tr[r].t=tr[x].t;
			tr[x].r=r;
		}
		swap(tr[x].l,tr[x].r);
		if(tr[x].l>0)tr[tr[x].l].bk^=1;
		if(tr[x].r>0)tr[tr[x].r].bk^=1;
		tr[x].bk=false;
	}
}
int T;
inline void copy(int &x)
{
	int len=new_node();
	tr[len]=tr[x];
	tr[len].t=T;
	x=len;
}
void split(int now,int k,int &x,int &y)
{
	if(now==0)x=y=0;
	else
	{
		if(tr[now].t!=T)
		{
			if(tr[now].G)
			{
				pushdown(now);
				copy(now);
			}
			else
			{
				copy(now);
				G(now);
				pushdown(now);
			}
		}
		else
		{
			G(now);
			pushdown(now);
		}
		if(k<=tr[tr[now].l].size)
		{
			y=now;split(tr[now].l,k,x,tr[y].l);
		}
		else
		{
			x=now;split(tr[now].r,k-tr[tr[now].l].size-1,tr[x].r,y);
		}
		update(now);
	}
}
int merge(int x,int y)
{
	if(x==0&&y==0)return 0;
	if(x==0||y==0)
	{
		int xy=x+y;
		if(tr[xy].t!=T)copy(xy);
		return xy;
	}
	if(tr[x].c<tr[y].c)
	{
		G(x);
		pushdown(x);
		if(tr[x].t!=T)copy(x);
		tr[x].r=merge(tr[x].r,y);
		update(x);
		return x;
	}
	else
	{
		G(y);
		pushdown(y);
		if(tr[y].t!=T)copy(y);
		tr[y].l=merge(x,tr[y].l);
		update(y);
		return y;
	}
}
int select(int now,int k)
{
	if(tr[now].bk)k=tr[now].size-k+1;
	if(!tr[now].G)return tr[now].gl+k-1;
	if(k<=tr[tr[now].l].size)return select(tr[now].l,k);
	else if(k==tr[tr[now].l].size+1)return tr[now].key;
	else return select(tr[now].r,k-tr[tr[now].l].size-1);
}
int z[110000];
struct trnode
{
	int l,r,lc,rc,c;
}a[210000];int len;
int bt(int l,int r)
{
	if(r-l<10000)return -1;
	len++;int now=len;
	a[now].l=l;a[now].r=r;a[now].lc=a[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		a[now].lc=bt(l,mid);
		a[now].rc=bt(mid+1,r);
		int root,R;
		if(a[now].rc==-1)
		{
			root=new_node();R=r;
			tr[root].c=rand();
			tr[root].t=0;
			tr[root].size=10000001;
			tr[root].gl=0;tr[root].gr=10000000;
		}
		else root=a[a[now].rc].c,R=mid;
		for(int i=R;i>=l;i--)
		{
			T=i;
			int x,xx;split(root,z[i]+1,x,xx);
			if(xx>0)sta[++top]=xx;
			int y,yy;split(root,10000000-z[i]+1,y,yy);
			if(yy>0)sta[++top]=yy;
			split(y,1,yy,y);
			if(yy>0)sta[++top]=yy;
			tr[x].bk^=1;
			root=merge(x,y);
		}
		a[now].c=root;
	}
	return now;
}
int query(int now,int l,int r,int c)
{
	if(now==-1)
	{
		for(int i=l;i<=r;i++)c=abs(c-z[i]);
		return c;
	}
	if(a[now].l==l&&a[now].r==r)return select(a[now].c,c+1);
	int lc=a[now].lc,rc=a[now].rc;
	int mid=(a[now].l+a[now].r)/2;
	if(r<=mid)return query(lc,l,r,c);
	else if(l>=mid+1)return query(rc,l,r,c);
	else return query(rc,mid+1,r,query(lc,l,mid,c));
}
int main()
{
	freopen("leetcode.in","r",stdin);
	freopen("leetcode.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&z[i]);
	for(int i=1;i<=60000000;i++)sta[i]=60000000-i+1;
	top=60000000;
	len=0;int rt=bt(1,n);
	int lst=0;
	for(int i=1;i<=m;i++)
	{
		int l,r,c;scanf("%d%d%d",&l,&r,&c);
		l^=lst;r^=lst;c^=lst;
		printf("%d\n",lst=query(rt,l,r,c));
	}
	return 0;
}