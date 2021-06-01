#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct trnode
{
	int l,r,lc,rc,c,cc;
}tr[2010000];int len;
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=tr[now].cc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
inline int mymax(int x,int y){return x>y?x:y;}
void change(int now,int l,int r,int c)
{
	if(tr[now].l==l&&tr[now].r==r){tr[now].c+=c;tr[now].cc+=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	tr[now].c=mymax(tr[lc].c,tr[rc].c)+tr[now].cc;
}
int z[1010000];
struct node
{
	int l,r,c;
}a[510000];
inline bool cmp(node x,node y){return x.c<y.c;}
int main()
{
	freopen("interval.in","r",stdin);
	freopen("interval.out","w",stdout);
	int n,m;read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		read(a[i].l);read(a[i].r);
		a[i].c=a[i].r-a[i].l;
		z[i*2-1]=a[i].l;
		z[i*2]=a[i].r;
	}
	sort(z+1,z+n*2+1);
	len=0;bt(1,n*2);
	for(int i=1;i<=n;i++)
	{
		a[i].l=lower_bound(z+1,z+n*2+1,a[i].l)-z;
		a[i].r=lower_bound(z+1,z+n*2+1,a[i].r)-z;
		change(1,a[i].l,a[i].r,1);
	}
	sort(a+1,a+n+1,cmp);
	if(tr[1].c<m)
	{
		puts("-1");
		return 0;
	}
	int l=0,r=1000000000;
	while(l<r)
	{
		int mid=(l+r)/2;
		bool bk=false;
		int j=1;
		len=0;bt(1,n*2);
		for(int i=1;i<=n;i++)
		{
			while(j<=n&&a[j].c<=a[i].c+mid)
			{
				change(1,a[j].l,a[j].r,1);
				j++;
			}
			if(tr[1].c>=m){bk=true;break;}
			change(1,a[i].l,a[i].r,-1);
			while(i<n&&a[i].c==a[i+1].c)
			{
				i++;
				change(1,a[i].l,a[i].r,-1);
			}
		}
		if(bk)r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}
