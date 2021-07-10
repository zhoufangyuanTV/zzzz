#include<cstdio>
#include<cstring>
using namespace std;
template<int n,int m>
struct matrix
{
	long long a[n][m];
};
template<int n,int nm,int m>
inline matrix<n,m> operator*(matrix<n,nm> x,matrix<nm,m> y)
{
	matrix<n,m> z;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			z.a[i][j]=0;
			for(int k=0;k<nm;k++)z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%998244353;
		}
	}
	return z;
}
struct node
{
	int l,r,lc,rc;
	matrix<3,3> c;
	void vv(long long,long long,long long);
}tr[110000];int len;
void node::vv(long long p,long long a,long long b)
{
	c.a[0][0]=1;c.a[0][1]=c.a[0][2]=0;
	c.a[1][0]=b*p%998244353;c.a[1][1]=((a-1)*p+1)%998244353;c.a[1][2]=0;
	c.a[2][0]=b*b%998244353*p%998244353;c.a[2][1]=2*a*b%998244353*p%998244353;c.a[2][2]=((a*a-1)%998244353*p+1)%998244353;
}
long long p[51000],a[51000],b[51000];
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		tr[now].c=tr[tr[now].rc].c*tr[tr[now].lc].c;
	}
	else tr[now].vv(p[l],a[l],b[l]);
}
void change(int now,int x)
{
	if(tr[now].l==tr[now].r){tr[now].vv(p[x],a[x],b[x]);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(lc,x);
	else change(rc,x);
	tr[now].c=tr[rc].c*tr[lc].c;
}
matrix<3,1> query(int now,int l,int r,matrix<3,1> c)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c*c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return query(lc,l,r,c);
	else if(l>=mid+1)return query(rc,l,r,c);
	else return query(rc,mid+1,r,query(lc,l,mid,c));
}
int main()
{
	freopen("bet.in","r",stdin);
	freopen("bet.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&p[i],&a[i],&b[i]);
		p[i]%=998244353;
	}
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if(opt==0)
		{
			int x;scanf("%d",&x);
			scanf("%lld%lld%lld",&p[x],&a[x],&b[x]);
			p[x]%=998244353;
			change(1,x);
		}
		else
		{
			int l,r;long long x;scanf("%d%d%lld",&l,&r,&x);
			matrix<3,1> c;
			c.a[0][0]=1;c.a[1][0]=x;c.a[2][0]=x*x%998244353;
			c=query(1,l,r,c);
			if(opt==1)printf("%lld\n",c.a[1][0]);
			else printf("%lld\n",(c.a[2][0]-c.a[1][0]*c.a[1][0]%998244353+998244353)%998244353);
		}
	}
	return 0;
}
