#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
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
}a[2010000];int len,last[2010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long g[2010000];
int dep[2010000];
void dfs(int x,int fa)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dep[y]=dep[x]+1;
			dfs(y,x);
		}
	}
}
int main()
{
	freopen("deconstruct.in","r",stdin);
	freopen("deconstruct.out","w",stdout);
	int n;read(n);
	len=0;memset(last,0,sizeof(last));
	for(int i=2;i<=n;i++)
	{
		int f;read(f);
		ins(f,i);
	}
	g[1]=1;
	for(int i=2;i<=n;i++)g[i]=(1000000007-g[1000000007%i])*(1000000007/i)%1000000007;
	for(int i=2;i<=n;i++)g[i]=(g[i]+g[i-1])%1000000007;
	dep[1]=0;dfs(1,0);
	long long ss=0;
	for(int i=2;i<=n;i++)ss=(ss+g[dep[i]])%1000000007;
	printf("%lld\n",ss);
	return 0;
}