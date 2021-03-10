#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
bool b[51000];
int p[11000],s;
int low[51000],phi[51000],mu[51000],d[51000];
vector<int> e[51000];
long long f[51000],A[51000],B[51000],C[51000];
inline long long ksm(long long x,long long k)
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
struct node
{
	int x,y,c,next,other;
	long long Beta,Gamma;
}a[1010000];int len,last[51000];
int du[51000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;
	a[len].x=y;a[len].y=x;a[len].c=c;
	a[len].next=last[y];last[y]=len;
	a[len-1].other=len;
	a[len].other=len-1;
	du[x]++;du[y]++;
}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int T[51000];
long long Alpha[51000],Lambda[51000];
struct edge
{
	int y,c;
	long long Beta,Gamma,OB,OG;
}D[51000];
vector<edge> E[51000];
int main()
{
	freopen("eeswes.in","r",stdin);
	freopen("eeswes.out","w",stdout);
	int n;scanf("%d",&n);
	memset(b,true,sizeof(b));s=0;
	b[1]=false;low[1]=phi[1]=mu[1]=d[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			low[i]=i;
			phi[i]=i-1;
			mu[i]=-1;
			d[i]=2;
		}
		for(int j=1;j<=s&&i*p[j]<=n;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				low[i*p[j]]=low[i]*p[j];
				phi[i*p[j]]=phi[i]*p[j];
				mu[i*p[j]]=0;
				d[i*p[j]]=d[i/low[i]]*(d[low[i]]+1);
				break;
			}
			else
			{
				low[i*p[j]]=p[j];
				phi[i*p[j]]=phi[i]*(p[j]-1);
				mu[i*p[j]]=-mu[i];
				d[i*p[j]]=d[i]*2;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(mu[i]!=0)for(int j=i;j<=n;j+=i)e[j].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		if(mu[i]!=0)
		{
			for(int j=i;j<=n;j+=i)
			{
				if(mu[j]!=0)
				{
					f[j]+=i*ksm(phi[i],998244351)%998244353*mu[j/i];
				}
			}
			f[i]=(f[i]%998244353+998244353)%998244353;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j+=i)A[i]+=phi[j]*mu[j];
		A[i]=(A[i]%998244353+998244353)%998244353;
	}
	len=0;memset(last,0,sizeof(last));
	memset(du,0,sizeof(du));
	for(int i=1;i<=n;i++)
	{
		if(mu[i]!=0)
		{
			for(int x:e[i])
			{
				for(int y:e[i])
				{
					if(x==y)break;
					if(x/gcd(x,y)*y==i)ins(x,y,i);
				}
			}
		}
	}
	memset(T,0,sizeof(T));
	for(int i=1;i<=n;i++)
	{
		if(mu[i]!=0)
		{
			for(int j=i;j<=n;j+=i)
			{
				for(int k:e[j])
				{
					if(i!=T[k])T[k]=i,Alpha[k]=Lambda[k]=0;
					Alpha[k]+=phi[j]*d[j/k];Lambda[k]+=mu[j]*d[j/k];
				}
			}
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				a[k].Beta=Alpha[y]%998244353;
				a[k].Gamma=(Lambda[y]%998244353+998244353)%998244353;
			}
			B[i]=Alpha[i]%998244353;
			C[i]=(Lambda[i]%998244353+998244353)%998244353;
		}
	}
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		if(mu[i]!=0)
		{
			ss+=f[i]*A[i]%998244353*B[i]%998244353*C[i]%998244353;
			for(int k=last[i];k>0;k=a[k].next)
			{
				int y=a[k].y;
				ss+=f[i]*mu[i]*mu[y]*A[i]%998244353*a[k].Beta%998244353*a[k].Gamma%998244353;
				ss+=f[i]*mu[y]*mu[i]*A[a[k].c]%998244353*B[i]%998244353*a[a[k].other].Gamma%998244353;
				ss+=f[y]*mu[i]*mu[i]*A[a[k].c]%998244353*a[a[k].other].Beta%998244353*C[i]%998244353;
			}
			ss=(ss%998244353+998244353)%998244353;
		}
	}
	memset(last,0,sizeof(last));
	for(int i=1;i<=len;i++)
	{
		int x=a[i].x,y=a[i].y;
		if(du[y]<du[x]||du[y]==du[x]&&y<=x)E[x].push_back((edge){y,a[i].c,a[i].Beta,a[i].Gamma,a[a[i].other].Beta,a[a[i].other].Gamma});
	}
	memset(T,0,sizeof(T));
	for(int i=1;i<=n;i++)
	{
		if(mu[i]!=0)
		{
			for(edge k:E[i])T[k.y]=i,D[k.y]=k;
			for(edge k:E[i])
			{
				int y=k.y;
				for(edge kk:E[y])
				{
					int x=kk.y;
					if(i==T[x])
					{
						edge kkk=D[x];
						ss+=f[i]*mu[y]*mu[x]*A[k.c]%998244353*kkk.Beta%998244353*kk.Gamma%998244353;
						ss+=f[i]*mu[x]*mu[y]*A[kkk.c]%998244353*k.Beta%998244353*kk.OG%998244353;
						ss+=f[y]*mu[i]*mu[x]*A[k.c]%998244353*kk.Beta%998244353*kkk.Gamma%998244353;
						ss+=f[y]*mu[x]*mu[i]*A[kk.c]%998244353*k.OB%998244353*kkk.OG%998244353;
						ss+=f[x]*mu[i]*mu[y]*A[kkk.c]%998244353*kk.OB%998244353*k.Gamma%998244353;
						ss+=f[x]*mu[y]*mu[i]*A[kk.c]%998244353*kkk.OB%998244353*k.OG%998244353;
					}
				}
			}
			ss=(ss%998244353+998244353)%998244353;
		}
	}
	printf("%lld\n",ss);
	return 0;
}