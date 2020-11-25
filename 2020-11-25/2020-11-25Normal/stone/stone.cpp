#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,next;
}a[610000];int len,last[610000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int lg2[1210000],st[1210000][21];
int z,Euler[1210000],in[610000],out[610000];
int dep[610000],son[610000];
int ys[610000],yss[610000],top[610000];
struct L{int x,z;}list[610000];
inline int mylca(int x,int y){return dep[x]<dep[y]?x:y;}
void bst()
{
	for(int i=1;i<=z;i++)st[i][0]=Euler[i];
	for(int i=1;i<=lg2[z];i++)
	{
		for(int j=1;j<=z-(1<<i)+1;j++)
		{
			st[j][i]=mylca(st[j][i-1],st[j+(1<<i-1)][i-1]);
		}
	}
}
inline int lca(int x,int y)
{
	int l=out[x],r=in[y];
	if(l>r)l^=r^=l^=r;
	int lr=lg2[r-l+1];
	return mylca(st[l][lr],st[r-(1<<lr)+1][lr]);
}
int f[610000],g[310000];
inline int mymin(int x,int y){return x<y?x:y;}
int fi[610000],tot[610000],op[610000],po[610000];
int main()
{
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	lg2[0]=-1;
	for(int i=1;i<=1200000;i++)lg2[i]=lg2[i/2]+1;
	int n;read(n);
	len=0;memset(last,0,sizeof(last));
	memset(op,0,sizeof(op));
	for(int i=2;i<=n;i++)
	{
		int f;read(f);
		ins(f,n+i-1);
		ins(n+i-1,i);
		fi[n+i-1]=f;
		fi[i]=n+i-1;
		op[f]++;
		op[n+i-1]++;
	}
	int head=1,tail=1;
	for(int i=1;i<=2*n-1;i++)
	{
		son[i]=0;
		tot[i]=1;
		po[i]=op[i];
		if(op[i]==0)list[tail++].x=i;
	}
	while(head<tail)
	{
		int x=list[head].x;
		if(x!=1)
		{
			if(tot[son[fi[x]]]<tot[x])son[fi[x]]=x;
			tot[fi[x]]+=tot[x];
			op[fi[x]]--;
			if(op[fi[x]]==0)list[tail++].x=fi[x];
		}
		head++;
	}
	dep[1]=0;ys[1]=1;top[1]=1;
	head=1;tail=2;
	list[1]=(L){1,0};
	while(head<tail)
	{
		L x=list[head];
		Euler[++x.z]=x.x;
		in[x.x]=x.z;
		int sy=ys[x.x];
		yss[sy]=x.x;
		if(son[x.x]!=0)
		{
			dep[son[x.x]]=dep[x.x]+1;
			top[son[x.x]]=top[x.x];
			ys[son[x.x]]=sy+1;
			sy+=tot[son[x.x]];
			list[tail++]={son[x.x],x.z};
			x.z+=tot[son[x.x]]*2;
			Euler[x.z]=x.x;
		}
		for(int k=last[x.x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=son[x.x])
			{
				dep[y]=dep[x.x]+1;
				top[y]=y;
				ys[y]=sy+1;
				sy+=tot[y];
				list[tail++]={y,x.z};
				x.z+=tot[y]*2;
				Euler[x.z]=x.x;
			}
		}
		out[x.x]=x.z;
		head++;
	}
	z=2*tot[1]-1;bst();
	int q;read(q);
	memset(f,63,sizeof(f));
	for(int i=1;i<=q;i++)
	{
		int k;read(k);read(g[1]);
		int p=g[1],d=0;
		for(int j=2;j<=k;j++)
		{
			read(g[j]);
			int dd=dep[g[j]]+dep[g[1]]-2*dep[lca(g[j],g[1])];
			if(d<dd)p=g[j],d=dd;
		}
		int pp=p;d=0;
		for(int j=1;j<=k;j++)
		{
			int dd=dep[g[j]]+dep[p]-2*dep[lca(g[j],p)];
			if(d<dd)pp=g[j],d=dd;
		}
		int acl=lca(p,pp);d=d/2;
		if(d>dep[p]-dep[acl])p=pp;
		int dd=d;
		while(dep[p]-dep[top[p]]+1<=dd)
		{
			dd=dd-dep[p]+dep[top[p]]-1;
			p=fi[top[p]];
		}
		p=yss[ys[p]-dd];
		f[p]=mymin(f[p],d);
	}
	head=1;tail=1;
	for(int i=1;i<=2*n-1;i++)if(po[i]==0)list[tail++].x=i;
	while(head<tail)
	{
		int x=list[head].x;
		if(x!=1)
		{
			f[fi[x]]=mymin(f[fi[x]],f[x]+1);
			po[fi[x]]--;
			if(po[fi[x]]==0)list[tail++].x=fi[x];
		}
		head++;
	}
	head=1;tail=2;
	list[1].x=1;
	while(head<tail)
	{
		int x=list[head].x;
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			f[y]=mymin(f[y],f[x]+1);
			list[tail++].x=y;
		}
		head++;
	}
	for(int i=1;i<=n;i++)printf("%d\n",f[i]/2);
	return 0;
}