#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int l,r,lc,rc;
	long long a,b,c;
}tr[210000];int len;
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].a=tr[now].b=tr[now].c=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
long long aa,bb,cc;
void change(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)
	{
		tr[now].a+=aa;tr[now].b+=bb;tr[now].c+=cc;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)change(lc,l,r);
	else if(l>=mid+1)change(rc,l,r);
	else change(lc,l,mid),change(rc,mid+1,r);
}
long long f(int now,int x)
{
    aa+=tr[now].a;bb+=tr[now].b;cc+=tr[now].c;
	if(tr[now].l==tr[now].r)return aa*x*x+bb*x+cc;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)return f(lc,x);
	else return f(rc,x);
}
int n,a[110000],c,k;
inline int mymin(int x,int y){return x<y?x:y;}
bool pand(int x)
{
	len=0;bt(1,n);
	int ss=0;
	for(int i=1;i<=n;i++)
	{
        aa=bb=cc=0;
		long long d=f(1,i);
		if(d<a[i])
		{
			if(c==0)
			{
				ss=ss+a[i]-d;
				if(ss>k)return false;
                aa=0;bb=0;cc=a[i]-d;
				change(1,i,mymin(i+x,n));
			}
			else if(c==1)
			{
				long long ct=(a[i]-d)/x+((a[i]-d)%x!=0);
				ss=ss+ct;
				if(ss>k)return false;
                aa=0;bb=-ct;cc=ct*(x+i);
				change(1,i,mymin(i+x-1,n));
			}
			else if(c==2)
			{
				long long ct=(a[i]-d)/(1ll*x*x)+((a[i]-d)%(1ll*x*x)!=0);
				ss=ss+ct;
				if(ss>k)return false;
                aa=ct;bb=-2*ct*(x+i);cc=1ll*ct*(x+i)*(x+i);
				change(1,i,mymin(i+x-1,n));
			}
		}
	}
	return true;
}
int main()
{
	freopen("dispersion.in","r",stdin);
	freopen("dispersion.out","w",stdout);
	scanf("%*d%d%d%d",&n,&c,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	if(k==0)
	{
		printf("-1\n");
		return 0;
	}
	if(c==0)
	{
		int m=0;
		for(int i=1;i<=n;i++)if(m<a[i])m=a[i];
		if(m>k)
		{
			printf("-1\n");return 0;
		}
	}
	int l=1,r;
	if(c==0)l=0,r=n;
	else if(c==1)r=n+1000000;
	else if(c==2)r=n+1000;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(pand(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}