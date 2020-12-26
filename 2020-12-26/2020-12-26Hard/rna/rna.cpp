#include<cstdio>
#include<cstring>
using namespace std;
int log_2[610000];
int a[610000];
int fa[610000][20],dep[610000];
int fail[610000];
int f[610000];
int root[610000];
struct node
{
	int l,r,lc,rc,c,cc;
}tr[16660000];int len;
int bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=tr[now].cc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=bt(l,mid);
		tr[now].rc=bt(mid+1,r);
	}
	return now;
}
inline int plus(int x,int y){return x+y<998244353?x+y:x+y-998244353;}
void change(int &now,int x,int c)
{
	tr[++len]=tr[now];now=len;
	if(tr[now].l==tr[now].r){tr[now].c=c;tr[now].cc=f[c];return ;}
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(tr[now].lc,x,c);
	else change(tr[now].rc,x,c);
	tr[now].cc=plus(tr[tr[now].lc].cc,tr[tr[now].rc].cc);
}
int query(int now,int x)
{
	if(tr[now].l==tr[now].r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)return query(lc,x);
	else return query(rc,x);
}
int findk(int x,int k)
{
	for(int i=0;i<=log_2[k];i++)if(k&1<<i)x=fa[x][i];
	return x;
}
char opt[11];
int main()
{
	freopen("rna.in","r",stdin);
	freopen("rna.out","w",stdout);
	int id;scanf("%d",&id);
	if(id==1||id==2)return 0;
	log_2[0]=-1;
	for(int i=1;i<=600000;i++)log_2[i]=log_2[i/2]+1;
	int n,L,q,enc;scanf("%d%d%d%d",&n,&L,&q,&enc);
	dep[0]=0;f[0]=0;
	len=0;root[0]=bt(0,2*n-1);
	scanf("%d",&a[1]);
	fa[1][0]=0;dep[1]=1;
	fail[1]=0;f[1]=2*n;
	root[1]=root[0];change(root[1],a[1],1);
	for(int i=2;i<=L;i++)
	{
		scanf("%d",&a[i]);
		for(int j=0;j<=log_2[i];j++)fa[i][j]=i-(1<<j);
		dep[i]=i;
		fail[i]=query(root[i-1],a[i]);
		f[i]=(2ll*n*(f[i-1]+1)-tr[root[i-1]].cc+f[fail[i]]+998244353)%998244353;
		root[i]=root[fail[i]];
		change(root[i],a[fail[i]+1],fail[i]+1);
	}
	int tot=L+1,ans=0;
	while(q--)
	{
		int ff,g;scanf("%s%d%d",opt+1,&ff,&g);
		if(opt[1]=='A')
		{
			ff=L+ff;
			g=(g+enc*ans)%(2*n);
			a[tot]=g;
			fa[tot][0]=ff;dep[tot]=dep[ff]+1;
			for(int i=1;i<=log_2[dep[tot]];i++)fa[tot][i]=fa[fa[tot][i-1]][i-1];
			fail[tot]=query(root[ff],g);
			f[tot]=(2ll*n*(f[ff]+1)-tr[root[ff]].cc+f[fail[tot]]+998244353)%998244353;
			root[tot]=root[fail[tot]];
			int fk=findk(tot,dep[tot]-dep[fail[tot]]-1);
			change(root[tot],a[fk],fk);
			tot++;
		}
		else
		{
			ff=L+ff;
			g=(g+enc*ans)%(dep[ff]+1);
			printf("%lld\n",ans=(f[ff]-f[findk(ff,dep[ff]-g)]+998244353)%998244353);
		}
	}
	return 0;
}