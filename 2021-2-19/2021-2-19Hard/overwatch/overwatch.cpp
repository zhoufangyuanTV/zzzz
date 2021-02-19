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
int K,c[110000],ss;
void dfs(int x,int fa,int dep,int s)
{
	if(dep==K)
	{
		if(ss<s)ss=s;
		return ;
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,dep+1,s+c[y]);
	}
}
int ff[110000],f[110000][7],g[110000];
inline int mymax(int x,int y){return x>y?x:y;}
void treedp(int x)
{
	f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=0xc0c0c0c0;
	g[x]=0xc0c0c0c0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=ff[x])
		{
			ff[y]=x;
			treedp(y);
			for(int i=1;i<5;i++)g[x]=mymax(g[x],f[y][i]+f[x][K-i]);
			for(int i=1;i<5;i++)f[x][i+1]=mymax(f[x][i+1],f[y][i]+c[x]);
		}
	}
	g[x]=mymax(g[x],f[x][K]);
}
int gg[110000];
int main()
{
	freopen("overwatch.in","r",stdin);
	freopen("overwatch.out","w",stdout);
	int n,q;scanf("%d%d%d",&n,&q,&K);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	memset(gg,0,sizeof(gg));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
		gg[x]++;gg[y]++;
	}
	int gs=0;
	for(int i=1;i<=n;i++)if(gg[i]==0)gs++;
	if(gs<=100)
	{
		ff[1]=0;treedp(1);
		ss=0xc0c0c0c0;
		for(int i=1;i<=n;i++)ss=mymax(ss,g[i]);
		if(ss<-10611095)ss=-1;
		printf("%d\n",ss);
		for(int i=1;i<=q;i++)
		{
			int x,w;scanf("%d%d",&x,&w);
			c[x]=w;
			f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=0xc0c0c0c0;
			g[x]=0xc0c0c0c0;
			for(int k=last[x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(y!=ff[x])
				{
					ff[y]=x;
					treedp(y);
					for(int i=1;i<5;i++)g[x]=mymax(g[x],f[y][i]+f[x][K-i]);
					for(int i=1;i<5;i++)f[x][i+1]=mymax(f[x][i+1],f[y][i]+c[x]);
				}
			}
			g[x]=mymax(g[x],f[x][k]);
			if(x!=1)
			{
				x=ff[x];
				f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=0xc0c0c0c0;
				g[x]=0xc0c0c0c0;
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(y!=ff[x])
					{
						ff[y]=x;
						treedp(y);
						for(int i=1;i<5;i++)g[x]=mymax(g[x],f[y][i]+f[x][K-i]);
						for(int i=1;i<5;i++)f[x][i+1]=mymax(f[x][i+1],f[y][i]+c[x]);
					}
				}
				g[x]=mymax(g[x],f[x][k]);
				if(x!=1)
				{
					x=ff[x];
					f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=0xc0c0c0c0;
					g[x]=0xc0c0c0c0;
					for(int k=last[x];k>0;k=a[k].next)
					{
						int y=a[k].y;
						if(y!=ff[x])
						{
							ff[y]=x;
							treedp(y);
							for(int i=1;i<5;i++)g[x]=mymax(g[x],f[y][i]+f[x][K-i]);
							for(int i=1;i<5;i++)f[x][i+1]=mymax(f[x][i+1],f[y][i]+c[x]);
						}
					}
					g[x]=mymax(g[x],f[x][k]);
					if(x!=1)
					{
						x=ff[x];
						f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=0xc0c0c0c0;
						g[x]=0xc0c0c0c0;
						for(int k=last[x];k>0;k=a[k].next)
						{
							int y=a[k].y;
							if(y!=ff[x])
							{
								ff[y]=x;
								treedp(y);
								for(int i=1;i<5;i++)g[x]=mymax(g[x],f[y][i]+f[x][K-i]);
								for(int i=1;i<5;i++)f[x][i+1]=mymax(f[x][i+1],f[y][i]+c[x]);
							}
						}
						g[x]=mymax(g[x],f[x][k]);
						if(x!=1)
						{
							x=ff[x];
							f[x][1]=c[x];f[x][2]=f[x][3]=f[x][4]=f[x][5]=0xc0c0c0c0;
							g[x]=0xc0c0c0c0;
							for(int k=last[x];k>0;k=a[k].next)
							{
								int y=a[k].y;
								if(y!=ff[x])
								{
									ff[y]=x;
									treedp(y);
									for(int i=1;i<5;i++)g[x]=mymax(g[x],f[y][i]+f[x][K-i]);
									for(int i=1;i<5;i++)f[x][i+1]=mymax(f[x][i+1],f[y][i]+c[x]);
								}
							}
							g[x]=mymax(g[x],f[x][K]);
						}
					}
				}
			}
			ss=0xc0c0c0c0;
			for(int i=1;i<=n;i++)ss=mymax(ss,g[i]);
			if(ss<-10611095)ss=-1;
			printf("%d\n",ss);
		}
	}
	ss=0xc0c0c0c0;
	for(int i=1;i<=n;i++)dfs(i,0,1,c[i]);
	printf("%d\n",ss==0xc0c0c0c0?-1:ss);
	for(int i=1;i<=q;i++)
	{
		int x,w;scanf("%d%d",&x,&w);c[x]=w;
		ss=0xc0c0c0c0;
		for(int i=1;i<=n;i++)dfs(i,0,1,c[i]);
		printf("%d\n",ss==0xc0c0c0c0?-1:ss);
	}
	return 0;
}