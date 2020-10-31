#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct node
{
	int x,y,next;
}a[2100];int len,last[1100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int f[1100];
void dfs(int x)
{
	if(f[x]!=-1)return ;
	f[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(x<y)
		{
			dfs(y);
			f[x]=(f[x]+f[y])%998244353;
		}
	}
}
int main()
{
	freopen("algebra.in","r",stdin);
	freopen("algebra.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len++;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		memset(f,-1,sizeof(f));
		dfs(i);ss=(ss+f[i])%998244353;
	}
	printf("%d\n",ss);
	return 0;
}