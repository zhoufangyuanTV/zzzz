#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
struct node
{
	int l,r,lc,rc,c;
}tr[2010000];int len;
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
bool add(int now,int x,int c)
{
	if(tr[now].l==tr[now].r)
	{
		tr[now].c+=c;
		if(tr[now].c<1073741824)return false;
		else
		{
			tr[now].c-=1073741824;
			return true;
		}
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)tr[lc].c=tr[rc].c=tr[now].c;
	bool re;
	if(x<=mid)re=add(lc,x,c);
	else re=add(rc,x,c);
	tr[now].c=tr[lc].c!=tr[rc].c?-1:tr[lc].c;
	return re;
}
bool del(int now,int x,int c)
{
	if(tr[now].l==tr[now].r)
	{
		tr[now].c-=c;
		if(tr[now].c<0){tr[now].c+=1073741824;return true;}
		else return false;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)tr[lc].c=tr[rc].c=tr[now].c;
	bool re;
	if(x<=mid)re=del(lc,x,c);
	else re=del(rc,x,c);
	tr[now].c=tr[lc].c!=tr[rc].c?-1:tr[lc].c;
	return re;
}
bool add(int now,int x)
{
	if(tr[now].l==x&&tr[now].c==1073741823){tr[now].c=0;return true;}
	if(tr[now].l==tr[now].r){tr[now].c++;return false;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)tr[lc].c=tr[rc].c=tr[now].c;
	bool re=false;
	if(x<=mid)
	{
		if(add(lc,x))re=add(rc,mid+1);
	}
	else re=add(rc,x);
	tr[now].c=tr[lc].c!=tr[rc].c?-1:tr[lc].c;
	return re;
}
bool del(int now,int x)
{
	if(tr[now].l==x&&tr[now].c==0){tr[now].c=1073741823;return true;}
	if(tr[now].l==tr[now].r){tr[now].c--;return false;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)tr[lc].c=tr[rc].c=tr[now].c;
	bool re=false;
	if(x<=mid)
	{
		if(del(lc,x))re=del(rc,mid+1);
	}
	else re=del(rc,x);
	tr[now].c=tr[lc].c!=tr[rc].c?-1:tr[lc].c;
	return re;
}
int look(int now,int x)
{
	if(tr[now].c!=-1)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)tr[lc].c=tr[rc].c=tr[now].c;
	if(x<=mid)return look(lc,x);
	else return look(rc,x);
}
int main()
{
	freopen("integer.in","r",stdin);
	freopen("integer.out","w",stdout);
	int n,m;read(n);read(m);read(m);read(m);
	len=0;
	if(n+2<1000)bt(1,1000);
	else bt(1,n+2);
	for(int i=1;i<=n;i++)
	{
		int opt;read(opt);
		if(opt==1)
		{
			int a,b;read(a);read(b);
			if(a==0)continue;
			if(a>0)
			{
				int x=-1;
				if(b%30==0)
				{
					if(add(1,b/30+1,a))x=b/30+2;
				}
				else
				{
					int B=b%30;
					int A=(a&((1<<(30-B))-1))<<B,AA=a>>(30-B);
					if(add(1,b/30+1,A))AA++;
					if(add(1,b/30+2,AA))x=b/30+3;
				}
				if(x!=-1)add(1,x);
			}
			else
			{
				a=-a;
				int x=-1;
				if(b%30==0)
				{
					if(del(1,b/30+1,a))x=b/30+2;
				}
				else
				{
					int B=b%30;
					int A=(a&((1<<(30-B))-1))<<B,AA=a>>(30-B);
					if(del(1,b/30+1,A))AA++;
					if(del(1,b/30+2,AA))x=b/30+3;
				}
				if(x!=-1)del(1,x);
			}
		}
		else
		{
			int k;read(k);
			int c=look(1,k/30+1);
			putchar((c>>(k%30)&1)+'0');
			putchar('\n');
		}
	}
	return 0;
}