#include<cstdio>
#include<cstring>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
inline bool equal(long double x,long double y){return x-y<1e-15&&y-x<1e-15;}
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,fa[110000],dep[110000],son[110000],tot[110000];
void dfs(int x)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
int z,ys[110000],top[110000];
void dfs(int x,int tp)
{
	ys[x]=++z;top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
	}
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])dep[top[x]]<dep[top[y]]?y=fa[top[y]]:x=fa[top[x]];
	return dep[x]<dep[y]?x:y;
}
struct trnode{int l,r;long double lc,rc;};
inline bool operator<(trnode x,trnode y)
{
	if(equal(x.lc,y.lc))return x.l<y.l;
	else if(equal(x.lc,x.rc))x.l<y.l+(y.r-y.l)/(y.rc-y.lc)*(x.lc-y.lc);
	else return x.l+(x.r-x.l)/(x.rc-x.lc)*(y.lc-x.lc)<y.l;
}
inline bool cmpl(trnode x,trnode y){return x.lc<y.lc;}
inline bool cmpr(trnode x,trnode y){return x.rc<y.rc;}
vector<trnode> va[210000],vc;
void solve(int x,int y,long double xc,long double yc,long double c)
{
	int tx=top[x],ty=top[y];
	while(tx!=ty)
	{
		if(dep[tx]<dep[ty])
		{
			va[ty].push_back((trnode){ys[ty],ys[y],yc-(ys[y]-ys[ty])/c,yc});
			yc=yc-(ys[y]-ys[ty])/c;
			y=fa[ty];
			va[n+ty].push_back((trnode){ys[y],ys[ty],yc-1/c,yc});
			yc=yc-1/c;
			ty=top[y];
		}
		else
		{
			va[tx].push_back((trnode){ys[x],ys[tx],xc,xc+(ys[x]-ys[tx])/c});
			xc=xc+(ys[x]-ys[tx])/c;
			x=fa[tx];
			va[n+tx].push_back((trnode){ys[tx],ys[x],xc,xc+1/c});
			xc=xc+1/c;
			tx=top[x];
		}
	}
	va[tx].push_back((trnode){ys[x],ys[y],xc,yc});
}
multiset<trnode> S;
int main()
{
	int m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	z=0;dfs(1,1);
	for(int i=1;i<=m;i++)
	{
		int x,y;double xc,c;
		scanf("%lf%lf%d%d",&xc,&c,&x,&y);
		solve(x,y,xc,xc+(long double)(dep[x]+dep[y]-dep[lca(x,y)]*2)/c,c);
	}
	long double ss=1e6;
	for(int i=1;i<=n*2;i++)
	{
		sort(va[i].begin(),va[i].end(),cmpl);
		vc=va[i];
		sort(vc.begin(),vc.end(),cmpr);
		int k=0;
		S.clear();
		for(int j=0;j<va[i].size();j++)
		{
			if(ss<va[i][j].lc)break;
			while(k<vc.size()&&va[i][j].lc-vc[k].rc>1e-15){S.erase(vc[k]);k++;}
			set<trnode>::iterator it=S.insert(va[i][j]);
			if(it!=S.begin())
			{
				it--;
				if(equal((*it).lc,(*it).rc))
				{
					if(equal((*it).lc,va[i][j].lc)&&equal((*it).l,va[i][j].l)&&(*it).lc<ss)ss=(*it).lc;
				}
				else
				{
					long double xx=(*it).l+((*it).r-(*it).l)/((*it).rc-(*it).lc)*(va[i][j].lc-(*it).lc);
					if(equal(va[i][j].lc,va[i][j].rc))
					{
						if(equal(xx,va[i][j].l)&&va[i][j].lc<ss)ss=va[i][j].lc;
					}
					else if(equal((va[i][j].r-va[i][j].l)/(va[i][j].rc-va[i][j].lc),((*it).r-(*it).l)/((*it).rc-(*it).lc)))
					{
						if(equal(xx,va[i][j].l)&&va[i][j].lc<ss)ss=va[i][j].lc;
					}
					else
					{
						long double t=va[i][j].lc+(xx-va[i][j].l)/((va[i][j].r-va[i][j].l)/(va[i][j].rc-va[i][j].lc)-((*it).r-(*it).l)/((*it).rc-(*it).lc));
						if(t-va[i][j].rc<1e-15&&t-(*it).rc<1e-15&&t<ss)ss=t;
					}
				}
				it++;
			}
			it++;
			if(it!=S.end())
			{
				if(equal((*it).lc,(*it).rc))
				{
					if(equal((*it).lc,va[i][j].lc)&&equal((*it).l,va[i][j].l)&&(*it).lc<ss)ss=(*it).lc;
				}
				else
				{
					long double xx=(*it).l+((*it).r-(*it).l)/((*it).rc-(*it).lc)*(va[i][j].lc-(*it).lc);
					if(equal(va[i][j].lc,va[i][j].rc))
					{
						if(equal(xx,va[i][j].l)&&va[i][j].lc<ss)ss=va[i][j].lc;
					}
					else if(equal((va[i][j].r-va[i][j].l)/(va[i][j].rc-va[i][j].lc),((*it).r-(*it).l)/((*it).rc-(*it).lc)))
					{
						if(equal(xx,va[i][j].l)&&va[i][j].lc<ss)ss=va[i][j].lc;
					}
					else
					{
						long double t=va[i][j].lc+(xx-va[i][j].l)/((va[i][j].r-va[i][j].l)/(va[i][j].rc-va[i][j].lc)-((*it).r-(*it).l)/((*it).rc-(*it).lc));
						if(t-va[i][j].rc<1e-15&&t-(*it).rc<1e-15&&t<ss)ss=t;
					}
				}
			}
		}
	}
	if(equal(ss,1e6))printf("-1\n");
	else printf("%.9lf\n",(double)ss);
	return 0;
}