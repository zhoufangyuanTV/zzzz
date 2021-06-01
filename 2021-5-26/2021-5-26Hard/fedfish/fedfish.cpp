#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int Z[110000];
struct node
{
	int x,y,p;
}a[110000];
inline bool cmp1(node x,node y){return x.x<y.x;}
inline bool cmp2(node x,node y){return x.y>y.y;}
inline bool cmp3(node x,node y){return x.p<y.p;}
struct Query
{
	int x,y,p;
}Q[110000];
inline bool cmp4(Query x,Query y){return x.y<y.y;}
int Ans[110000];
int c1[110000],c2[110000];
int block,blk[110000];
vector<Query> Que[510];
int n,l[110000],r[110000];
bool b[110000];
struct gun
{
	int p,l,r;
	bool b;
}g[3100];int glen;
int ss;
inline int mymax(int x,int y){return x>y?x:y;}
inline void link(int x,bool bk)
{
	ss=mymax(ss,(x>1&&b[x-1]?x-l[x-1]:0)+1+(x<n&&b[x+1]?r[x+1]-x:0));
	if(bk)g[++glen]=(gun){x,x,x,false};
	b[x]=true;
	if(x>1&&b[x-1])
	{
		l[x]=l[x-1];
		if(bk)g[++glen]=(gun){l[x],l[x],x-1,true};
		r[l[x]]=x;
	}
	if(x<n&&b[x+1])
	{
		r[l[x]]=r[x+1];
		if(bk)g[++glen]=(gun){r[x+1],x+1,r[x+1],true};
		l[r[x+1]]=l[x];
	}
}
int main()
{
	freopen("fedfish.in","r",stdin);
	freopen("fedfish.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].p=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&Q[i].y,&Q[i].x);
		Q[i].p=i;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)
	{
		Z[i]=a[i].x;
		a[i].x=i;
		c1[i]=a[i].p;
	}
	for(int i=1;i<=m;i++)Q[i].x=upper_bound(Z+1,Z+n+1,Q[i].x)-Z-1;
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++)
	{
		Z[i]=-a[i].y;
		a[i].y=i;
		c2[i]=a[i].p;
	}
	for(int i=1;i<=m;i++)Q[i].y=upper_bound(Z+1,Z+n+1,-Q[i].y)-Z-1;
	sort(a+1,a+n+1,cmp3);
	block=sqrt(n);
	for(int i=1;i<=n;i++)blk[i]=(i-1)/block+1;
	for(int i=1;i<=m;i++)Que[blk[Q[i].x]].push_back(Q[i]);
	for(int i=1;i<=blk[n];i++)
	{
		for(int j=1;j<=n;j++)l[j]=r[j]=j,b[j]=false;
		glen=0;ss=0;
		sort(Que[i].begin(),Que[i].end(),cmp4);
		int k=1;
		for(int j=0;j<Que[i].size();j++)
		{
			while(k<=n&&k<=Que[i][j].y)
			{
				if(blk[a[c2[k]].x]<i)link(c2[k],false);
				k++;
			}
			int s=ss;
			for(int e=(i-1)*block+1;e<=Que[i][j].x;e++)
			{
				if(a[c1[e]].y<=Que[i][j].y)link(c1[e],true);
			}
			Ans[Que[i][j].p]=ss;
			ss=s;
			while(glen>0)
			{
				l[g[glen].p]=g[glen].l;
				r[g[glen].p]=g[glen].r;
				b[g[glen].p]=g[glen].b;
				glen--;
			}
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
