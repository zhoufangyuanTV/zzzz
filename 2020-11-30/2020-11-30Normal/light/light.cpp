#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,next;
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
inline long long mymin(long long x,long long y){return x<y?x:y;}
long long f[510000][2],g[510000];
char str[510000];
bool b[510000];
void bb(int x,int fa)
{
	b[x]=str[x]=='1';
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			bb(y,x);
			b[x]&=b[y];
		}
	}
}
int c[510000];
void dfs(int x,int fa)
{
	c[x]=str[x]-'0';
	c[x]^=1;g[x]=1;
	f[x][1]=0;f[x][2]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&!b[y])
		{
			dfs(y,x);
			g[x]+=g[y]+1;
			c[x]^=1;
			if(c[y]==0)
			{
				g[x]++;
				c[x]^=1;
			}
		}
	}
}
int main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	int n;read(n);scanf("%s",str+1);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	return 0;
}
