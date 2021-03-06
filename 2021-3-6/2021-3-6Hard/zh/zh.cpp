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
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int d[1010000],dd[1010000],ddd[1010000];
void dfs(int x,int fa,int dep)
{
	d[dep]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,dep+1);
	}
}
int main()
{
	freopen("zh.in","r",stdin);
	freopen("zh.out","w",stdout);
	int n;read(n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int i=1;i<=n;i++)dd[i]=ddd[i]=0;
		for(int k=last[i];k>0;k=a[k].next)
		{
			int y=a[k].y;
			for(int i=1;i<=n;i++)d[i]=0;
			dfs(y,i,1);
			for(int i=1;i<=n;i++)
			{
				ss+=ddd[i]*d[i];
				ddd[i]+=dd[i]*d[i];
				dd[i]+=d[i];
			}
		}
	}
	printf("%lld\n",ss);
	return 0;
}