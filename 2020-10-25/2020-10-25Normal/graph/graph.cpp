#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[410];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool b[410];
int sta1[410],sta2[410];
int Ans[110000];
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int n,m,s,t;scanf("%d%d%d%d",&n,&m,&s,&t);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(Ans,0,sizeof(Ans));
	memset(b,false,sizeof(b));
	int top1=1;sta1[1]=s;b[s]=true;
	int ss=1;
	while(ss<n)
	{
		int top2=0;
		while(top1>0)
		{
			int x=sta1[top1--];
			for(int k=last[x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(Ans[(k+1)/2]==0)Ans[(k+1)/2]=ss;
				if(b[y]==false)
				{
					b[y]=true;
					sta2[++top2]=y;
				}
			}
		}
		while(top2>0)
		{
			sta1[++top1]=sta2[top2--];
			if(sta1[top1]==t)
			{
				printf("%d\n",ss);
				for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
				return 0;
			}
		}
		ss++;
	}
}