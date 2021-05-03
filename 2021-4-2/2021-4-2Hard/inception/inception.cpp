#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int e[110000],elen;
int L2[110000];
int fa[110000][17],dep[110000],h[110000];
int f[110000][17],g[110000][17],ord[110000],reo[110000];
inline int mymax(int x,int y){return x>y?x:y;}
int z,in[110000],out[110000];
void dfs(int x)
{
	in[x]=++z;
	h[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0])
		{
			fa[y][0]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(h[x]<h[y]+1)h[x]=h[y]+1;
		}
	}
	elen=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0])e[++elen]=y;
	}
	ord[0]=reo[elen+1]=0xc0c0c0c0;
	for(int i=1;i<=elen;i++)ord[i]=mymax(ord[i-1],h[e[i]]);
	for(int i=elen;i>=1;i--)reo[i]=mymax(reo[i+1],h[e[i]]);
	for(int i=1;i<=elen;i++)
	{
		f[e[i]][0]=mymax(ord[i-1],reo[i+1])+dep[x];
		g[e[i]][0]=mymax(ord[i-1],reo[i+1])-dep[x];
	}
	out[x]=z;
}
void init(int x)
{
	for(int i=1;i<=L2[dep[x]];i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
		f[x][i]=mymax(f[x][i-1],f[fa[x][i-1]][i-1]);
		g[x][i]=mymax(g[x][i-1],g[fa[x][i-1]][i-1]);
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0])init(y);
	}
}
inline int lca(int x,int y)
{
	if(dep[x]<dep[y])x^=y^=x^=y;
	for(int i=L2[dep[x]-dep[y]];i>=0;i--)
	{
		if(1<<i<=dep[x]-dep[y])x=fa[x][i];
	}
	if(x==y)return x;
	for(int i=L2[dep[x]];i>=0;i--)
	{
		if(1<<i<=dep[x]&&fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];y=fa[y][i];
		}
	}
	return fa[x][0];
}
inline int FA(int x,int k)
{
	for(int i=0;k>0;k>>=1,i++)
	{
		if(k&1)x=fa[x][i];
	}
	return x;
}
inline int F(int x,int k)
{
	int s=0xc0c0c0c0;
	for(int i=0;k>0;k>>=1,i++)
	{
		if(k&1)
		{
			s=mymax(s,f[x][i]);
			x=fa[x][i];
		}
	}
	return s;
}
inline int G(int x,int k)
{
	int s=0xc0c0c0c0;
	for(int i=0;k>0;k>>=1,i++)
	{
		if(k&1)
		{
			s=mymax(s,g[x][i]);
			x=fa[x][i];
		}
	}
	return s;
}
int p[110000],plen;
inline bool cmp(int x,int y){return in[x]<in[y];}
int sta[110000],top;
int d[110000];
inline int mymin(int x,int y){return x<y?x:y;}
void treedp(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		treedp(y);
		d[x]=mymin(d[x],d[y]+dep[y]-dep[x]);
	}
}
void treedp(int x,int df)
{
	d[x]=mymin(d[x],df);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		treedp(y,d[x]+dep[y]-dep[x]);
	}
}
int biao[110000][17];
inline void st(int n)
{
	for(int i=1;i<=L2[n];i++)
	{
		for(int j=1;j<=n-(1<<i)+1;j++)
		{
			biao[j][i]=mymax(biao[j][i-1],biao[j+(1<<i-1)][i-1]);
		}
	}
}
inline int st(int l,int r)
{
	int LL=L2[r-l+1];
	return mymax(biao[l][LL],biao[r-(1<<LL)+1][LL]);
}
int ss;
void FL(int x)
{
	int left=out[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		FL(y);
		int son=FA(y,dep[y]-dep[x]-1);
		if(out[son]<left)ss=mymax(ss,d[x]+st(out[son]+1,left)-dep[x]);
		left=in[son]-1;
		int kth=(d[x]-d[y]+dep[y]-dep[x])/2;
		ss=mymax(ss,d[y]+kth);
		int mid=FA(y,kth);
		if(mid==x)kth--;
		ss=mymax(ss,d[y]+dep[y]+G(y,kth));
		ss=mymax(ss,d[x]-dep[x]+F(mid,dep[y]-dep[x]-kth-1));
	}
	ss=mymax(ss,d[x]+st(in[x],left)-dep[x]);
}
int main()
{
	freopen("inception.in","r",stdin);
	freopen("inception.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	z=0;
	dep[1]=0;dfs(1);
	L2[0]=-1;
	for(int i=1;i<=n;i++)L2[i]=L2[i>>1]+1;
	init(1);
	for(int i=1;i<=n;i++)biao[in[i]][0]=dep[i];
	st(z);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&plen);
		for(int j=1;j<=plen;j++)scanf("%d",&p[j]);
		sort(p+1,p+plen+1,cmp);
		len=0;
		last[1]=0;
		sta[1]=1;top=1;
		d[1]=0x3f3f3f3f;
		for(int j=1;j<=plen;j++)
		{
			if(p[j]==1)continue;
			last[p[j]]=0;
			int lst=-1;
			while(out[sta[top]]<in[p[j]])
			{
				if(lst!=-1)ins(sta[top],lst);
				lst=sta[top--];
			}
			if(lst!=-1)
			{
				int np=lca(lst,p[j]);
				if(np!=sta[top])
				{
					last[np]=0;
					sta[++top]=np;
					d[np]=0x3f3f3f3f;
				}
				ins(np,lst);
			}
			sta[++top]=p[j];
		}
		for(int j=1;j<top;j++)ins(sta[j],sta[j+1]);
		for(int j=1;j<=plen;j++)d[p[j]]=0;
		treedp(1);treedp(1,0x3f3f3f3f);
		ss=0xc0c0c0c0;
		FL(1);
		printf("%d\n",ss);
	}
	return 0;
}