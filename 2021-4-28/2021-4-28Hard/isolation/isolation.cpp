#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct point
{
	int x,y;
}p[110000];
int pp[110000];
inline bool cmp3(int x,int y){return p[x].y<p[y].y;}
struct edge
{
	int x,y;
}e[1010000];
inline int mymax(int x,int y){return x>y?x:y;}
inline bool cmp1(edge x,edge y){return mymax(p[x.x].y,p[x.y].y)<mymax(p[y.x].y,p[y.y].y);}
struct Query
{
	int lx,ly,rx,ry,p;
}Q[110000];
inline bool cmp2(Query x,Query y){return x.ry<y.ry;}
int fa[110000];
int findfa(int x){return x==fa[x]?x:fa[x]=findfa(fa[x]);}
int main()
{
	freopen("isolation.in","r",stdin);
	freopen("isolation.out","w",stdout);
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
	for(int i=1;i<=m;i++)scanf("%d%d",&e[i].x,&e[i].y);
	for(int i=1;i<=q;i++)scanf("%d%d%d%d",&Q[i].lx,&Q[i].ly,&Q[i].rx,&Q[i].ry);
	if(n<=1000&&q<=1000)
	{
		for(int i=1;i<=q;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(Q[i].lx<=p[j].x&&Q[i].ly<=p[j].y&&p[j].x<=Q[i].rx&&p[j].y<=Q[i].ry)fa[j]=j;
				else fa[j]=0;
			}
			for(int j=1;j<=m;j++)
			{
				if(fa[e[j].x]!=0&&fa[e[j].y]!=0)
				{
					int fx=findfa(e[j].x),fy=findfa(e[j].y);
					if(fx!=fy)fa[fx]=fy;
				}
			}
			int ss=0;
			for(int j=1;j<=n;j++)ss+=fa[j]==j;
			printf("%d\n",ss);
		}
	}
	bool bk1=true;
	for(int i=1;i<=q;i++)
	{
		if(Q[i].lx!=0||Q[i].ly!=0||Q[i].rx!=1000000000){bk1=false;break;}
	}
	if(bk1)
	{
		for(int i=1;i<=q;i++)Q[i].p=i;
		sort(e+1,e+m+1,cmp1);
		sort(Q+1,Q+q+1,cmp2);
		sort(pp+1,pp+n+1,cmp3);
		int j=1,k=1,ss=0;
		for(int i=1;i<=q;i++)
		{
			while(k<=n&&p[pp[k]].y<=Q[i].ry)
			{
				fa[pp[k]]=pp[k];
				k++;
			}
			while(j<=m&&p[e[j].x].y<=Q[i].ry&&p[e[j].y].y<=Q[i].ry)
			{
				int fx=findfa(e[j].x),fy=findfa(e[j].y);
				if(fx!=fy)ss++,fa[fx]=fy;
				j++;
			}
			printf("%d\n",k-1-ss);
		}
	}
	return 0;
}
