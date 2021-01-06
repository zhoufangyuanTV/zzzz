#include<cstdio>
#include<cstring>
using namespace std;
int x[11000],y[11000],w[11000];
int p[110];
long long M[110][110];
int f[110];
int findfa(int x){return f[x]==x?x:f[x]=findfa(f[x]);}
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
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	bool bk=true;
	memset(p,0,sizeof(p));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x[i],&y[i],&w[i]);
		p[x[i]]++;p[y[i]]++;
		if(w[i]!=1)bk=false;
	}
	if(m<n-1)
	{
		printf("0\n");
		return 0;
	}
	if(m<=21)
	{
		int ss=0;
		for(int i=0;i<1<<m;i++)
		{
			int cnt=0;
			for(int j=1;j<=m;j++)
			{
				if(i==(i|1<<j-1))cnt++;
			}
			if(cnt==n-1)
			{
				int v=0;bk=true;
				for(int j=1;j<=n;j++)f[j]=j;
				for(int j=1;j<=m;j++)
				{
					if(i==(i|1<<j-1))
					{
						v^=w[j];
						int fx=findfa(x[j]),fy=findfa(y[j]);
						if(fx==fy){bk=false;break;}
						else f[fx]=fy;
					}
				}
				if(bk)ss=(ss+v)%998244353;
			}
		}
		printf("%d\n",ss);
		return 0;
	}
	if(bk)
	{
		if(n%2==1)
		{
			printf("0\n");
			return 0;
		}
		for(int i=1;i<=n;i++)if(p[i]==0){printf("0\n");return 0;}
		memset(M,0,sizeof(M));
		for(int i=1;i<=m;i++)M[x[i]][y[i]]++,M[y[i]][x[i]]++;
		for(int i=1;i<=n;i++)M[i][i]=998244353-p[i];
		for(int i=1;i<=n;i++)
		{
			int fi=998244353-ksm(M[i][i],998244351);
			for(int j=1;j<=n;j++)
			{
				if(i==j)continue;
				long long l=fi*M[j][i]%998244353;
				for(int k=1;k<=n;k++)M[j][k]=(M[j][k]+M[i][k]*l)%998244353;
			}
		}
		long long ss=1;
		for(int i=1;i<=n;i++)ss=ss*M[i][i]%998244353;
		printf("%lld\n",ss);
		return 0;
	}
	return 0;
}