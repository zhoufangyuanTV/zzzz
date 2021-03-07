#include<cstdio>
#include<cstring>
using namespace std;
int Ka,c[110000];
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
struct value{int val,p;};
struct trnode
{
	int l,r,lc,rc;
	value c,cc;
}tr[1210000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c.val=tr[now].cc.val=0xc0c0c0c0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	if(tr[lc].c.val>tr[rc].c.val)
	{
		tr[x].c=tr[lc].c;
		if(tr[lc].cc.val>tr[rc].c.val)tr[x].cc=tr[lc].cc;
		else tr[x].cc=tr[rc].c;
	}
	else
	{
		tr[x].c=tr[rc].c;
		if(tr[lc].c.val>tr[rc].cc.val)tr[x].cc=tr[lc].c;
		else tr[x].cc=tr[rc].cc;
	}
}
void change(int now,int x,int c,int p)
{
	if(tr[now].l==tr[now].r){tr[now].c=(value){c,p};return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(lc,x,c,p);
	else change(rc,x,c,p);
	update(now);
}
bool leaf[110000];
int rk[110000],rt[110000][7];
int fa[110000],f[110000][7],g[110000];
inline int mymax(int x,int y){return x>y?x:y;}
void treedp(int x)
{
	int cnt=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])rk[y]=++cnt;
	}
	if(cnt==0)
	{
		leaf[x]=true;
		f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=f[x][6]=0xc0c0c0c0;
		g[x]=f[x][Ka];
		change(1,x,g[x],x);
	}
	for(int i=1;i<Ka;i++){rt[x][i]=trlen+1;bt(1,cnt);}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			treedp(y);
			for(int i=1;i<Ka;i++)change(rt[x][i],rk[y],f[y][i],y);
		}
	}
	f[x][1]=c[x];
	for(int i=2;i<=Ka;i++)f[x][i]=tr[rt[x][i-1]].c.val+c[x];
	g[x]=f[x][Ka];
	for(int i=1;i<=Ka-2;i++)
	{
		if(tr[rt[x][i]].c.p==tr[rt[x][Ka-i-1]].c.p)g[x]=mymax(g[x],tr[rt[x][i]].c.val+tr[rt[x][Ka-i-1]].cc.val+c[x]);
		else g[x]=mymax(g[x],tr[rt[x][i]].c.val+tr[rt[x][Ka-i-1]].c.val+c[x]);
	}
	change(1,x,g[x],x);
}
int main()
{
	freopen("overwatch.in","r",stdin);
	freopen("overwatch.out","w",stdout);
	int n,m;scanf("%d%d%d",&n,&m,&Ka);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	trlen=0;bt(1,n);
	memset(leaf,false,sizeof(leaf));
	fa[1]=0;treedp(1);
	printf("%d\n",tr[1].c.val<-106110956?-1:tr[1].c.val);
	while(m--)
	{
		int x,cc;scanf("%d%d",&x,&cc);
		c[x]=cc;
		f[x][1]=c[x];
		if(!leaf[x])for(int i=2;i<=Ka;i++)f[x][i]=tr[rt[x][i-1]].c.val+c[x];
		g[x]=f[x][Ka];
		for(int i=1;i<=Ka-2;i++)
		{
			if(tr[rt[x][i]].c.p==tr[rt[x][Ka-i-1]].c.p)g[x]=mymax(g[x],tr[rt[x][i]].c.val+tr[rt[x][Ka-i-1]].cc.val+c[x]);
			else g[x]=mymax(g[x],tr[rt[x][i]].c.val+tr[rt[x][Ka-i-1]].c.val+c[x]);
		}
		change(1,x,g[x],x);
		int gg=1;
		while(x!=1&&gg<Ka)
		{
			int y=x;x=fa[x];gg++;
			for(int i=1;i<Ka;i++)change(rt[x][i],rk[y],f[y][i],y);
			f[x][1]=c[x];
			for(int i=2;i<=Ka;i++)f[x][i]=tr[rt[x][i-1]].c.val+c[x];
			g[x]=f[x][Ka];
			for(int i=1;i<=Ka-2;i++)
			{
				if(tr[rt[x][i]].c.p==tr[rt[x][Ka-i-1]].c.p)g[x]=mymax(g[x],tr[rt[x][i]].c.val+tr[rt[x][Ka-i-1]].cc.val+c[x]);
				else g[x]=mymax(g[x],tr[rt[x][i]].c.val+tr[rt[x][Ka-i-1]].c.val+c[x]);
			}
			change(1,x,g[x],x);
		}
		printf("%d\n",tr[1].c.val<-106110956?-1:tr[1].c.val);
	}
	return 0;
}