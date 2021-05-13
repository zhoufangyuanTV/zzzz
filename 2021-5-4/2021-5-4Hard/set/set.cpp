#include<cstdio>
#include<cstring>
#include<utility>
#include<algorithm>
using namespace std;
struct node
{
	int l,r,lc,rc;
	pair<int,int> c;
}a[2010000];int len;
int L[1010000],R[1010000];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
inline pair<int,int> jiao(pair<int,int> x,pair<int,int> y){return make_pair(mymax(x.first,y.first),mymin(x.second,y.second));}
void ba(int l,int r)
{
	len++;int now=len;
	a[now].l=l;a[now].r=r;a[now].lc=a[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		a[now].lc=len+1;ba(l,mid);
		a[now].rc=len+1;ba(mid+1,r);
		a[now].c=jiao(a[a[now].lc].c,a[a[now].rc].c);
	}
	else a[now].c=make_pair(L[l],R[l]);
}
pair<int,int> fjiao(int now,int l,int r)
{
	if(a[now].l==l&&a[now].r==r)return a[now].c;
	int lc=a[now].lc,rc=a[now].rc;
	int mid=(a[now].l+a[now].r)/2;
	if(r<=mid)return fjiao(lc,l,r);
	else if(l>=mid+1)return fjiao(rc,l,r);
	else return jiao(fjiao(lc,l,mid),fjiao(rc,mid+1,r));
}
int z,Z[2010000];
struct Query{int l,r,L,R,p;}Q[1010000];
int Ans[1010000];
inline bool cmp(Query x,Query y){return x.r<y.r;}
struct trnode
{
	int l,r,lc,rc,c;
}tr[4010000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
void change(int now,int l,int r,int c)
{
	if(tr[now].l==l&&tr[now].r==r){tr[now].c=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c=mymax(tr[lc].c,tr[now].c);
	tr[rc].c=mymax(tr[rc].c,tr[now].c);
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	tr[now].c=mymin(tr[lc].c,tr[rc].c);
}
int ff(int now,int l,int r,int c)
{
	if(c<=tr[now].c)return -1;
	if(tr[now].l==tr[now].r)return tr[now].l;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return ff(lc,l,r,c);
	else if(l>=mid+1)return ff(rc,l,r,c);
	else
	{
		int re=ff(lc,l,mid,c);
		if(re==-1)return ff(rc,mid+1,r,c);
		else return re;
	}
}
int l[1010000],r[1010000];
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int main()
{
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
	int n,m;read(n);read(m);
	z=1;Z[1]=1;
	for(int i=1;i<=n;i++)
	{
		int a,b,c,d;read(a);read(b);read(c);read(d);
		if(a>c)a^=c^=a^=c,b^=d^=b^=d;
		if(b+1<c)
		{
			L[i]=a;R[i]=d;
			l[i]=b+1;r[i]=c;
			Z[++z]=l[i];Z[++z]=r[i];
		}
		else
		{
			l[i]=r[i]=-1;
			L[i]=a;R[i]=mymax(b,d);
		}
	}
	sort(Z+1,Z+z+1);
	z=unique(Z+1,Z+z+1)-Z-1;
	len=trlen=0;ba(1,n);bt(1,z);
	for(int i=1;i<=m;i++)
	{
		read(Q[i].l);read(Q[i].r);
		Q[i].p=i;
		pair<int,int> c=fjiao(1,Q[i].l,Q[i].r);
		Q[i].L=c.first;Q[i].R=c.second;
	}
	sort(Q+1,Q+m+1,cmp);
	int j=1;
	for(int i=1;i<=n;i++)
	{
		if(l[i]!=-1)change(1,lower_bound(Z+1,Z+z+1,l[i])-Z,lower_bound(Z+1,Z+z+1,r[i])-Z-1,i);
		while(j<=m&&Q[j].r==i)
		{
			if(Q[j].L>Q[j].R)Ans[Q[j].p]=-1;
			else
			{
				Ans[Q[j].p]=ff(1,upper_bound(Z+1,Z+z+1,Q[j].L)-Z-1,upper_bound(Z+1,Z+z+1,Q[j].R)-Z-1,Q[j].l);
				if(Ans[Q[j].p]!=-1)Ans[Q[j].p]=mymax(Z[Ans[Q[j].p]],Q[j].L);
			}
			j++;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(Ans[i]==-1)puts("NO");
		else printf("%d\n",Ans[i]);
	}
	return 0;
}