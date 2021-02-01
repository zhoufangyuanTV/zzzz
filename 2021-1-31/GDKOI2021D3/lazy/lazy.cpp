#include<cstdio>
#include<cstring>
using namespace std;
int n;
struct node
{
	int x,y,next;
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int c[510000];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
bool b[510000];
long long ss=1;
int rt;
void dfs(int x,int fa,int lcm)
{
	if(b[x])lcm=lcm/gcd(lcm,c[x])*c[x];
	if(rt<=x)ss=ss*lcm%1000000007;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,lcm);
	}
}
int rts;
void dfs(int x,int fa)
{
	b[x]=true;
	if(rts<=x)for(int i=1;i<=n;i++){rt=i;dfs(i,0,1);}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x);
	}
	b[x]=false;
}
int main()
{
	freopen("lazy.in","r",stdin);
	freopen("lazy.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		rts=i;dfs(i,0);
	}
	printf("%lld\n",ss);
	return 0;
}
