#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int a[1010000],s;
bool b[1010000],bb[1010000];
int low[1010000],lown[1010000],f[1010000],g[1010000],h[1010000];
int A[1010000],B[1010000];
long long c[1010000],d[1010000];
vector<int> dd[1010000];
int e[1010000],ee[1010000],eee[1010000],E[1010000];
int main()
{
	freopen("library.in","r",stdin);
	freopen("library.out","w",stdout);
	int n,m;read(n);read(m);
	int ma=0;
	for(int i=1;i<=n;i++)
	{
		int x;read(x);
		A[x]++;
		if(ma<x)ma=x;
	}
	for(int i=1;i<=m;i++)
	{
		int x;read(x);
		B[x]++;
		if(ma<x)ma=x;
	}
	memset(b,true,sizeof(b));b[1]=false;
	s=0;low[1]=1;lown[1]=0;f[1]=g[1]=h[1]=1;
	for(int i=2;i<=ma;i++)
	{
		if(b[i])
		{
			a[++s]=i;
			low[i]=i;
			lown[i]=1;
			f[i]=h[i]=i;
			g[i]=1;
		}
		for(int j=1;j<=s&&i*a[j]<=ma;j++)
		{
			b[i*a[j]]=false;
			if(i%a[j]==0)
			{
				low[i*a[j]]=low[i]*a[j];
				lown[i*a[j]]=lown[i]+1;
				if(lown[i]&1)
				{
					f[i*a[j]]=f[i]/low[i];
					g[i*a[j]]=g[i]*low[i]*a[j];
					h[i*a[j]]=h[i]/a[j];
				}
				else
				{
					f[i*a[j]]=f[i]*low[i]*a[j];
					g[i*a[j]]=g[i]/low[i];
					h[i*a[j]]=h[i]*a[j];
				}
				break;
			}
			else
			{
				low[i*a[j]]=a[j];
				lown[i*a[j]]=1;
				f[i*a[j]]=f[i]*a[j];
				g[i*a[j]]=g[i];
				h[i*a[j]]=h[i]*a[j];
			}
		}
	}
	s=0;
	for(int i=1;i<=ma;i++)
	{
		if(f[i]<=ma/h[i])
		{
			s++;
			e[s]=f[i];
			ee[s]=g[i];
			eee[s]=f[i]*h[i];
			b[i]=true;
			E[i]=s;
			c[s]=A[i];
			d[s]=B[i];
			bb[f[i]*h[i]]=true;
		}
		else b[i]=false;
	}
	for(int i=1;i<=ma;i++)
	{
		if(bb[i]==true)
		{
			for(int j=i;j<=ma;j+=i)
			{
				if(b[j]==true)dd[i].push_back(E[j]);
			}
		}
	}
	long long ss=0;
	for(register int i=1;i<=s;i++)
	{
		for(vector<int>::iterator it=dd[eee[i]].begin();it!=dd[eee[i]].end();it++)
		{
			if(ee[i]%e[*it]==0&&ee[*it]%e[i]==0)ss+=c[i]*d[*it];
		}
	}
	printf("%lld\n",ss);
	return 0;
}
