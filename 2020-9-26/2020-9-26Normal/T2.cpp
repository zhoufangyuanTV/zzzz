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
int k,ss=0;
bool b[110000];
void dfs(int x,int fa,int dep)
{
	b[x]=true;
	if(k<=dep)ss++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&b[y]==false)dfs(y,x,dep+1);
	}
	b[x]=false;
}
int main()
{
	int n,m;scanf("%d%d%d",&n,&m,&k);
	len++;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)dfs(i,0,1);
	printf("%d\n",ss/2);
	return 0;
}