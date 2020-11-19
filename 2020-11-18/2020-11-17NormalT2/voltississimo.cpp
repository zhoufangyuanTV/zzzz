#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
	bool c;
}a[11000];int len,last[5100];
inline void ins(int x,int y,bool c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long f[5100][5100][4];
int tot[5100];
void dfs(int x,int fa)
{
	tot[x]=1;
	f[x][0][0]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			for(int i=tot[y];i>=0;i--)
			{
				f[y][i][0]=(f[y][i][0]+f[y][i][1]+f[y][i][2]+f[y][i][3])%998244353;
				if(i>0)f[y][i][1]=(f[y][i-1][0]+f[y][i-1][1])%998244353;
				if(i>0)f[y][i][2]=(f[y][i-1][0]+f[y][i-1][2])%998244353;
				if(a[k].c)f[y][i][2]=0;
				else f[y][i][1]=0;
			}
			for(int i=tot[x]-1;i>=0;i--)
			{
				for(int j=tot[y];j>=0;j--)
				{
					long long t=f[x][i][0],u=f[x][i][1],v=f[x][i][2],w=f[x][i][3];
					if(j==0)f[x][i][0]=f[x][i][1]=f[x][i][2]=f[x][i][3]=0;
					f[x][i+j][0]=(f[x][i+j][0]+t*f[y][j][0])%998244353;
					f[x][i+j][1]=(f[x][i+j][1]+t*f[y][j][1]+u*f[y][j][0])%998244353;
					f[x][i+j][2]=(f[x][i+j][2]+t*f[y][j][2]+v*f[y][j][0])%998244353;
					f[x][i+j][3]=(f[x][i+j][3]+u*f[y][j][2]+v*f[y][j][1]+w*f[y][j][0])%998244353;
				}
			}
			tot[x]+=tot[y];
		}
	}
}
long long jc[5100];
int main()
{
	freopen("voltississimo.in","r",stdin);
	freopen("voltississimo.out","w",stdout);
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y,true);ins(y,x,false);
	}
	memset(f,0,sizeof(f));
	dfs(1,0);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	long long Ans=0;
	for(int i=0;i<=n;i++)Ans=(Ans+(i&1?-1:1)*jc[n-i]*(f[1][i][0]+f[1][i][1]+f[1][i][2]+f[1][i][3])%998244353+998244353)%998244353;
	printf("%lld\n",Ans);
	return 0;
}