#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,next;
	unsigned long long c;
}a[210000];int len,last[110000];
inline void ins(int x,int y,unsigned long long c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int n,fa[110000],dep[110000],son[110000],tot[110000];
unsigned long long cl[110000];
void dfs(int x)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			cl[y]=a[k].c;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
int z,ys[110000],yss[110000],top[110000];
void dfs(int x,int tp)
{
	ys[x]=++z;yss[z]=x;top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
	}
}
int rt[110000];
struct trnode
{
	int l,r,lc,rc;
	unsigned long long c,cc;
}tr[210000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].cc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
		tr[now].c=tr[tr[now].lc].c+tr[tr[now].rc].c;
	}
	else tr[now].c=cl[yss[l]];
}
void change(int now,int l,int r,unsigned long long c)
{
	if(tr[now].l==l&&tr[now].r==r)
	{
		tr[now].c+=c*(r-l+1);
		tr[now].cc+=c;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	tr[now].c=tr[now].cc*(tr[now].r-tr[now].l+1)+tr[lc].c+tr[rc].c;
}
unsigned long long findsum(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return tr[now].cc*(r-l+1)+findsum(lc,l,r);
	else if(l>=mid+1)return tr[now].cc*(r-l+1)+findsum(rc,l,r);
	else return tr[now].cc*(r-l+1)+findsum(lc,l,mid)+findsum(rc,mid+1,r);
}
inline void cd(int x,int y,unsigned long long c)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			change(rt[top[y]],ys[top[y]],ys[y],c);
			y=fa[top[y]];
		}
		else
		{
			change(rt[top[x]],ys[top[x]],ys[x],c);
			x=fa[top[x]];
		}
	}
	if(x!=y)
	{
		if(dep[x]<dep[y])change(rt[top[x]],ys[x]+1,ys[y],c);
		else change(rt[top[x]],ys[y]+1,ys[x],c);
	}
}
inline unsigned long long dis(int x,int y)
{
	unsigned long long s=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			s+=findsum(rt[top[y]],ys[top[y]],ys[y]);
			y=fa[top[y]];
		}
		else
		{
			s+=findsum(rt[top[x]],ys[top[x]],ys[x]);
			x=fa[top[x]];
		}
	}
	if(x==y)return s;
	else
	{
		if(dep[x]<dep[y])return s+findsum(rt[top[x]],ys[x]+1,ys[y]);
		else return s+findsum(rt[top[x]],ys[y]+1,ys[x]);
	}
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])y=fa[top[y]];
		else x=fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	else return y;
}
int sta[110000],op;
vector<int> e[110000];
vector<unsigned long long> ev[110000];
bool b[110000],B[110000];
int siz[110000];
void fsiz(int x,int fa)
{
	siz[x]=1;
	for(int i=0;i<e[x].size();i++)
	{
		int y=e[x][i];
		if(b[y]&&y!=fa)
		{
			fsiz(y,x);
			siz[x]+=siz[y];
		}
	}
}
int ce,ff,size;
void fce(int x,int fa)
{
	int f=size-siz[x];
	for(int i=0;i<e[x].size();i++)
	{
		int y=e[x][i];
		if(b[y]&&y!=fa)
		{
			fce(y,x);
			if(f<siz[y])f=siz[y];
		}
	}
	if(f<ff)ce=x,ff=f;
}
int L,R;
unsigned long long cf[110000],cg[110000];
inline int lowbit(int x){return x&-x;}
inline void change(unsigned long long c[],int x,unsigned long long s)
{
	while(x<=n)
	{
		c[x]+=s;
		x+=lowbit(x);
	}
}
inline unsigned long long sum(unsigned long long c[],int x)
{
	unsigned long long s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
inline void clean(unsigned long long c[],int x)
{
	while(x<=n&&c[x]>0)
	{
		c[x]=0;
		x+=lowbit(x);
	}
}
unsigned long long ss;
inline int ddp(int x,int y){return dep[x]<dep[y]?dep[y]-dep[x]:dep[x]-dep[y];}
void calc(int x,int fa,int dep,unsigned long long d)
{
	if(B[x])
	{
		if(dep<=L)ss+=sum(cf,R-dep+1)-sum(cf,L-dep)+d*(sum(cg,R-dep+1)-sum(cg,L-dep));
		else if(dep<=R)ss+=sum(cf,R-dep+1)+d*sum(cg,R-dep+1);
	}
	for(int i=0;i<e[x].size();i++)
	{
		int y=e[x][i];
		if(b[y]&&y!=fa)calc(y,x,dep+ddp(x,y),d+ev[x][i]);
	}
}
void stt(int x,int fa,int dep,unsigned long long d)
{
	if(B[x])
	{
		change(cf,dep,d);
		change(cg,dep,1);
	}
	for(int i=0;i<e[x].size();i++)
	{
		int y=e[x][i];
		if(b[y]&&y!=fa)stt(y,x,dep+ddp(x,y),d+ev[x][i]);
	}
}
void clean(int x,int fa,int dep)
{
	clean(cf,dep);
	clean(cg,dep);
	for(int i=0;i<e[x].size();i++)
	{
		int y=e[x][i];
		if(b[y]&&y!=fa)clean(y,x,dep+ddp(x,y));
	}
}
void div(int x)
{
	fsiz(x,0);
	size=siz[x];
	ff=0x3f3f3f3f;
	fce(x,0);
	int root=ce;
	if(B[root])change(cg,1,1);
	for(int i=0;i<e[root].size();i++)
	{
		int y=e[root][i];
		if(b[y])
		{
			calc(y,root,ddp(root,y),ev[root][i]);
			stt(y,root,1+ddp(root,y),ev[root][i]);
		}
	}
	clean(cg,1);
	for(int i=0;i<e[root].size();i++)
	{
		int y=e[root][i];
		if(b[y])clean(y,root,1+ddp(root,y));
	}
	b[root]=false;
	for(int i=0;i<e[root].size();i++)
	{
		int y=e[root][i];
		if(b[y])div(y);
	}
}
inline bool cmp(int x,int y){return ys[x]<ys[y];}
int p[110000];
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;unsigned long long c;scanf("%d%d%llu",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	z=0;dfs(1,1);
	trlen=0;
	for(int i=1;i<=n;i++)
	{
		int l=i;
		while(i<n&&yss[l]==top[yss[i+1]])i++;
		rt[yss[l]]=trlen+1;
		bt(l,i);
	}
	for(int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if(opt==1)
		{
			int x,y;unsigned long long c;scanf("%d%d%llu",&x,&y,&c);
			cd(x,y,c);
		}
		else
		{
			int k;scanf("%d%d%d",&L,&R,&k);
			for(int j=1;j<=k;j++)scanf("%d",&p[j]);
			sort(p+1,p+k+1,cmp);
			sta[op=1]=p[1];
			e[p[1]].clear();
			ev[p[1]].clear();
			b[p[1]]=true;
			for(int j=2;j<=k;j++)
			{
				int lc=lca(sta[op],p[j]);
				int lst=-1;
				while(op>0&&dep[lc]<dep[sta[op]])
				{
					if(lst!=-1)
					{
						unsigned long long d=dis(sta[op],lst);
						e[sta[op]].push_back(lst);
						ev[sta[op]].push_back(d);
						e[lst].push_back(sta[op]);
						ev[lst].push_back(d);
					}
					lst=sta[op];
					op--;
				}
				if(op>0&&lc==sta[op])
				{
					if(lst!=-1)
					{
						unsigned long long d=dis(sta[op],lst);
						e[sta[op]].push_back(lst);
						ev[sta[op]].push_back(d);
						e[lst].push_back(sta[op]);
						ev[lst].push_back(d);
					}
					sta[++op]=p[j];
					e[p[j]].clear();
					ev[p[j]].clear();
					b[p[j]]=true;
				}
				else
				{
					e[lc].clear();
					ev[lc].clear();
					b[lc]=true;
					e[p[j]].clear();
					ev[p[j]].clear();
					b[p[j]]=true;
					unsigned long long d=dis(lc,lst);
					e[lc].push_back(lst);
					ev[lc].push_back(d);
					e[lst].push_back(lc);
					ev[lst].push_back(d);
					sta[++op]=lc;
					sta[++op]=p[j];
				}
			}
			for(int j=1;j<op;j++)
			{
				unsigned long long d=dis(sta[j],sta[j+1]);
				e[sta[j]].push_back(sta[j+1]);
				ev[sta[j]].push_back(d);
				e[sta[j+1]].push_back(sta[j]);
				ev[sta[j+1]].push_back(d);
			}
			ss=0;
			for(int j=1;j<=k;j++)B[p[j]]=true;
			div(sta[1]);
			for(int j=1;j<=k;j++)B[p[j]]=false;
			printf("%llu\n",ss);
		}
	}
	return 0;
}