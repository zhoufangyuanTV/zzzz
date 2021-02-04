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
int n,m;
long long jc[5210000],fjc[5210000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
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
long long F[210000],f[210000];
int fa[210000],tot[210000];
void dfs1(int x)
{
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dfs1(y);
			tot[x]+=tot[y];
		}
	}
}
int ys[410000];
void dfs2(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			ys[k]=tot[y];
			dfs2(y);
		}
		else ys[k]=n-tot[x];
	}
}
bool b[210000];
void dfs3(int x,int fa)
{
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			dfs3(y,x);
			tot[x]+=tot[y];
		}
	}
}
int ce,ff,size;
void dfs4(int x,int fa)
{
	int g=size-tot[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa)
		{
			dfs4(y,x);
			if(g<tot[y])g=tot[y];
		}
	}
	if(g<ff)ce=x,ff=g;
}
int p[210000],pp[210000],plen;
void dfs5(int x)
{
	p[++plen]=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			tot[y]=ys[k];
			if(b[y])
			{
				fa[y]=x;
				dfs5(y);
			}
		}
	}
}
long long s,ss=0,sss;
int T=0,t[210000];
void dfs6(int x,int c)
{
	if(T==t[x])return ;
	t[x]=T;
	if(x!=ce)
	{
		long long g=F[tot[x]];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa[x])g-=F[tot[y]];
		}
		g=g%998244353+998244353;
		s=(s+sss*g)%998244353;
		sss=(sss+c*g)%998244353;
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]&&y!=fa[x])dfs6(y,c);
	}
}
int cnt[512];
void div(int x)
{
	dfs3(x,0);
	ff=size=tot[x];
	dfs4(x,0);
	plen=0;
	fa[ce]=0;dfs5(ce);
	if(plen<512)sort(p+1,p+plen+1);
	else
	{
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=plen;i++)cnt[p[i]&511]++;
		for(int i=1;i<512;i++)cnt[i]+=cnt[i-1];
		for(int i=plen;i>=1;i--)pp[cnt[p[i]&511]--]=p[i];
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=plen;i++)cnt[pp[i]>>9&511]++;
		for(int i=1;i<512;i++)cnt[i]+=cnt[i-1];
		for(int i=plen;i>=1;i--)p[cnt[pp[i]>>9&511]--]=pp[i];
	}
	s=sss=0;T++;
	for(int i=1;i<=plen;i++)dfs6(p[i],p[i]);
	ss=(ss+s)%998244353;
	long long g=0;
	for(int k=last[ce];k>0;k=a[k].next)g=g+F[tot[a[k].y]];
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])
		{
			long long gg=(F[n-tot[y]]-(g-F[tot[y]])%998244353+998244353)%998244353;
			plen=1;p[1]=ce;
			dfs5(y);
			if(plen<512)sort(p+1,p+plen+1);
			else
			{
				memset(cnt,0,sizeof(cnt));
				for(int i=1;i<=plen;i++)cnt[p[i]&511]++;
				for(int i=1;i<512;i++)cnt[i]+=cnt[i-1];
				for(int i=plen;i>=1;i--)pp[cnt[p[i]&511]--]=p[i];
				memset(cnt,0,sizeof(cnt));
				for(int i=1;i<=plen;i++)cnt[pp[i]>>9&511]++;
				for(int i=1;i<512;i++)cnt[i]+=cnt[i-1];
				for(int i=plen;i>=1;i--)p[cnt[pp[i]>>9&511]--]=pp[i];
			}
			s=sss=0;T++;
			for(int i=1;i<=plen;i++)
			{
				if(p[i]!=ce)dfs6(p[i],p[i]);
				else
				{
					dfs6(y,p[i]);
					ss=(ss+sss*gg)%998244353;
					break;
				}
			}
			ss=(ss-s+998244353)%998244353;
		}
	}
	b[ce]=false;
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])div(y);
	}
}
int main()
{
	freopen("milkyway.in","r",stdin);
	freopen("milkyway.out","w",stdout);
	scanf("%d%d",&n,&m);
	jc[0]=1;
	for(int i=1;i<=n+m;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n+m]=ksm(jc[n+m],998244351);
	for(int i=n+m-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	if(m&1)
	{
		for(int i=1;i<=n;i++)f[i]=(f[i-1]+C(m/2+i-1,i-1)*C(m/2+n-i,n-i))%998244353;
		fa[1]=0;dfs1(1);
		for(int i=1;i<=n;i++)
		{
			s=f[tot[i]];
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(y!=fa[i])s-=f[tot[y]];
			}
			ss=(ss+i*(s%998244353+998244353))%998244353;
		}
		printf("%lld\n",ss);
	}
	else
	{
		for(int i=1;i<=n;i++)f[i]=(f[i-1]+C(m/2+i-2,i-1)*C(m/2+n-i,n-i))%998244353;
		for(int i=1;i<=n;i++)F[i]=C(m/2+i-1,i-1);
		fa[1]=0;dfs1(1);
		for(int i=1;i<=n;i++)
		{
			s=f[tot[i]];sss=F[tot[i]];
			long long S=0,SSS=0;
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(y!=fa[i])
				{
					s-=f[tot[y]];
					sss-=F[tot[y]];
					S=(S+SSS*F[tot[y]])%998244353;
					SSS=(SSS+F[tot[y]])%998244353;
				}
			}
			ss=(ss+i*((s-sss%998244353*F[n-tot[i]]+S)%998244353+998244353))%998244353;
		}
		dfs2(1);
		memset(b,true,sizeof(b));
		memset(t,0,sizeof(t));
		div(1);
		printf("%lld\n",ss);
	}
	return 0;
}