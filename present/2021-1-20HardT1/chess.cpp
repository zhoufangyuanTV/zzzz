#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,m;
long long f[1010000],g[1010000];
int p[1010000],type[1010000];
void intree()
{
	while(m--)puts("0");
	exit(0);
}
namespace case1
{
	int d[1010000];
	void dfs(int x,int fa)
	{
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa)
			{
				d[y]=d[x]+1;
				dfs(y,x);
			}
		}
	}
	void work()
	{
		int rt;
		for(rt=1;rt<=n;rt++)if(type[rt]==0)break;
		d[rt]=1;dfs(rt,0);
		for(int i=1;i<=m;i++)
		{
			int x;scanf("%d",&x);
			if(type[x]==0){printf("%lld\n",f[n]);continue;}
			int dy=n-d[x];
			printf("%lld\n",(f[abs(d[x]-dy)]+f[abs(d[x]-dy-2)])%1000000007);
		}
		exit(0);
	}
}
namespace case2
{
	int d[1010000],c[1010000],cc[11];
	void dfs(int x,int fa,int col)
	{
		c[x]=col;cc[col]=d[x];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa)
			{
				d[y]=d[x]+1;
				dfs(y,x,col);
			}
		}
	}
	void work()
	{
		int rt;
		for(rt=1;rt<=n;rt++)if(type[rt]==2)break;
		int cnt=0;
		for(int k=last[rt];k>0;k=a[k].next)
		{
			int y=a[k].y;d[y]=1;dfs(y,rt,++cnt);
		}
		for(int i=1;i<=m;i++)
		{
			int x;scanf("%d",&x);
			if(type[x]==2){puts("0");continue;}
			if(d[x]<cc[c[x]]-d[x]){puts("0");continue;}
			int l=2*d[x]-cc[c[x]],cca,ccb;
			if(c[x]==1)cca=cc[2],ccb=cc[3];
			if(c[x]==2)cca=cc[1],ccb=cc[3];
			if(c[x]==3)cca=cc[1],ccb=cc[2];
			long long ss=g[l]*(f[abs(cca-ccb+1)]+f[abs(cca-ccb-1)])%1000000007;
			if(cca<=l+1)ss=(ss+g[l-cca+1]*f[ccb])%1000000007;
			if(cca+1<=l)ss=(ss+g[l-cca-1]*f[ccb])%1000000007;
			if(ccb<=l+1)ss=(ss+g[l-ccb+1]*f[cca])%1000000007;
			if(ccb+1<=l)ss=(ss+g[l-ccb-1]*f[cca])%1000000007;
			if(type[x]!=0&&cc[c[x]]-d[x]+1<=d[x]-1)
			{
				l=2*d[x]-cc[c[x]]-2;
				ss=(ss+g[l]*(f[abs(cca-ccb+1)]+f[abs(cca-ccb-1)]))%1000000007;
				if(cca<=l+1)ss=(ss+g[l-cca+1]*f[ccb])%1000000007;
				if(cca+1<=l)ss=(ss+g[l-cca-1]*f[ccb])%1000000007;
				if(ccb<=l+1)ss=(ss+g[l-ccb+1]*f[cca])%1000000007;
				if(ccb+1<=l)ss=(ss+g[l-ccb-1]*f[cca])%1000000007;
			}
			printf("%lld\n",ss);
		}
	}
}
namespace case3
{
	int d[1010000],c[1010000],cc[11];
	void dfs(int x,int fa,int col)
	{
		c[x]=col;cc[col]=d[x];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa)
			{
				d[y]=d[x]+1;
				dfs(y,x,col);
			}
		}
	}
	void work()
	{
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(type[i]==3)
			{
				for(int k=last[i];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(type[y]<2)
					{
						d[y]=1;dfs(y,i,++cnt);
					}
				}
			}
		}
		for(int i=1;i<=m;i++)
		{
			int x;scanf("%d",&x);
			if(type[x]==3){puts("0");continue;}
			if(d[x]<cc[c[x]]-d[x]){puts("0");continue;}
			int l=2*d[x]-cc[c[x]],lcc,cca,ccb;
			if(c[x]==1)lcc=cc[2],cca=cc[3],ccb=cc[4];
			if(c[x]==2)lcc=cc[1],cca=cc[3],ccb=cc[4];
			if(c[x]==3)lcc=cc[4],cca=cc[1],ccb=cc[2];
			if(c[x]==4)lcc=cc[3],cca=cc[1],ccb=cc[2];
			long long ss=0;
			if(lcc<=l+1)ss=(ss+g[l-lcc+1]*(f[abs(cca-ccb+1)]+f[abs(cca-ccb-1)]))%1000000007;
			if(cca<=l)ss=(ss+g[l-cca]*f[abs(lcc-ccb)])%1000000007;
			if(ccb<=l)ss=(ss+g[l-ccb]*f[abs(lcc-cca)])%1000000007;
			if(type[x]!=0&&cc[c[x]]-d[x]+1<=d[x]-1)
			{
				l=2*d[x]-cc[c[x]]-2;
				if(lcc<=l+1)ss=(ss+g[l-lcc+1]*(f[abs(cca-ccb+1)]+f[abs(cca-ccb-1)]))%1000000007;
				if(cca<=l)ss=(ss+g[l-cca]*f[abs(lcc-ccb)])%1000000007;
				if(ccb<=l)ss=(ss+g[l-ccb]*f[abs(lcc-cca)])%1000000007;
			}
			printf("%lld\n",ss);
		}
	}
}
namespace case4
{
	int d[1010000],c[1010000],cc[11];
	void dfs(int x,int fa,int col)
	{
		c[x]=col;cc[col]=d[x];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa)
			{
				d[y]=d[x]+1;
				dfs(y,x,col);
			}
		}
	}
	void work()
	{
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(type[i]==3)
			{
				for(int k=last[i];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(type[y]<2)
					{
						d[y]=1;dfs(y,i,++cnt);
					}
				}
			}
			if(type[i]==4)
			{
				for(int k=last[i];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(type[y]==0)c[y]=-1;
				}
			}
		}
		for(int i=1;i<=m;i++)
		{
			int x;scanf("%d",&x);
			if(type[x]>1||c[x]==-1){puts("0");continue;}
			if(d[x]<cc[c[x]]-d[x]){puts("0");continue;}
			int l=2*d[x]-cc[c[x]],lcc,cca,ccb;
			if(c[x]==1)lcc=cc[2],cca=cc[3],ccb=cc[4];
			if(c[x]==2)lcc=cc[1],cca=cc[3],ccb=cc[4];
			if(c[x]==3)lcc=cc[4],cca=cc[1],ccb=cc[2];
			if(c[x]==4)lcc=cc[3],cca=cc[1],ccb=cc[2];
			if(l+1<lcc){puts("0");continue;}
			long long ss=g[l-lcc+1]*(f[abs(cca-ccb+1)]+f[abs(cca-ccb-1)])%1000000007;
			if(type[x]!=0&&cc[c[x]]-d[x]+1<=d[x]-1)
			{
				l=2*d[x]-cc[c[x]]-2;
				ss=(ss+g[l-lcc+1]*(f[abs(cca-ccb+1)]+f[abs(cca-ccb-1)]))%1000000007;
			}
			printf("%lld\n",ss);
		}
	}
}
/*int fr[1010000];
bool swich[1010000];
void ffr(int x,int fa,int fl)
{
	if(type[x]==4)swich[fl]=true;
	if(type[x]==3)
	{
		fr[fl]=x;fr[x]=fl;
		swich[x]=swich[fl];
		return ;
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&type[y]>2)ffr(y,x,fl);
	}
}*/
bool fpt(int x,int fa)
{
	if(type[x]>1)return true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&fpt(y,x))return true;
	}
	return false;
}
int ffr(int x,int fa)
{
	if(type[x]==3)return x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&type[y]>1)return ffr(y,x);
	}
}
int pt[1010000];
int main()
{
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	scanf("%d%d",&n,&m);
	f[0]=f[1]=1;g[0]=g[1]=1;
	for(int i=2;i<=n;i++)
	{
		f[i]=(f[i-1]+f[i-2])%1000000007;
		if(i>2&&i%2==0)f[i]=(f[i]+1)%1000000007;
		g[i]=(g[i-1]+g[i-2])%1000000007;
	}
	len=0;memset(last,0,sizeof(last));
	memset(p,0,sizeof(p));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
		p[x]++;p[y]++;
	}
	int bk1=0,bk2=0,bk3=0;
	for(int i=1;i<=n;i++)
	{
		if(p[i]>3)intree();
		if(p[i]==1)type[i]=0;
		if(p[i]==2)type[i]=1;
		if(p[i]==3)
		{
			bk1++;
			int cnt=0,gt=0;
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(p[y]==3)cnt++;
				if(p[y]==1)gt++;
			}
			if(cnt==0)type[i]=2;
			if(cnt==1)type[i]=3,bk2++;
			if(cnt==2)
			{
				if(gt==0)intree();
				type[i]=4;
				bk3++;
			}
			if(cnt==3)intree();
		}
	}
	if(bk1==0)case1::work();
	if(bk1==1)case2::work();
	if(bk1==2&&bk2==2)case3::work();
	if(bk1==bk2+bk3&&bk2==2)case4::work();
	for(int i=1;i<=n;i++)
	{
		if(type[i]>1)
		{
			pt[i]=0;
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(type[y]<2)pt[i]+=fpt(y,i);
			}
			if(pt[i]==3)intree();
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(type[i]==3)
		{
			bool swich=false;
			int ddd=0;
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(type[y]==3){ddd=y;break;}
				if(type[y]==4){swich=true;ddd=ffr(y,i);break;}
			}
			if(swich)
			{
				if(pt[i]==2||pt[ddd]==2)intree();
			}
		}
	}
	return 0;
}