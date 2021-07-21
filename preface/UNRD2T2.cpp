#include<cstdio>
#include<cstring>
using namespace std;
typedef __uint128_t u128;
inline u128 read() {
    static char buf[100];
    scanf("%s", buf);
    // std::cin >> buf;
    u128 res = 0;
    for(int i = 0;buf[i];++i) {
        res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);
    }
    return res;
}
inline void output(u128 res) {
    if(res >= 16)
        output(res / 16);
    putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
    //std::cout.put(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}
struct node
{
	int l,r,lc,rc;
	u128 c,fi;
}tr[610000];int len;
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].c=tr[lc].c+tr[rc].c;
	tr[x].fi=tr[lc].fi|tr[rc].fi;
}
u128 a[310000];
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l+64<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else
	{
		tr[now].c=tr[now].fi=0;
		for(int i=l;i<=r;i++)
		{
			tr[now].c+=a[i];
			tr[now].fi|=a[i];
		}
	}
}
void change1(int now,int l,int r,u128 c)
{
	if(tr[now].fi==0)return ;
	if(tr[now].r<=tr[now].l+64)
	{
		for(int i=l;i<=r;i++)a[i]/=c;
		tr[now].c=tr[now].fi=0;
		for(int i=tr[now].l;i<=tr[now].r;i++)
		{
			tr[now].c+=a[i];
			tr[now].fi|=a[i];
		}
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)change1(lc,l,r,c);
	else if(l>=mid+1)change1(rc,l,r,c);
	else change1(lc,l,mid,c),change1(rc,mid+1,r,c);
	update(now);
}
void change2(int now,int l,int r,u128 c)
{
	if((tr[now].fi|c)==c)return ;
	if(tr[now].r<=tr[now].l+64)
	{
		for(int i=l;i<=r;i++)a[i]&=c;
		tr[now].c=tr[now].fi=0;
		for(int i=tr[now].l;i<=tr[now].r;i++)
		{
			tr[now].c+=a[i];
			tr[now].fi|=a[i];
		}
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)change2(lc,l,r,c);
	else if(l>=mid+1)change2(rc,l,r,c);
	else change2(lc,l,mid,c),change2(rc,mid+1,r,c);
	update(now);
}
u128 findsum(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	if(tr[now].r<=tr[now].l+64)
	{
		u128 c=0;
		for(int i=l;i<=r;i++)c+=a[i];
		return c;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return findsum(lc,l,r);
	else if(l>=mid+1)return findsum(rc,l,r);
	else return findsum(lc,l,mid)+findsum(rc,mid+1,r);
}
struct Query{int opt,l,r;u128 c;}Q[210000];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)a[i]=read();
	bool bk=true;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&Q[i].opt,&Q[i].l,&Q[i].r);
		if(Q[i].opt==1||Q[i].opt==2)Q[i].c=read();
		if(Q[i].l!=1)bk=false;
		if(Q[i].r!=n)bk=false;
	}
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		if(Q[i].opt==1)
		{
			if(Q[i].c>1)change1(1,Q[i].l,Q[i].r,Q[i].c);
		}
		else if(Q[i].opt==2)change2(1,Q[i].l,Q[i].r,Q[i].c);
		else
		{
			output(findsum(1,Q[i].l,Q[i].r));
			putchar('\n');
		}
	}
	return 0;
}