#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();};
}
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int f[1010000][2];
inline int mymax(int x,int y){return x>y?x:y;}
void dfs(int x,int fa)
{
	f[x][1]=1;f[x][0]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			f[x][1]+=f[y][0];
			f[x][0]+=mymax(f[y][0],f[y][1]);
		}
	}
}
int ss=0,Ans[1010000];
void dfs(int x,int fa,bool bk)
{
	if(bk)Ans[++ss]=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(bk)dfs(y,x,false);
			else if(f[y][0]<f[y][1])dfs(y,x,true);
			else dfs(y,x,false);
		}
	}
}
int main(int argc,char* argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	int n,m;read(n);read(n);read(m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;read(x);read(y);
		if(i>1){ins(x,y);ins(y,x);}
	}
	dfs(1,0);
	int s=f[1][0];
	dfs(30005,0);
	if(s<f[30005][0])dfs(30005,0,false);
	else
	{
		dfs(1,0);
		dfs(1,0,false);
	}
	printf("%d\n",ss);
	for(int i=1;i<=ss;i++)printf("%d\n",Ans[i]);
	return 0;
}