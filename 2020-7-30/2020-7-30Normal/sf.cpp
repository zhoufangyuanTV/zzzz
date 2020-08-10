#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,c[210000];
inline int lowbit(int x){return x&-x;}
void change(int x,int s)
{
	while(x<=n)
	{
		c[x]+=s;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
struct node
{
	int l,r,lc,rc;
	long long c;
	int maxc,cc,mac;
	int bac;
}tr[410000];int len;
int v[210000];
inline int mymax(int x,int y){return x>y?x:y;}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].c=tr[lc].c+tr[rc].c;
	if(tr[lc].maxc==tr[rc].maxc)
	{
		tr[x].maxc=tr[lc].maxc;
		tr[x].cc=tr[lc].cc+tr[rc].cc;
		tr[x].mac=mymax(tr[lc].mac,tr[rc].mac);
	}
	else
	{
		if(tr[lc].maxc<tr[rc].maxc)tr[x].maxc=tr[rc].maxc,tr[x].cc=tr[rc].cc,tr[x].mac=mymax(tr[lc].maxc,tr[rc].mac);
		else tr[x].maxc=tr[lc].maxc,tr[x].cc=tr[lc].cc,tr[x].mac=mymax(tr[lc].mac,tr[rc].maxc);
	}
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].bac=0x3f3f3f3f;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else tr[now].c=tr[now].maxc=v[l],tr[now].cc=1,tr[now].mac=0xc0c0c0c0;
}
void change(int now,int l,int r,int c)
{
	if(tr[now].maxc<=c)return ;
	if(tr[now].l==l&&tr[now].r==r&&tr[now].mac<c)
	{
		tr[now].c-=(long long)(tr[now].maxc-c)*tr[now].cc;
		tr[now].maxc=c;tr[now].bac=c;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bac<tr[lc].maxc)
	{
		tr[lc].c-=(long long)(tr[lc].maxc-tr[now].bac)*tr[lc].cc;
		tr[lc].maxc=tr[now].bac;tr[lc].bac=tr[now].bac;
	}
	if(tr[now].bac<tr[rc].maxc)
	{
		tr[rc].c-=(long long)(tr[rc].maxc-tr[now].bac)*tr[rc].cc;
		tr[rc].maxc=tr[now].bac;tr[rc].bac=tr[now].bac;
	}
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	update(now);
}
long long findc(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bac<tr[lc].maxc)
	{
		tr[lc].c-=(long long)(tr[lc].maxc-tr[now].bac)*tr[lc].cc;
		tr[lc].maxc=tr[now].bac;tr[lc].bac=tr[now].bac;
	}
	if(tr[now].bac<tr[rc].maxc)
	{
		tr[rc].c-=(long long)(tr[rc].maxc-tr[now].bac)*tr[rc].cc;
		tr[rc].maxc=tr[now].bac;tr[rc].bac=tr[now].bac;
	}
	if(r<=mid)return findc(lc,l,r);
	else if(l>=mid+1)return findc(rc,l,r);
	else return findc(lc,l,mid)+findc(rc,mid+1,r);
}
struct QwQ
{
	int l,r,p;
}Q[210000];
inline bool cmp1(QwQ x,QwQ y){return x.r>y.r;}
long long Ans[210000];
int a[210000];
int sta[210000],top;
struct IM{int x,p;}mi[210000];
inline bool cmp2(IM x,IM y){return x.x>y.x;}
int main()
{
	freopen("sf.in","r",stdin);
	freopen("sf.out","w",stdout);
	int m,p1,p2;scanf("%d%d%d%d",&n,&m,&p1,&p2);p1=p1-p2;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].p=i;
	top=0;
	for(int i=n;i>=1;i--)
	{
		while(top>0&&a[sta[top]]<a[i])top--;
		if(top>0)v[i]=sta[top]-1;
		else v[i]=n;
		mi[i]=(IM){v[i]+1,i};
		sta[++top]=i;
	}
	for(int i=1;i<=n;i++)c[i]=lowbit(i);
	sort(mi+1,mi+n+1,cmp2);
	len=0;bt(1,n);
	sort(Q+1,Q+m+1,cmp1);
	int j=1;
	for(int i=1;i<=m;i++)
	{
		while(j<=n&&mi[j].x>Q[i].r)
		{
			change(mi[j].p,-1);j++;
		}
		change(1,1,n,Q[i].r);
		int l=Q[i].l,r=Q[i].r;
		Ans[Q[i].p]=(findc(1,Q[i].l,Q[i].r)-(long long)(l+r)*(r-l+1)/2)*p2+(sum(Q[i].r)-sum(Q[i].l-1))*p1;
	}
	for(int i=1;i<=n/2;i++)a[i]^=a[n-i+1]^=a[i]^=a[n-i+1];
	for(int i=1;i<=m;i++)Q[i]=(QwQ){(n-Q[i].r+1),(n-Q[i].l+1),Q[i].p};
	top=0;
	for(int i=n;i>=1;i--)
	{
		while(top>0&&a[sta[top]]<a[i])top--;
		if(top>0)v[i]=sta[top]-1;
		else v[i]=n;
		mi[i]=(IM){v[i]+1,i};
		sta[++top]=i;
	}
	for(int i=1;i<=n;i++)c[i]=lowbit(i);
	sort(mi+1,mi+n+1,cmp2);
	len=0;bt(1,n);
	sort(Q+1,Q+m+1,cmp1);
	j=1;
	for(int i=1;i<=m;i++)
	{
		while(j<=n&&mi[j].x>Q[i].r)
		{
			change(mi[j].p,-1);j++;
		}
		change(1,1,n,Q[i].r);
		int l=Q[i].l,r=Q[i].r;
		Ans[Q[i].p]+=(findc(1,Q[i].l,Q[i].r)-(long long)(l+r)*(r-l+1)/2)*p2+(sum(Q[i].r)-sum(Q[i].l-1))*p1;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}