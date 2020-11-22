#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int f[210000],ff[210000];
void dfs(int x,int fa,int dep[210000])
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dep[y]=dep[x]+1;
			dfs(y,x,dep);
		}
	}
}
int nn[210000],cnt[210000],tnc[210000];
int main()
{
	int n;scanf("%d",&n);
	len++;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	f[1]=0;dfs(1,0,f);
	int X=1;
	for(int i=2;i<=n;i++)if(f[i]>f[X])X=i;
	f[X]=0;dfs(X,0,f);
	int Y=1;
	for(int i=2;i<=n;i++)if(f[i]>f[Y])Y=i;
	ff[Y]=0;dfs(Y,0,ff);
	nn[0]=1;
	for(int i=1;i<=n;i++)nn[i]=nn[i-1]*2%1000000007;
	int ss=2ll*nn[n-2]*f[Y]%1000000007,sr=nn[n-2];
	memset(cnt,0,sizeof(cnt));
	memset(tnc,0,sizeof(tnc));
	for(int i=1;i<=n;i++)cnt[max(f[i],ff[i])]++,tnc[min(f[i],ff[i])]++;
	for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
	for(int i=f[Y]-1;i>=0;i--)
	{
		if(tnc[i+1]>0)break;
		sr=nn[cnt[i]];
		ss=(ss-sr+1000000007)%1000000007;
	}
	printf("%d\n",ss*2%1000000007);
	return 0;
}