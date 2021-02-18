#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int n,f[310000],siz[310000],root[310000];
int findzx(int x){return f[x]==x?x:f[x]=findzx(f[x]);}
struct node{int x,y;}list[310000];int head,tail;
struct trnode
{
	int l,r,lc,rc,c;
}tr[12010000];int trlen;
void ins(int now,int w,int y)
{
	if(tr[now].l==tr[now].r)
	{
		if(tr[now].c==-1)tr[now].c=y;
		else
		{
			int fx=findzx(tr[now].c),fy=findzx(y);
			if(fx!=fy)
			{
				if(siz[fx]<siz[fy])
				{
					f[fx]=fy;
					siz[fy]+=siz[fx];
					list[tail++]=(node){fy,fx};
				}
				else
				{
					f[fy]=fx;
					siz[fx]+=siz[fy];
					list[tail++]=(node){fx,fy};
				}
			}
		}
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(w<=mid)
	{
		if(lc==-1)
		{
			lc=tr[now].lc=++trlen;
			tr[lc].l=tr[now].l;tr[lc].r=mid;tr[lc].lc=tr[lc].rc=tr[lc].c=-1;
		}
		ins(lc,w,y);
	}
	else
	{
		if(rc==-1)
		{
			rc=tr[now].rc=++trlen;
			tr[rc].l=mid+1;tr[rc].r=tr[now].r;tr[rc].lc=tr[rc].rc=tr[rc].c=-1;
		}
		ins(rc,w,y);
	}
}
int merge(int x,int y)
{
	if(x==-1||y==-1)return x+y+1;
	if(tr[x].l==tr[x].r)
	{
		if(tr[x].c==-1||tr[y].c==-1)tr[x].c=tr[x].c+tr[y].c+1;
		else
		{
			int fx=findzx(tr[x].c),fy=findzx(tr[y].c);
			if(fx!=fy)
			{
				if(siz[fx]<siz[fy])
				{
					f[fx]=fy;
					siz[fy]+=siz[fx];
					list[tail++]=(node){fy,fx};
				}
				else
				{
					f[fy]=fx;
					siz[fx]+=siz[fy];
					list[tail++]=(node){fx,fy};
				}
			}
		}
	}
	tr[x].lc=merge(tr[x].lc,tr[y].lc);
	tr[x].rc=merge(tr[x].rc,tr[y].rc);
	return x;
}
int main()
{
	freopen("bracket.in","r",stdin);
	freopen("bracket.out","w",stdout);
	int m,k;read(n);read(m);read(k);
	head=tail=1;trlen=0;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;siz[i]=1;
		trlen++;root[i]=trlen;
		tr[trlen].l=1;tr[trlen].r=k;tr[trlen].lc=tr[trlen].rc=tr[trlen].c=-1;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,c;read(x);read(y);read(c);
		ins(root[y],c,x);
	}
	while(head<tail)
	{
		int x=list[head].x,y=list[head].y;
		root[x]=merge(root[x],root[y]);
		head++;
	}
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		if(f[i]==i)ss=ss+1ll*siz[i]*(siz[i]-1)/2;
	}
	printf("%lld\n",ss);
	return 0;
}
