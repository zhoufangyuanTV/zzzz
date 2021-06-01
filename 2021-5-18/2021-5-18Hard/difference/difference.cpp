#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int l,r,lc,rc;
	int lmin,lm,rmax,rm;
	long long c,lmc,rmc;
}tr[1010000];int len;
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
inline long long plus(long long x,long long y){return x+y<998244353?x+y:x+y-998244353;}
inline long long jian(long long x,long long y){return x<y?x-y+998244353:x-y;}
inline void pushdown(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	if(tr[lc].lmin<tr[x].lmin)
	{
		tr[lc].c=jian(tr[lc].c,tr[lc].lmc*(tr[x].lmin-tr[lc].lmin)%998244353);
		tr[lc].lmin=tr[x].lmin;
	}
	if(tr[x].rmax<tr[lc].rmax)
	{
		tr[lc].c=jian(tr[lc].c,tr[lc].rmc*(tr[lc].rmax-tr[x].rmax)%998244353);
		tr[lc].rmax=tr[x].rmax;
	}
	if(tr[rc].lmin<tr[x].lmin)
	{
		tr[rc].c=jian(tr[rc].c,tr[rc].lmc*(tr[x].lmin-tr[rc].lmin)%998244353);
		tr[rc].lmin=tr[x].lmin;
	}
	if(tr[x].rmax<tr[rc].rmax)
	{
		tr[rc].c=jian(tr[rc].c,tr[rc].rmc*(tr[rc].rmax-tr[x].rmax)%998244353);
		tr[rc].rmax=tr[x].rmax;
	}
}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	if(tr[lc].lmin==tr[rc].lmin)
	{
		tr[x].lmin=tr[lc].lmin;
		tr[x].lmc=plus(tr[lc].lmc,tr[rc].lmc);
		tr[x].lm=mymin(tr[lc].lm,tr[rc].lm);
	}
	else
	{
		if(tr[lc].lmin<tr[rc].lmin)
		{
			tr[x].lmin=tr[lc].lmin;
			tr[x].lmc=tr[lc].lmc;
			tr[x].lm=mymin(tr[lc].lm,tr[rc].lmin);
		}
		else
		{
			tr[x].lmin=tr[rc].lmin;
			tr[x].lmc=tr[rc].lmc;
			tr[x].lm=mymin(tr[lc].lmin,tr[rc].lm);
		}
	}
	if(tr[lc].rmax==tr[rc].rmax)
	{
		tr[x].rmax=tr[lc].rmax;
		tr[x].rmc=plus(tr[lc].rmc,tr[rc].rmc);
		tr[x].rm=mymax(tr[lc].rm,tr[rc].rm);
	}
	else
	{
		if(tr[lc].rmax<tr[rc].rmax)
		{
			tr[x].rmax=tr[rc].rmax;
			tr[x].rmc=tr[rc].rmc;
			tr[x].rm=mymax(tr[lc].rmax,tr[rc].rm);
		}
		else
		{
			tr[x].rmax=tr[lc].rmax;
			tr[x].rmc=tr[lc].rmc;
			tr[x].rm=mymax(tr[lc].rm,tr[rc].rmax);
		}
	}
	tr[x].c=plus(tr[lc].c,tr[rc].c);
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	tr[now].lmin=1;tr[now].lm=1000000001;
	tr[now].rmax=1000000000;tr[now].rm=0;
	tr[now].c=tr[now].lmc=tr[now].rmc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
void lchange(int now,int l,int r,int c)
{
	if(c<=tr[now].lmin)return ;
	if(tr[now].l==l&&tr[now].r==r&&c<tr[now].lm)
	{
		tr[now].c=jian(tr[now].c,tr[now].lmc*(c-tr[now].lmin)%998244353);
		tr[now].lmin=c;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)lchange(lc,l,r,c);
	else if(l>=mid+1)lchange(rc,l,r,c);
	else lchange(lc,l,mid,c),lchange(rc,mid+1,r,c);
	update(now);
}
void rchange(int now,int l,int r,int c)
{
	if(tr[now].rmax<=c)return ;
	if(tr[now].l==l&&tr[now].r==r&&tr[now].rm<c)
	{
		tr[now].c=jian(tr[now].c,tr[now].rmc*(tr[now].rmax-c)%998244353);
		tr[now].rmax=c;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)rchange(lc,l,r,c);
	else if(l>=mid+1)rchange(rc,l,r,c);
	else rchange(lc,l,mid,c),rchange(rc,mid+1,r,c);
	update(now);
}
void fchange(int now,int x,long long f)
{
	if(tr[now].l==tr[now].r){tr[now].lmc=tr[now].rmc=f;tr[now].c=f*(tr[now].rmax-tr[now].lmin+1)%998244353;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(x<=mid)fchange(lc,x,f);
	else fchange(rc,x,f);
	update(now);
}
bool query(int now,int x)
{
	if(tr[now].lmin>tr[now].rmax)return false;
	if(tr[now].l==tr[now].r)return true;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(x<=mid)return query(lc,x);
	else return query(rc,x);
}
long long query(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)return query(lc,l,r);
	else if(l>=mid+1)return query(rc,l,r);
	else return plus(query(lc,l,mid),query(rc,mid+1,r));
}
long long f[510000];
int g[510000],gr[510000];
int main()
{
	freopen("difference.in","r",stdin);
	freopen("difference.out","w",stdout);
	int n,id;read(n);read(id);
	len=0;bt(1,n);
	fchange(1,1,1);
	int p=1;g[1]=0;f[1]=1;gr[0]=1;
	for(int i=1;i<=n;i++)
	{
		int l,r;read(l);read(r);
		lchange(1,1,i,l);
		rchange(1,1,i,r);
		while(!query(1,p))p++;
		g[i+1]=g[p]+1;
		f[i+1]=query(1,p,gr[g[p]]);
		gr[g[i+1]]=i+1;
		if(i<n)fchange(1,i+1,f[i+1]);
	}
	if(id==1)printf("%d\n",g[n+1]-1);
	else printf("%lld\n",f[n+1]);
	return 0;
}
