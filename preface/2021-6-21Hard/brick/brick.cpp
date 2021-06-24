#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct lint
{
	unsigned long long a;
	unsigned b;
	lint(int x=0):a(x>>8),b(x&255){}
	lint(long long x):a(x>>8),b(x&255){}
	lint(unsigned long long x,unsigned y):a(x),b(y){}
};
inline lint operator+(lint x,lint y)
{
	lint z(x.a+y.a,x.b+y.b);
	if(z.b>=256)z.b-=256,z.a++;
	return z;
}
inline lint operator-(lint x,lint y)
{
	lint z(x.a-y.a-1,x.b-y.b+256);
	if(z.b>=256)z.b-=256,z.a++;
	return z;
}
inline lint operator*(lint x,lint y)
{
	lint z((x.a*y.a<<8)+x.a*y.b+x.b*y.a,x.b*y.b);
	z.a+=z.b>>8;z.b&=255;
	return z;
}
inline bool operator<(lint x,lint y){return x.a^y.a?x.a<y.a:x.b<y.b;}
inline bool IZ(lint x){return x.a==0&&x.b==0;}
inline bool odd(lint x){return x.b&1;}
inline lint half(lint x){return lint(x.a>>1,(x.a&1)<<7|x.b>>1);}
inline lint d(lint x,lint y){return x<y?y-x:x-y;}
lint gcd(lint x,lint y)
{
	if(y<x)swap(x,y);
	if(IZ(x))return y;
	if(IZ(y))return x;
	if(odd(x))
	{
		if(odd(y))return gcd(x,half(y-x));
		else return gcd(x,half(y));
	}
	else
	{
		if(odd(y))return gcd(half(x),y);
		else return 2*gcd(half(x),half(y));
	}
}
char buf[110],*p;
inline void write(lint x)
{
	if(IZ(x))puts("0");
	p=buf;
	while(!IZ(x))
	{
		x.b+=x.a%10<<8;
		x.a/=10;
	    *p++=x.b%10+'0';
		x.b/=10;
	}
	while(p!=buf)putchar(*--p);
	putchar('\n');
}
int h[210000];
struct node
{
	int l,r,lc,rc;
	int a,b;
	long long c,cc;
}a[410000];int len;
void ba(int l,int r)
{
	len++;int now=len;
	a[now].l=l;a[now].r=r;a[now].lc=a[now].rc=-1;a[now].cc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		a[now].lc=len+1;ba(l,mid);
		a[now].rc=len+1;ba(mid+1,r);
	}
	else a[now].a=a[now].b=0,a[now].c=h[l],a[now].cc=-1;
}
inline void pushdown(int x)
{
	if(a[x].cc==-1)
	{
		a[a[x].lc].a=a[a[x].rc].a=a[x].a;
		a[a[x].lc].b=a[a[x].rc].b=a[x].b;
		a[a[x].lc].c=a[a[x].rc].c=a[x].c;
		a[a[x].lc].cc=a[a[x].rc].cc=-1;
		a[x].cc=0;
	}
	else
	{
		if(a[a[x].lc].cc==-1)a[a[x].lc].c+=a[x].cc;
		else a[a[x].lc].cc+=a[x].cc;
		if(a[a[x].rc].cc==-1)a[a[x].rc].c+=a[x].cc;
		else a[a[x].rc].cc+=a[x].cc;
		a[x].cc=0;
	}
}
void change(int now,int l,int r,int A,int b,int c)
{
	if(a[now].l==l&&a[now].r==r)
	{
		a[now].a=A;a[now].b=b;a[now].c=c;
		a[now].cc=-1;
		return ;
	}
	int lc=a[now].lc,rc=a[now].rc;
	int mid=(a[now].l+a[now].r)/2;
	pushdown(now);
	if(r<=mid)change(lc,l,r,A,b,c);
	else if(l>=mid+1)change(rc,l,r,A,b,c);
	else change(lc,l,mid,A,b,c),change(rc,mid+1,r,A,b,c);
}
void change(int now,int l,int r,int c)
{
	if(a[now].l==l&&a[now].r==r)
	{
		if(a[now].cc==-1)a[now].c+=c;
		else a[now].cc+=c;
		return ;
	}
	int lc=a[now].lc,rc=a[now].rc;
	int mid=(a[now].l+a[now].r)/2;
	pushdown(now);
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
}
lint query(int now,int x)
{
	if(a[now].l==a[now].r)
	{
		lint X(x);
		return a[now].a*X*X+a[now].b*X+a[now].c;
	}
	int lc=a[now].lc,rc=a[now].rc;
	int mid=(a[now].l+a[now].r)/2;
	pushdown(now);
	if(x<=mid)return query(lc,x);
	else return query(rc,x);
}
struct trnode
{
	int l,r,lc,rc;
	int a,b;lint c;
	bool bk;
}tr[410000];int trlen;
void btr(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].bk=false;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;btr(l,mid);
		tr[now].rc=trlen+1;btr(mid+1,r);
		tr[now].c=gcd(tr[tr[now].lc].c,tr[tr[now].rc].c);
	}
	else tr[now].c=d(h[l],h[l+1]);
}
void calc(int x)
{
	if(tr[x].l==tr[x].r)
	{
		lint X=tr[x].l;
		tr[x].c=2*tr[x].a*X+tr[x].a+tr[x].b;
	}
	else tr[x].c=gcd(2*tr[x].a,tr[x].a+tr[x].b);
}
void change(int now,int x,lint c)
{
	if(tr[now].l==tr[now].r){tr[now].c=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bk)
	{
		tr[lc].a=tr[rc].a=tr[now].a;
		tr[lc].b=tr[rc].b=tr[now].b;
		calc(lc);calc(rc);
		tr[lc].bk=tr[rc].bk=true;
		tr[now].bk=false;
	}
	if(x<=mid)change(lc,x,c);
	else change(rc,x,c);
	tr[now].c=gcd(tr[lc].c,tr[rc].c);
}
void change(int now,int l,int r,int A,int b)
{
	if(tr[now].l==l&&tr[now].r==r){tr[now].a=A;tr[now].b=b;calc(now);tr[now].bk=true;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bk)
	{
		tr[lc].a=tr[rc].a=tr[now].a;
		tr[lc].b=tr[rc].b=tr[now].b;
		calc(lc);calc(rc);
		tr[lc].bk=tr[rc].bk=true;
		tr[now].bk=false;
	}
	if(r<=mid)change(lc,l,r,A,b);
	else if(l>=mid+1)change(rc,l,r,A,b);
	else change(lc,l,mid,A,b),change(rc,mid+1,r,A,b);
	tr[now].c=gcd(tr[lc].c,tr[rc].c);
}
int main()
{
	freopen("brick.in","r",stdin);
	freopen("brick.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]);
	len=0;ba(1,n);
	trlen=0;btr(1,n-1);
	for(int i=1;i<=m;i++)
	{
		int op,l,r,a,b,c;scanf("%d%d%d%d%d%d",&op,&l,&r,&a,&b,&c);
		if(op==1)
		{
			change(1,l,r,a,b,c);
			if(l>1)change(1,l-1,d(query(1,l-1),query(1,l)));
			if(r<n)change(1,r,d(query(1,r),query(1,r+1)));
			if(l<r)change(1,l,r-1,a,b);
		}
		else
		{
			change(1,l,r,c);
			if(l>1)change(1,l-1,d(query(1,l-1),query(1,l)));
			if(r<n)change(1,r,d(query(1,r),query(1,r+1)));
		}
		write(tr[1].c);
	}
	return 0;
}
