#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[1100];int len,last[1100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long jc[410],fjc[410];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
long long f[401][401][401],g[401][401],hf[401][401],h[401],fg[401];
int tot[410];
void dfs(int x,int fa)
{
	f[x][1][0]=f[x][1][1]=1;tot[x]=1;
	for(int _=last[x];_>0;_=a[_].next)
	{
		int y=a[_].y;
		if(y!=fa)
		{
			dfs(y,x);
			for(int i=1;i<=tot[x];i++)
			{
				for(int j=0;j<=tot[x]-i+1;j++)
				{
					g[i][j]=f[x][i][j];
					f[x][i][j]=0;
				}
			}
			for(int i=0;i<=tot[y];i++)
			{
				h[i]=0;
				for(int j=1;j<=tot[y]-i+1;j++)h[i]+=f[y][j][i];
				h[i]%=998244353;
			}
			for(int i=1;i<=tot[x];i++)
			{
				for(int j=0;j<=tot[y];j++)
				{
					fg[j]=0;long long s=1;
					for(int k=j;k<=tot[y];k++,s=s*i%998244353)fg[j]=(fg[j]+C(k,j)*h[k]%998244353*s)%998244353;
				}
				for(int j=0;j<=tot[x]-i+1;j++)
				{
					for(int k=0;k<=tot[y];k++)
					{
						f[x][i][j+k]=(f[x][i][j+k]+g[i][j]*fg[k])%998244353;
					}
				}
			}
			for(int i=1;i<=tot[x];i++)
			{
				for(int j=1;j<=tot[y];j++)
				{
					for(int k=0;k<=tot[x]-i+1;k++)
					{
						long long ff=0,s=1;
						for(int l=k;l<=tot[x]-i+1;l++,s=s*j%998244353)ff=(ff+C(l,k)*g[i][l]%998244353*s)%998244353;
						f[x][i+j][k]=(f[x][i+j][k]+ff*f[y][j][0])%998244353;
					}
				}
			}
			tot[x]+=tot[y];
		}
	}
}
int main()
{
	freopen("sea.in","r",stdin);
	freopen("sea.out","w",stdout);
	int n;scanf("%d",&n);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(f,0,sizeof(f));
	dfs(1,0);
	long long ss=0;
	for(int i=1;i<=n;i++)ss=(ss+f[1][i][0])%998244353;
	printf("%lld\n",ss);
	return 0;
}