#include<cstdio>
#include<cstring>
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
int c[110000],g;
int cnt[210000];
long long ss=0;
void dfs1(int x,int fa)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			int gg=g-c[y];
			if(-10000<=gg&&gg<=10000)ss+=cnt[gg+10000];
			dfs1(y,x);
		}
	}
}
void dfs2(int x,int fa)
{
	g=c[x];dfs1(x,fa);
	cnt[c[x]+10000]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs2(y,x);
	}
	cnt[c[x]+10000]--;
}
int cp[110000],p[110000],ctt[210000];
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	memset(p,0,sizeof(p));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
		p[x]++;p[y]++;
	}
	bool bk=true;
	for(int i=1;i<=n;i++)if(p[i]>2){bk=false;break;}
	if(p[1]!=1)bk=false;
	memset(ctt,0,sizeof(ctt));
	memset(cnt,0,sizeof(cnt));
	if(bk==true)
	{
		p[0]=0;p[1]=1;
		for(int i=1;i<n;i++)
		{
			for(int k=last[p[i]];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(y!=p[i-1])p[i+1]=y;
			}
		}
		for(int i=1;i<=n;i++)cp[i]=c[i];
		for(int i=1;i<=n;i++)c[i]=cp[p[i]];
		for(int i=1;i<=n;i++)ctt[c[i]+1000]++;
		for(int i=1;i<=n;i++)
		{
			ctt[c[i]+1000]--;
			for(int j=-1000;j<=1000;j++)
			{
				int k=c[i]-j;
				if(-1000<=k&&k<=1000)ss+=1ll*cnt[j+1000]*ctt[k+1000];
			}
			cnt[c[i]+1000]++;
		}
	}
	else dfs2(1,0);
	printf("%lld\n",ss);
	return 0;
}