#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
bool b[1010000];
long long f[1010000],g[1010000],h[1010000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
void dfs(int x,int fa)
{
	b[x]=true;f[x]=g[x]=h[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			f[x]=mymax(f[x],f[y]+a[k].c);
			g[x]=(g[x]+2*g[y]+1)%998244353;
			h[x]=(h[x]+2*h[y]+(2*g[y]+1)*a[k].c+f[y])%998244353;
		}
	}
}
long long ss=0,As=0;
long long F[1010000];
int slen,son[1010000];
void dfs(int x,int fa,long long G,long long H)
{
	f[x]=mymax(f[x],F[x]);
	g[x]=(g[x]+G)%998244353;
	h[x]=(h[x]+H)%998244353;
	long long Fst=F[x],Sec=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(Fst<f[y]+a[k].c){Sec=Fst;Fst=f[y]+a[k].c;}
			else if(Sec<f[y]+a[k].c)Sec=f[y]+a[k].c;
		}
	}
	ss=(ss+2*(Fst+Sec)+h[x]+Fst%998244353*g[x])%998244353;
	if(Fst!=Sec)
	{
		bool bk=true;
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa)
			{
				if(Fst==f[y]+a[k].c)
				{
					ss=(ss+(2*g[y]+1)*((Sec-Fst)%998244353+998244353))%998244353;
					bk=false;break;
				}
			}
		}
		if(bk)ss=(ss+G*((Sec-Fst)%998244353+998244353))%998244353;
	}
	As=(As+2+g[x])%998244353;
	long long ff=F[x];
	slen=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			F[y]=ff+a[k].c;
			ff=mymax(ff,f[y]+a[k].c);
			son[++slen]=k;
		}
	}
	ff=F[x];
	for(int k=slen;k>0;k--)
	{
		int y=a[son[k]].y;
		F[y]=mymax(F[y],ff+a[son[k]].c);
		ff=mymax(ff,f[y]+a[son[k]].c);
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			long long gg=(g[x]-2*g[y]%998244353+998244352)%998244353;
			long long hh=((h[x]-2*h[y]-(2*g[y]+1)*a[k].c-f[y])%998244353+998244353)%998244353;
			dfs(y,x,(2*gg+1)%998244353,(2*hh+2*gg*a[k].c+F[y])%998244353);
		}
	}
}
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
int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		if(b[i]==false)
		{
			dfs(i,0);
			F[i]=0;
			dfs(i,0,0,0);
		}
	}
	printf("%lld\n",ss*ksm(As,998244351)%998244353);
	return 0;
}