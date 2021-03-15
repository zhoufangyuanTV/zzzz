#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
char obuf[1<<26],*op=obuf;
template<typename T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void write(long long x)
{
	unsigned long long y=10;
	while(y<=x)y*=10;
	while(y!=1){y/=10;*op++=x/y+'0';x%=y;}
	*op++='\n';
}
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int d[1010000],son[1010000],h[1010000];
void dfs(int x,int fa)
{
	son[x]=0;h[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			d[y]=d[x]+1;
			dfs(y,x);
			if(h[son[x]]<h[y])son[x]=y;
			if(h[x]<h[y]+1)h[x]=h[y]+1;
		}
	}
}
int p[1010000];
int z,ys[1010000],yss[1010000];
void dfs1(int x,int fa,int dis)
{
	if(p[x]==1){z++;ys[z]=x;yss[x]=dis;}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs1(y,x,dis);
	}
}
void dfs2(int x,int fa,int dis)
{
	if(son[x]!=0)dfs2(son[x],x,dis+1);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&y!=son[x])dfs1(y,x,dis);
	}
}
long long cl[1010000],cr[1010000],dl[1010000],dr[1010000];
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	int n;read(n);
	memset(p,0,sizeof(p));
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);p[x]++;p[y]++;
	}
	d[1]=0;dfs(1,0);
	int x=1;
	while(son[x]!=0)x=son[x];
	d[x]=0;dfs(x,0);
	int y=x;
	while(son[y]!=0)y=son[y];
	z=0;dfs2(x,0,0);
	int j=1;
	for(int i=d[y]-1;i>=1;i--)
	{
		cl[i]=cr[i]=dl[i]=dr[i]=0;
		while(j<=z&&i==yss[ys[j]])
		{
			cl[i]++;cr[i]++;
			dl[i]+=d[ys[j]]+d[y]-i*2;
			dr[i]+=d[ys[j]];
			j++;
		}
	}
	cl[0]=dl[0]=0;
	for(int i=1;i<d[y];i++)cl[i]+=cl[i-1],dl[i]+=dl[i-1];
	cr[d[y]]=dr[d[y]]=0;
	for(int i=d[y]-1;i>=1;i--)cr[i]+=cr[i+1],dr[i]+=dr[i+1];
	int mg=yss[ys[(z+1)/2]];
	int q;read(q);
	while(q--)
	{
		long long in;read(in);
		if(z==0)write(in+d[y]);
		else
		{
			long long l=d[y],r=d[y]+(in+z-1)/z*2;
			while(l<r)
			{
				long long mid=(l+r)/2;
				long long R=(mid+1)/2,ss=mid-d[y];
				long long fenjie,xs,ys;
				if(mg<R-ss)fenjie=R-ss,xs=ss;
				else if(R<mg)fenjie=R,xs=0;
				else fenjie=mg,xs=R-mg;
				ys=ss-xs;
				ss=ss+mid*z-cl[fenjie-1]*ys-cr[fenjie]*xs-dl[fenjie-1]-dr[fenjie];
				if(in<=ss)r=mid;
				else l=mid+1;
			}
			write(r);
		}
	}
	fwrite(obuf,op-obuf,1,stdout);
	return 0;
}