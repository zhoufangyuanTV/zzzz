#include<cstdio>
#include<cstring>
using namespace std;
struct zysfj{int p[10],c[10],pp,cc;}v[510000];
struct node
{
	int x,y,next;
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool b[5010000];
int T,n;
int tot[510000],l[510000],r[510000];
long long f[510000][23],F[23],FF[23];
long long Ans[23];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x,int fa)
{
	tot[x]=1;
	long long g=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			tot[x]+=tot[y];
			g+=1ll*tot[y]*tot[y];
		}
	}
	g=g+1ll*(n-tot[x])*(n-tot[x]);
	if(v[x].cc<=v[x].pp&&v[x].p[v[x].cc]==T){l[x]=r[x]=v[x].c[v[x].cc];v[x].cc++;}
	else l[x]=r[x]=0;
	f[x][l[x]]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			long long fg=(1ll*(n-tot[y]-1)*(n-tot[y]-1)-(g-1ll*tot[y]*tot[y])+2*(n-tot[y])-1)%1000000006;
			F[l[x]]=f[x][l[x]];
			for(int i=l[x]+1;i<=r[x];i++)F[i]=(F[i-1]+f[x][i])%1000000006;
			FF[l[y]]=f[y][l[y]];
			for(int i=l[y]+1;i<=r[y];i++)FF[i]=(FF[i-1]+f[y][i])%1000000006;
			for(int i=l[y];i<=r[y];i++)
			{
				int I=mymax(i,l[x]);
				Ans[I]=(Ans[I]+fg*f[y][i])%1000000006;
			}
			if(r[x]<r[y])
			{
				for(int i=mymax(l[x],l[y]);i<=r[y];i++)
				{
					int I=mymin(i,r[x]);
					if(I!=i)f[x][i]=0;
					Ans[i]=(Ans[i]+f[y][i]*F[I])%1000000006;
				}
				r[x]=r[y];
			}
			else
			{
				for(int i=mymax(l[x],l[y]);i<=r[x];i++)
				{
					int I=mymin(i,r[y]);
					Ans[i]=(Ans[i]+f[x][i]*FF[I])%1000000006;
				}
			}
			for(int i=l[y];i<=r[y];i++)
			{
				int I=mymax(i,l[x]);
				f[x][I]=(f[x][I]+f[y][i])%1000000006;
			}
		}
	}
	long long G=1ll*(tot[x]-1)*(tot[x]-1)-(g-1ll*(n-tot[x])*(n-tot[x]))+2*tot[x]-1;
	f[x][l[x]]=(f[x][l[x]]+G)%1000000006;
}
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
long long ss=1,w[510000],W[5];
void df_(int x,int fa)
{
	W[0]=1;W[1]=n-tot[x];W[2]=W[3]=W[4]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			for(int i=4;i>=1;i--)
			{
				W[i]=(W[i]+W[i-1]*tot[y])%1000000006;
			}
		}
	}
	ss=ss*ksm(w[x],W[4]*6+W[3]*6+W[2]*4+W[1]*2+W[0])%1000000007;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)df_(y,x);
	}
}
int main()
{
	freopen("lazy.in","r",stdin);
	freopen("lazy.out","w",stdout);
	scanf("%d",&n);
	int WWW=0;memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);w[i]=x;
		for(int j=2;j*j<=x;j++)
		{
			if(x%j==0)
			{
				WWW=mymax(WWW,j);b[j]=true;
				v[i].p[++v[i].pp]=j;v[i].c[v[i].pp]=0;
				while(x%j==0)x/=j,v[i].c[v[i].pp]++;
			}
		}
		if(x>1){WWW=mymax(WWW,x);b[x]=true;v[i].p[++v[i].pp]=x;v[i].c[v[i].pp]=1;}
		v[i].cc=1;
	}
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	T=1;
	dfs(1,0);
	for(int i=2;i<=WWW;i++)
	{
		if(b[i])
		{
			T=i;
			memset(Ans,0,sizeof(Ans));
			dfs(1,0);
			for(int j=0;j<=22;j++)ss=ss*ksm(T,Ans[j]*j%1000000006)%1000000007;
		}
	}
	df_(1,0);
	printf("%lld\n",ss);
	return 0;
}