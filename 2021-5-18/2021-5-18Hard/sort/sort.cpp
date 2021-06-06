#include<cstdio>
#include<cstring>
#include<bitset>
#include<queue>
using namespace std;
struct node
{
	int x,y,c,next,other;
}a[1100];int len,last[310];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[len-1].other=len;
	a[len].other=len-1;
}
int st,ed;
int dep[310];
int list[310];
bool build()
{
	memset(dep,-1,sizeof(dep));dep[st]=1;
	int head=1,tail=2;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(a[k].c>0&&dep[y]==-1)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed]!=-1;
}
int cur[310];
bool b[310];
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==ed)return f;
	if(b[x]==false)return 0;
	int used=0;
	for(int &k=cur[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(a[k].c>0&&dep[x]+1==dep[y]&&used<f)
		{
			int tt=find(y,mymin(a[k].c,f-used));
			used+=tt;
			a[k].c-=tt;
			a[a[k].other].c+=tt;
			if(used==f)break;
		}
	}
	if(used==0)b[x]=false;
	return used;
}
bool col[310];
void colour(int x)
{
	col[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(a[k].c>0&&col[y]==false)colour(y);
	}
}
struct bf
{
	bitset<101> T,F,S;
	int f;
	void calc();
};
inline bool operator<(const bf &x,const bf &y){return x.f>y.f;}
priority_queue<bf> Q;
int c[110];
struct tri
{
	int x,y,w;
}e[110];
int n,m;
void bf::calc()
{
	st=n+m+1;ed=n+m+2;
	len=0;memset(last,0,sizeof(last));
	f=0;
	for(int i=1;i<=n;i++)
	{
		if(T[i])f+=c[i];
		else if(F[i])ins(st,i,0x3f3f3f3f);
		else ins(st,i,c[i]);
	}
	for(int i=1;i<=m;i++)
	{
		ins(e[i].x,n+i,0x3f3f3f3f);
		ins(e[i].y,n+i,0x3f3f3f3f);
		ins(n+i,ed,e[i].w);
	}
	while(build())
	{
		for(int i=1;i<=n+m+2;i++)cur[i]=last[i];
		memset(b,true,sizeof(b));
		f+=find(st,0x3f3f3f3f);
	}
	memset(col,false,sizeof(col));
	colour(st);
	for(int i=1;i<=n;i++)
	{
		if(!col[i]&&!T[i]&&!F[i])S[i]=1;
		else S[i]=0;
	}
}
int main()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
	int k;scanf("%d",&k);
	int ss=0;
	for(int i=1;i<=n;i++)ss+=c[i];
	bf fst;
	fst.T.reset();
	fst.F.reset();
	fst.calc();
	Q.push(fst);
	for(int i=1;i<=k;i++)
	{
		bf x=Q.top();Q.pop();
		printf("%d%c",ss-x.f,i==k?'\n':' ');
		bitset<101> G=x.T,H=x.F;
		for(int j=1;j<=n;j++)
		{
			if(!x.T[j]&&!x.F[j])
			{
				bf y;
				y.T=G;
				y.F=H;
				if(x.S[j])
				{
					y.F[j]=1;
					G[j]=1;
				}
				else
				{
					y.T[j]=1;
					H[j]=1;
				}
				y.calc();
				Q.push(y);
			}
		}
	}
	return 0;
}