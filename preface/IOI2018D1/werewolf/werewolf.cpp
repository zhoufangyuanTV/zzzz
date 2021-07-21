#include"werewolf.h"
#include<cmath>
#include<algorithm>
using namespace std;
struct node
{
	int x,y;
}a[410000],b[410000];
inline bool cmp1(node x,node y){return min(x.x,x.y)>min(y.x,y.y);}
inline bool cmp2(node x,node y){return max(x.x,x.y)<max(y.x,y.y);}
struct Query{int st,ed,l,r,p;}Q[210000];
inline bool cmp3(Query x,Query y){return x.l>y.l;}
inline bool cmp4(Query x,Query y){return x.r<y.r;}
vector<int> Ans[210000];
int block,blk[410000];
vector<Query> Que[510];
struct bing
{
	int fa[210000],siz[210000];
	int f(int x){return fa[x]==x?x:fa[x]=f(fa[x]);}
	void he(int,int);
}A,B;
void bing::he(int x,int y)
{
	int fx=f(x),fy=f(y);
	if(fx!=fy)
	{
		if(siz[fx]<siz[fy])
		{
			fa[fx]=fy;
			siz[fy]+=siz[fx];
		}
		else
		{
			fa[fy]=fx;
			siz[fx]+=siz[fy];
		}
	}
}
struct edge
{
	int x,y,next;
}e[810000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;e[len].x=x;e[len].y=y;
	e[len].next=last[x];last[x]=len;
}
bool v[210000];
void dfs(int x)
{
	v[x]=true;
	for(int k=last[x];k>0;k=e[k].next)
	{
		int y=e[k].y;
		if(v[y]==false)dfs(y);
	}
}
vector<int> check_validity(int n,vector<int> X,vector<int> Y,vector<int> S,vector<int> E,vector<int> L,vector<int> R)
{
	int m=x.size(),q=st.size();
	for(int i=0;i<m;i++)a[i+1].x=b[i+1].x=X[i]+1,a[i+1].y=b[i+1].y=Y[i]+1;
	sort(a+1,a+m+1,cmp1);
	sort(b+1,b+m+1,cmp2);
	for(int i=0;i<q;i++)Q[i+1]=(Query){S[i]+1,E[i]+1,L[i]+1,R[i]+1,i};
	int j=1;
	sort(Q+1,Q+q+1,cmp3);
	for(int i=1;i<=q;i++)
	{
		while(j<=m&&Q[i].l<=min(a[j].x,a[j].y))j++;
		Q[i].l=j-1;
	}
	j=1;
	sort(Q+1,Q+q+1,cmp4);
	for(int i=1;i<=q;i++)
	{
		while(j<=m&&max(b[j].x,b[j].y)<=Q[i].r)j++;
		Q[i].r=j-1;
	}
	block=sqrt(n);
	for(int i=0;i<=m;i++)blk[i]=i/block+1;
	for(int i=1;i<=q;i++)Que[blk[Q[i].l]].push_back(Q[i]);
	for(int i=1;i<=n;i++)A.fa[i]=i,A.siz[i]=1;
	memset(v,false,sizeof(v));
	for(int i=1;i<=blk[m];i++)
	{
		if(i>1)
		{
			for(int j=(i-2)*block+1;j<=(i-1)*block;j++)A.he(a[j].x,a[j].y);
		}
		sort(Que[i].begin(),Que[i].end(),cmp4);
		for(int j=1;j<=n;j++)B.fa[i]=i,B.siz[i]=1;
		int p=1;
		for(int j=0;j<Que[i].size();j++)
		{
			Query g=Que[i][j];
			while(p<=g.r)
			{
				B.he(A.f(b[p].x),A.f(b[p].y));
				p++;
			}
			Ans[g.p]=0;
			if(B.f(A.f(g.st))==B.f(A.f(g.ed)))Ans[g.p]=1;
			else
			{
				len=0;
				for(int k=(i-1)*block+1;k<=g.l;k++)
				{
					ins(A.f(a[k].x),A.f(a[k].y));
					ins(A.f(a[k].y),A.f(a[k].x));
				}
				dfs(A.f(g.st));
				v[A.f(g.st)]=false;
				for(int k=(i-1)*block+1;k<=g.l;k++)
				{
					last[A.f(a[k].x)]=0;
					last[A.f(a[k].y)]=0;
					if(v[A.f(a[k].x)])
					{
						v[A.f(a[k].x)]=false;
						if(B.f(A.f(a[k].x))==B.f(A.f(g.ed)))Ans[g.p]=1;
					}
					if(v[A.f(a[k].y)])
					{
						v[A.f(a[k].y)]=false;
						if(B.f(A.f(a[k].y))==B.f(A.f(g.ed)))Ans[g.p]=1;
					}
				}
			}
		}
	}
}
