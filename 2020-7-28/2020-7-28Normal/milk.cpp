#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int l,r,lc,rc,minc,maxc;
	long long c;
	bool bk;
	int cc;
}tr[210000];int len;
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].minc=mymin(tr[lc].minc,tr[rc].minc);
	tr[x].maxc=mymax(tr[lc].maxc,tr[rc].maxc);
	tr[x].c=tr[lc].c+tr[rc].c;
}
int a[110000];
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=0;tr[now].cc=0;tr[now].bk=false;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else tr[now].minc=tr[now].maxc=tr[now].c=a[l],tr[now].bk=true;
}
void change1(int now,int l,int r,int c)
{
	if(tr[now].l==l&&tr[now].r==r)
	{
		tr[now].minc+=c;tr[now].maxc+=c;
		tr[now].c+=c*(r-l+1);
		if(!tr[now].bk)tr[now].cc+=c;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bk)
	{
		long long cc=tr[now].minc;
		tr[lc].bk=tr[rc].bk=true;
		tr[lc].cc=tr[rc].cc=0;
		tr[lc].minc=tr[rc].minc=tr[lc].maxc=tr[rc].maxc=cc;
		tr[lc].c=cc*(tr[lc].r-tr[lc].l+1);tr[rc].c=cc*(tr[rc].r-tr[rc].l+1);
	}
	long long cc=tr[now].cc;
	tr[lc].minc+=cc;tr[lc].maxc+=cc;
	tr[lc].c+=cc*(tr[lc].r-tr[lc].l+1);
	if(!tr[lc].bk)tr[lc].cc+=cc;
	tr[rc].minc+=cc;tr[rc].maxc+=cc;
	tr[rc].c+=cc*(tr[rc].r-tr[rc].l+1);
	if(!tr[rc].bk)tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)change1(lc,l,r,c);
	else if(l>=mid+1)change1(rc,l,r,c);
	else change1(lc,l,mid,c),change1(rc,mid+1,r,c);
	update(now);
	tr[now].bk=tr[now].minc==tr[now].maxc;
}
void change2(int now,int l,int r,int c)
{
	long long cg=tr[now].minc/c,cr=tr[now].maxc/c;
	if(tr[now].minc%c!=0&&tr[now].minc<0)cg--;
	if(tr[now].maxc%c!=0&&tr[now].maxc<0)cr--;
	if(tr[now].l==l&&tr[now].r==r&&cg==cr)
	{
		tr[now].bk=true;
		tr[now].minc=cg;tr[now].maxc=cg;
		tr[now].c=cg*(r-l+1);
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bk)
	{
		long long cc=tr[now].minc;
		tr[lc].bk=tr[rc].bk=true;
		tr[lc].cc=tr[rc].cc=0;
		tr[lc].minc=tr[rc].minc=tr[lc].maxc=tr[rc].maxc=cc;
		tr[lc].c=cc*(tr[lc].r-tr[lc].l+1);tr[rc].c=cc*(tr[rc].r-tr[rc].l+1);
	}
	long long cc=tr[now].cc;
	tr[lc].minc+=cc;tr[lc].maxc+=cc;
	tr[lc].c+=cc*(tr[lc].r-tr[lc].l+1);
	if(!tr[lc].bk)tr[lc].cc+=cc;
	tr[rc].minc+=cc;tr[rc].maxc+=cc;
	tr[rc].c+=cc*(tr[rc].r-tr[rc].l+1);
	if(!tr[rc].bk)tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)change2(lc,l,r,c);
	else if(l>=mid+1)change2(rc,l,r,c);
	else change2(lc,l,mid,c),change2(rc,mid+1,r,c);
	update(now);
	tr[now].bk=tr[now].minc==tr[now].maxc;
}
int findmin(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].minc;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bk)
	{
		long long cc=tr[now].minc;
		tr[lc].bk=tr[rc].bk=true;
		tr[lc].cc=tr[rc].cc=0;
		tr[lc].minc=tr[rc].minc=tr[lc].maxc=tr[rc].maxc=cc;
		tr[lc].c=cc*(tr[lc].r-tr[lc].l+1);tr[rc].c=cc*(tr[rc].r-tr[rc].l+1);
	}
	long long cc=tr[now].cc;
	tr[lc].minc+=cc;tr[lc].maxc+=cc;
	tr[lc].c+=cc*(tr[lc].r-tr[lc].l+1);
	if(!tr[lc].bk)tr[lc].cc+=cc;
	tr[rc].minc+=cc;tr[rc].maxc+=cc;
	tr[rc].c+=cc*(tr[rc].r-tr[rc].l+1);
	if(!tr[rc].bk)tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)return findmin(lc,l,r);
	else if(l>=mid+1)return findmin(rc,l,r);
	else return mymin(findmin(lc,l,mid),findmin(rc,mid+1,r));
}
long long findsum(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].bk)
	{
		long long cc=tr[now].minc;
		tr[lc].bk=tr[rc].bk=true;
		tr[lc].cc=tr[rc].cc=0;
		tr[lc].minc=tr[rc].minc=tr[lc].maxc=tr[rc].maxc=cc;
		tr[lc].c=cc*(tr[lc].r-tr[lc].l+1);tr[rc].c=cc*(tr[rc].r-tr[rc].l+1);
	}
	long long cc=tr[now].cc;
	tr[lc].minc+=cc;tr[lc].maxc+=cc;
	tr[lc].c+=cc*(tr[lc].r-tr[lc].l+1);
	if(!tr[lc].bk)tr[lc].cc+=cc;
	tr[rc].minc+=cc;tr[rc].maxc+=cc;
	tr[rc].c+=cc*(tr[rc].r-tr[rc].l+1);
	if(!tr[rc].bk)tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)return findsum(lc,l,r);
	else if(l>=mid+1)return findsum(rc,l,r);
	else return findsum(lc,l,mid)+findsum(rc,mid+1,r);
}
int main()
{
	freopen("milk.in","r",stdin);
	freopen("milk.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	len=0;bt(1,n);int t;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&t);
		wow:
		if(t<=2)
		{
			int l,r,c;
			scanf("%d%d%d",&l,&r,&c);
			if(t==1)
			{
				i++;
				scanf("%d",&t);
				if(t==2)
				{
					int ll,rr,cc;
					scanf("%d%d%d",&ll,&rr,&cc);
					if((cc==c+1||-cc==c+1)&&ll<=r&&l<=rr)
					{
						if(l<ll)change1(1,l,ll-1,c);
						if(ll<l)change2(1,ll,l-1,cc);
						if(r<rr)change2(1,r+1,rr,cc);
						if(rr<r)change1(1,rr+1,r,c);
					}
					else change1(1,l,r,c),change2(1,ll,rr,cc);
				}
				else goto wow;
			}
			if(t==2)change2(1,l,r,c);
		}
		else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			long long k=0;
			if(t==3)k=findmin(1,l,r);
			if(t==4)k=findsum(1,l,r);
			printf("%lld\n",k);
		}
	}
	return 0;
}
