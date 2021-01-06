#include<cstdio>
#include<cstring>
using namespace std;
int tpn[310000];
struct node
{
	int l,r,lc,rc,c[3];
	long long cc[3];
}tr[610000];int len;
int a[310000];
inline void fz(int x,int c)
{
	if(c==1)
	{
		tr[x].c[0]=0;tr[x].c[1]=2;tr[x].c[2]=1;
		tr[x].cc[0]=0;tr[x].cc[1]=tr[x].cc[2]=1;
	}
	else if(c==2)
	{
		tr[x].c[1]=1;tr[x].c[0]=2;tr[x].c[2]=0;
		tr[x].cc[1]=0;tr[x].cc[0]=tr[x].cc[2]=1;
	}
	else
	{
		tr[x].c[2]=2;tr[x].c[0]=1;tr[x].c[1]=0;
		tr[x].cc[2]=0;tr[x].cc[0]=tr[x].cc[1]=1;
	}
}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].c[0]=tr[lc].c[tr[rc].c[0]];
	tr[x].c[1]=tr[lc].c[tr[rc].c[1]];
	tr[x].c[2]=tr[lc].c[tr[rc].c[2]];
	tr[x].cc[0]=(tr[lc].cc[tr[rc].c[0]]+tpn[tr[rc].l-tr[x].l]*tr[rc].cc[0])%998244353;
	tr[x].cc[1]=(tr[lc].cc[tr[rc].c[1]]+tpn[tr[rc].l-tr[x].l]*tr[rc].cc[1])%998244353;
	tr[x].cc[2]=(tr[lc].cc[tr[rc].c[2]]+tpn[tr[rc].l-tr[x].l]*tr[rc].cc[2])%998244353;
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else fz(now,a[l]);
}
void change(int now,int x,int c)
{
	if(tr[now].l==tr[now].r){fz(now,c);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(lc,x,c);
	else change(rc,x,c);
	update(now);
}
struct value{int c;long long cc;};
value query(int now,int l,int r,int c)
{
	if(tr[now].l==l&&tr[now].r==r)return (value){tr[now].c[c],tr[now].cc[c]};
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return query(lc,l,r,c);
	else if(l>=mid+1)return query(rc,l,r,c);
	else
	{
		value v=query(rc,mid+1,r,c);
		value lv=query(lc,l,mid,v.c);
		return (value){lv.c,(lv.cc+tpn[mid+1-l]*v.cc)%998244353};
	}
}
int main()
{
	freopen("practice.in","r",stdin);
	freopen("practice.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	tpn[0]=1;
	for(int i=1;i<=n;i++)tpn[i]=tpn[i-1]*2%998244353;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt==1){a[x]=y;change(1,x,y);}
		else printf("%lld\n",query(1,x,y,a[y]-1).cc);
	}
	return 0;
}