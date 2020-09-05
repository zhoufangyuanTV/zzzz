#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[51000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int list[51000];
int dep[51000];
int tc[51000];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int k;scanf("%d",&k);
		int x;scanf("%d",&x);
		for(int j=2;j<=k;j++)
		{
			int y;scanf("%d",&y);
			ins(x,y);ins(y,x);
			x=y;
		}
	}
	int ss=0,tick=0;
	memset(tc,0,sizeof(tc));
	while(tick<=10000)
	{
		tick++;
		dep[tick]=0;tc[tick]=tick;
		int head=1,tail=2;
		list[1]=tick;
		while(head<tail)
		{
			int x=list[head];
			for(int k=last[x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(tc[y]!=tick)
				{
					tc[y]=tick;
					dep[y]=dep[x]+1;
					list[tail++]=y;
				}
			}
			head++;
		}
		if(dep[list[tail-1]]>ss)ss=dep[list[tail-1]];
		tick++;
		int Q1=list[tail-1];
		dep[Q1]=0;tc[Q1]=tick;
		head=1;tail=2;
		list[1]=Q1;
		while(head<tail)
		{
			int x=list[head];
			for(int k=last[x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(tc[y]!=tick)
				{
					tc[y]=tick;
					dep[y]=dep[x]+1;
					list[tail++]=y;
				}
			}
			head++;
		}
		if(dep[list[tail-1]]>ss)ss=dep[list[tail-1]];
	}
	printf("%d\n",ss);
	return 0;
}