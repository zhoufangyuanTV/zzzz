#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct node
{
	int x,y,c,next;
}a[610];int len,last[310];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
inline long long mymin(long long x,long long y){return x<y?x:y;}
long long f[610][610],dis[610];
bool b[610];
struct pq
{
	int x,t;
	long long d;
};
inline bool operator<(pq x,pq y){return x.d<y.d;}
priority_queue<pq> Q;
long long Ans[610];
int main()
{
	//freopen("travel.in","r",stdin);
	//freopen("travel.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	memset(dis,63,sizeof(dis));
	dis[1]=0;
	memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		int x;long long ff=0x3f3f3f3f3f3f3f3fll;
		for(int j=1;j<=n;j++)
		{
			if(b[j]==false&&dis[j]<ff)x=j,ff=dis[j];
		}
		b[x]=true;
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			dis[y]=mymin(dis[y],ff+a[k].c);
		}
	}
	for(int i=1;i<=n;i++)Ans[i]=dis[n];
	for(int tt=1;tt<len;tt+=2)
	{
		memset(f,63,sizeof(f));
		f[1][0]=0;
		while(!Q.empty())Q.pop();
		Q.push((pq){1,0,0});
		while(!Q.empty())
		{
			pq ff=Q.top();Q.pop();
			if(f[ff.x][ff.t]<ff.d)continue;
			for(int k=last[ff.x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(a[k].c>=a[tt].c)
				{
					if(ff.d+a[k].c<f[y][ff.t+1])
					{
						f[y][ff.t+1]=ff.d+a[k].c;
						Q.push((pq){y,ff.t+1,ff.d+a[k].c});
					}
				}
				if(a[k].c<=a[tt].c)
				{
					if(ff.d+a[k].c<f[y][ff.t])
					{
						f[y][ff.t]=ff.d+a[k].c;
						Q.push((pq){y,ff.t,ff.d+a[k].c});
					}
				}
			}
		}
		for(int i=1;i<=n;i++)Ans[i]=mymin(Ans[i],f[n][i]);
	}
	for(int i=1;i<=n;i++)printf("%lld\n",Ans[i]);
	return 0;
}