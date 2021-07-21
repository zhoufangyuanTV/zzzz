#include<cstdio>
#include<cstring>
using namespace std;
struct edge
{
	int x,y;
}e[2010000];
struct node
{
	int x,y,next;
}a[4010000];int len,last[2100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,d[2100][2100];
int list[2100];
void bfs(int st)
{
	for(int i=1;i<=n;i++)d[st][i]=0x3f3f3f3f;
	int head=1,tail=2;list[1]=st;d[st][st]=0;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(d[st][y]==0x3f3f3f3f)
			{
				d[st][y]=d[st][x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
}
int f[2100];
int main()
{
	int m;scanf("%d%d%*d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&e[i].x,&e[i].y);
	int s=0x3f3f3f3f;
	for(int i=1;i<=m;i++)
	{
		len=0;for(int i=1;i<=n;i++)last[i]=0;
		for(int j=1;j<=m;j++)
		{
			if(i!=j)
			{
				ins(e[j].x,e[j].y);
				ins(e[j].y,e[j].x);
			}
		}
		bfs(e[i].x);
		f[i]=d[e[i].x][e[i].y];
		if(f[i]<s)s=f[i];
	}
	printf("%d\n",s+m-1);
	int ss=0;
	for(int i=1;i<=m;i++)
	{
		if(f[i]==s)
		{
			ss=(ss+1)%1000000007;
			for(int j=i+1;j<=m;j++)
			{
				if(f[j]==s)
				{
					len=0;for(int i=1;i<=n;i++)last[i]=0;
					for(int k=1;k<=m;k++)
					{
						if(i!=k&&j!=k)
						{
							ins(e[k].x,e[k].y);
							ins(e[k].y,e[k].x);
						}
					}
					bfs(e[i].x);
					bfs(e[i].y);
					int x=e[j].x,y=e[j].y;
					if(d[e[i].x][y]+d[e[i].y][x]+1==s)x^=y^=x^=y;
					if(d[e[i].x][x]+d[e[i].y][y]+1==s)
					{
						bfs(x);bfs(y);
						int sx=0,sy=0;
						for(int k=1;k<=n;k++)
						{
							if(d[e[i].x][k]+d[x][k]==d[e[i].x][x])sx++;
							if(d[e[i].y][k]+d[y][k]==d[e[i].y][y])sy++;
						}
						ss=(ss+1ll*sx*sy+1000000005)%1000000007;
					}
				}
			}
		}
	}
	printf("%d\n",ss);
	return 0;
}