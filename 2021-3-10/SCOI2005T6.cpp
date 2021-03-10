#include<cstdio>
#include<cstring>
using namespace std;
int block,blk[110000];
int cnt,ce[110000];
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int sta[110000],top;
void dfs(int x,int fa)
{
	int t=top;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			if(block<=top-t)
			{
				ce[++cnt]=x;
				while(top>t)blk[sta[top--]]=cnt;
			}
		}
	}
	sta[++top]=x;
}
int main()
{
	int n;scanf("%d%d",&n,&block);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	top=cnt=0;dfs(1,0);
	while(top>0)blk[sta[top--]]=cnt;
	printf("%d\n",cnt);
	for(int i=1;i<n;i++)printf("%d ",blk[i]);
	printf("%d\n",blk[n]);
	for(int i=1;i<cnt;i++)printf("%d ",ce[i]);
	printf("%d\n",ce[cnt]);
	return 0;
}