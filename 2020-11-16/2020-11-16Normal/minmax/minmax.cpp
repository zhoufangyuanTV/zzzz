#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long ss=0,s;int kk;
bool b[210000];
int tot[210000];
void count(int x,int fa)
{
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			count(y,x);
			tot[x]+=tot[y];
		}
	}
}
int ce,ff,size;
void find(int x,int fa)
{
	int f=size-tot[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			find(y,x);
			if(f<tot[y])f=tot[y];
		}
	}
	if(f<ff)ce=x,ff=f;
}
struct minimax{int x,y;}p[210000];int plen;
inline bool cmp(minimax x,minimax y){return x.x>y.x;}
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
void dfs(int x,int fa,int minn,int maxx)
{
	if(maxx-minn>kk)return ;
	if(maxx-minn==kk)s++;
	p[++plen]=(minimax){minn,maxx};
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			int mi=mymin(minn,a[k].c),ma=mymax(maxx,a[k].c);
			dfs(y,x,mi,ma);
		}
	}
}
inline int lowbit(int x){return x&-x;}
int n,c[210000],cr[410000];
inline void change(int x,int cc)
{
	while(x<=n)
	{
		c[x]+=cc;
		x+=lowbit(x);
	}
}
inline int sum(int x)
{
	int cc=0;
	while(x>0)
	{
		cc+=c[x];
		x-=lowbit(x);
	}
	return cc;
}
void div(int x)
{
	count(x,0);
	ff=0x3f3f3f3f;
	size=tot[x];
	find(x,0);
	s=0;
	plen=0;
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])dfs(y,ce,a[k].c,a[k].c);
	}
	sort(p+1,p+plen+1,cmp);
	for(int i=1;i<=plen;i++)
	{
		if(p[i].y-p[i].x==kk)s=s+sum(p[i].y);
		else s=s+cr[p[i].x+kk];
		change(p[i].y,1);
		cr[p[i].y]++;
	}
	ss=ss+s;
	for(int i=1;i<=plen;i++)change(p[i].y,-1),cr[p[i].y]--;
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])
		{
			plen=0;
			dfs(y,ce,a[k].c,a[k].c);
			s=0;
			sort(p+1,p+plen+1,cmp);
			for(int i=1;i<=plen;i++)
			{
				if(p[i].y-p[i].x==kk)s=s+sum(p[i].y);
				else s=s+cr[p[i].x+kk];
				change(p[i].y,1);
				cr[p[i].y]++;
			}
			ss=ss-s;
			for(int i=1;i<=plen;i++)change(p[i].y,-1),cr[p[i].y]--;
		}
	}
	b[ce]=false;
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])div(y);
	}
}
int main()
{
	freopen("minmax.in","r",stdin);
	freopen("minmax.out","w",stdout);
	scanf("%d%d",&n,&kk);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	memset(b,true,sizeof(b));
	div(1);
	printf("%lld\n",ss);
	return 0;
}