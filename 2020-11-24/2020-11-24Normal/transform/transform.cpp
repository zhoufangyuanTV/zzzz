#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int l,r,lc,rc;
	char c,cl,cr;
	int ls,rs,cc;
}tr[1010000];int len;
char a[510000];
inline int mymax(int x,int y){return x>y?x:y;}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].cl=tr[lc].cl;
	tr[x].cr=tr[rc].cr;
	tr[x].ls=tr[lc].ls;
	tr[x].rs=tr[rc].rs;
	tr[x].cc=mymax(tr[lc].cc,tr[rc].cc);
	if(tr[lc].cr!=tr[rc].cl)
	{
		if(tr[lc].cc==tr[lc].r-tr[lc].l+1)tr[x].ls=tr[lc].cc+tr[rc].ls;
		if(tr[rc].cc==tr[rc].r-tr[rc].l+1)tr[x].rs=tr[rc].cc+tr[lc].rs;
		tr[x].cc=mymax(tr[x].cc,tr[lc].rs+tr[rc].ls);
	}
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=EOF;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else tr[now].cl=tr[now].cr=a[l],tr[now].ls=tr[now].rs=tr[now].cc=1;
}
void change(int now,int l,int r,char c)
{
	if(tr[now].l==l&&tr[now].r==r){tr[now].c=tr[now].cl=tr[now].cr=c;tr[now].ls=tr[now].rs=tr[now].cc=1;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=EOF)
	{
		tr[lc].c=tr[lc].cl=tr[lc].cr=tr[now].c;
		tr[lc].ls=tr[lc].rs=tr[lc].cc=1;
		tr[rc].c=tr[rc].cl=tr[rc].cr=tr[now].c;
		tr[rc].ls=tr[rc].rs=tr[rc].cc=1;
		tr[now].c=EOF;
	}
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	update(now);
}
int main()
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	scanf("%s",a+1);
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int x,l,k;scanf("%d%d%d",&x,&l,&k);
		if(x+l<=n)change(1,x+1,x+l,k+'0');
		else change(1,x+1,n,k+'0'),change(1,1,x+l-n,k+'0');
		int ss=tr[1].cc;
		if(tr[1].cl!=tr[1].cr)ss=mymax(ss,tr[1].rs+tr[1].ls);
		if(ss>n)puts("-1");
		else printf("%d\n",(ss-1)/2);
	}
	return 0;
}