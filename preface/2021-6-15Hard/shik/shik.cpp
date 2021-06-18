#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
template<typename T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int ss=0;
unsigned S1,S2;
unsigned rnd()
{
	S1*=S2,S2>>=S1&13,S2-=S1,S1^=S2;
	return ((S1-S2)&(S1+S2))^(S1*S2>>4);
}
struct node
{
	int x,y,next;
}a[4010000];int len,last[2010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fr[2010000],to[2010000];
int n,fa[2010000],dep[2010000],son[2010000],tot[2010000];
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
int top[2010000];
void dfs(int x,int tp)
{
	top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
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
vector<int> e[2010000];
int fg[2010000];
void bf(int x)
{
	int stash=fg[fr[x]];
	fg[fr[x]]=x;
	e[fg[to[x]]].push_back(x);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])bf(y);
	}
	fg[fr[x]]=stash;
}
int z,Z[710000];
vector<int> Q[2010000],A[2010000],ns[2010000];
int sta[2010000],p;
void Qs(int x)
{
	sta[++p]=x;
	for(int i=0;i<Q[x].size();i++)
	{
		int cf=lca(x,Q[x][i]);
		int l=1,r=p;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(dep[cf]<=dep[sta[mid]])r=mid;
			else l=mid+1;
		}
		Z[++z]=to[sta[r]];
		A[cf].push_back(z);
		ns[Q[x][i]].push_back(z);
	}
	for(int i=0;i<e[x].size();i++)Qs(e[x][i]);
	p--;
}
int f[710000],siz[710000],grand[2010000],ft[710000];
inline int findft(int x)
{
	while(f[x]!=x)x=f[x];
	return ft[x];
}
void Asnss(int x)
{
	int fx=grand[fr[x]],fy=grand[to[x]];
	int sx=fx==-1?-1:siz[fx],sy=fy==-1?-1:siz[fy];
	if(fx!=-1)
	{
		ft[fx]=to[x];
		if(fy==-1)grand[to[x]]=fx;
		else
		{
			if(sx<sy)
			{
				f[fx]=fy;
				siz[fy]+=sx;
			}
			else
			{
				grand[to[x]]=fx;
				f[fy]=fx;
				siz[fx]+=sy;
			}
		}
		grand[fr[x]]=-1;
	}
	for(int i=0;i<A[x].size();i++)
	{
		int id=A[x][i];
		if(grand[Z[id]]==-1)
		{
			grand[Z[id]]=id;
			ft[id]=Z[id];
			f[id]=id;
			siz[id]=1;
		}
		else
		{
			f[id]=grand[Z[id]];
			siz[f[id]]++;
		}
	}
	for(int i=0;i<ns[x].size();i++)ss^=findft(ns[x][i]);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])Asnss(y);
	}
	for(int i=A[x].size()-1;i>=0;i--)
	{
		int id=A[x][i];
		if(f[id]==id)grand[Z[id]]=-1;
		else siz[f[id]]--;
	}
	grand[fr[x]]=fx;
	grand[to[x]]=fy;
	if(fx!=-1)
	{
		ft[fx]=fr[x];
		f[fx]=fx;
		siz[fx]=sx;
	}
	if(fy!=-1)
	{
		f[fy]=fy;
		siz[fy]=sy;
	}
}
int main()
{
	freopen("shik.in","r",stdin);
	freopen("shik.out","w",stdout);
	int m;read(n);read(m);read(S1);read(S2);
	if(n<=500000)
	{
		for(int i=1;i<=n;i++)
		{
			read(fr[i]);read(to[i]);
		}
	}
	else
	{
		for(int i=1;i<=500000;i++)
		{
			read(fr[i]);read(to[i]);
		}
		for(int i=500001;i<=n;i++)
		{
			fr[i]=rnd()%n+1;
			to[i]=fr[rnd()%500000+1];
			if(fr[i]==to[i])
			{
				++fr[i];
				if(fr[i]>n)fr[i]=1;
			}
		}
	}
	len=0;memset(last,0,sizeof(last));
	for(int i=2;i<=n;i++)
	{
		int fi;read(fi);
		ins(fi,i);ins(i,fi);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	dfs(1,1);
	memset(fg,0,sizeof(fg));
	bf(1);
	for(int i=1;i<=m;i++)
	{
		int x,y;read(x);read(y);
		Q[x].push_back(y);
	}
	z=0;
	for(int i=0;i<e[0].size();i++)Qs(e[0][i]);
	memset(grand,-1,sizeof(grand));
	Asnss(1);
	printf("%d\n",ss);
	return 0;
}