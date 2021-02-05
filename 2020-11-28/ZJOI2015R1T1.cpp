#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[310000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int lg2[210000],st[210000][18];
int z,in[110000],out[110000];
int d[110000];
void dfs(int x,int fa)
{
	st[++z][0]=x;
	in[x]=z;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			d[y]=d[x]+a[k].c;
			dfs(y,x);
			st[++z][0]=x;
		}
	}
	out[x]=z;
}
inline int mymin(int x,int y){return d[x]<d[y]?x:y;}
void bst()
{
	for(int j=1;j<=lg2[z];j++)
	{
		for(int i=1;i<=z-(1<<j)+1;i++)
		{
			st[i][j]=mymin(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
inline int lca(int x,int y)
{
	int l=out[x],r=in[y];
	if(l>r)l^=r^=l^=r;
	int lr=lg2[r-l+1];
	return mymin(st[l][lr],st[r-(1<<lr)+1][lr]);
}
inline int dis(int x,int y){return d[x]+d[y]-2*d[lca(x,y)];}
bool b[110000];
int tot[110000];
void count(int x,int fa)
{
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			count(y,x);
			tot[x]+=tot[y];
		}
	}
}
int ce,ff,size;
inline int mymax(int x,int y){return x>y?x:y;}
void find(int x,int fa)
{
	int f=size-tot[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			find(y,x);
			f=mymax(f,tot[y]);
		}
	}
	if(f<ff)ce=x,ff=f;
}
int fa[110000],fs[110000];
int div(int x)
{
	count(x,0);
	ff=0x3f3f3f3f;
	size=tot[x];
	find(x,0);
	int rt=ce;
	b[rt]=false;
	int k=last[rt];
	last[rt]=0;
	for(;k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])
		{
			int son=div(y);
			ins(rt,son);
			fa[son]=rt;
			fs[son]=y;
		}
	}
	return rt;
}
long long f[110000],sf[110000],g[110000];
struct zuxian
{
	int x;
	long long g;
}pa[110000];int plen;
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	z=0;dfs(1,0);
	lg2[0]=-1;
	for(int i=1;i<=z;i++)lg2[i]=lg2[i/2]+1;
	bst();
	memset(b,true,sizeof(b));
	int root=div(1);
	fa[root]=0;
	fs[root]=1;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	for(int i=1;i<=m;i++)
	{
		int x;long long c;scanf("%d%lld",&x,&c);
		int p=x;
		while(p!=0)
		{
			f[p]=f[p]+c*dis(x,p);
			sf[p]=sf[p]+c*dis(x,fs[p]);
			g[p]=g[p]+c;
			p=fa[p];
		}
		p=root;
		plen=0;
		bool bk;
		long long ss=f[p],ff=0;
		do
		{
			bk=false;
			for(int k=last[p];k>0;k=a[k].next)
			{
				int y=a[k].y;
				long long gg=sf[y]+ff;
				for(int i=1;i<=plen;i++)gg=gg+pa[i].g*dis(pa[i].x,fs[y]);
				gg=gg+f[p]-sf[y]-g[y]*dis(p,fs[y])+(g[p]-g[y])*dis(p,fs[y]);
				if(gg<ss)
				{
					bk=true;
					pa[++plen]=(zuxian){p,g[p]-g[y]};
					ff=ff+f[p]-sf[y]-g[y]*dis(p,fs[y]);
					ss=f[y]+ff;
					for(int i=1;i<=plen;i++)ss=ss+pa[i].g*dis(pa[i].x,y);
					p=y;
					break;
				}
			}
		}while(bk);
		printf("%lld\n",ss);
	}
	return 0;
}