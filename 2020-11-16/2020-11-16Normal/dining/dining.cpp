#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[31000];int len,last[2100];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int d[2100];
bool b[2100];
int list[2100];
long long f[2100][2100],g[2100];
int in[2100];
bool mp[2100][2100];
int main()
{
	freopen("dining.in","r",stdin);
	freopen("dining.out","w",stdout);
	int n,m,s,t;scanf("%d%d%d%d",&n,&m,&s,&t);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);
	}
	memset(d,63,sizeof(d));d[s]=0;
	memset(b,false,sizeof(b));b[s]=true;
	int head=1,tail=2;list[1]=s;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(d[x]+a[k].c<d[y])
			{
				d[y]=d[x]+a[k].c;
				if(b[y]==false)
				{
					b[y]=true;
					list[tail++]=y;
				}
			}
		}
		head++;
		b[x]=false;
	}
	memset(g,0,sizeof(g));
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)f[i][i]=1;
	memset(in,0,sizeof(in));
	for(int i=1;i<=m;i++)
	{
		int x=a[i].x,y=a[i].y;
		if(d[x]+a[i].c==d[y])in[y]++;
	}
	head=1;tail=1;
	for(int i=1;i<=n;i++)
	{
		if(in[i]==0)list[tail++]=i;
	}
	memset(mp,false,sizeof(mp));
	while(head<tail)
	{
		int x=list[head];
		g[x]=f[s][x]*f[s][x]%1000000009;
		for(int i=1;i<=n;i++)
		{
			if(i!=x&&i!=s)g[x]=(g[x]-g[i]*f[i][x]%1000000009*f[i][x]%1000000009+1000000009)%1000000009;
		}
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(d[x]+a[k].c==d[y])
			{
				if(mp[x][y]==false)
				{
					mp[x][y]=true;
					for(int i=1;i<=n;i++)f[i][y]=(f[i][y]+f[i][x])%1000000009;
				}
				in[y]--;
				if(in[y]==0)list[tail++]=y;
			}
		}
		head++;
	}
	printf("%lld\n",(g[t]+mp[s][t])*500000005%1000000009);
	return 0;
}