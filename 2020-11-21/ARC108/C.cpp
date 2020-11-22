#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int col[110000];
void dfs(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(col[y]==0)
		{
			if(col[x]!=a[k].c)col[y]=a[k].c;
			else if(col[x]!=1)col[y]=1;
			else col[y]=2;
			dfs(y);
		}
	}
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len++;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	col[1]=1;dfs(1);
	for(int i=1;i<=n;i++)printf("%d\n",col[i]);
	return 0;
}