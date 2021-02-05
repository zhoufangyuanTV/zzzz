#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
int n,m,w[110],c[510000],d[510000];
int a[110],aa[110];
long long ss;
void dfs(int k)
{
	if(k==m+1)
	{
		for(int i=1;i<=m;i++)aa[i]=a[i];
		bool bk=true;
		int i=1,sr=m;
		long long s=0;
		while(bk)
		{
			s++;
			if(aa[c[i]]==a[c[i]])sr--;
			aa[c[i]]+=d[i];
			if(aa[c[i]]<1||aa[c[i]]>w[c[i]])break;
			if(aa[c[i]]==a[c[i]])sr++;
			i++;
			if(i>n)
			{
				if(sr==m)
				{
					puts("-1");
					exit(0);
				}
				i=1;
			}
		}
		ss+=s;
	}
	else
	{
		for(int i=1;i<=w[k];i++)
		{
			a[k]=i;
			dfs(k+1);
		}
	}
}
long long l[1010000],r[1010000];
long long f[1010000];
int main()
{
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=m;i++)read(w[i]);
	for(int i=1;i<=n;i++){read(c[i]);read(d[i]);}
	if(m==1)
	{
		int s=0;l[0]=r[0]=0;
		memset(l,-1,sizeof(l));
		memset(r,-1,sizeof(r));
		for(int i=1;i<=n;i++)
		{
			s=s+d[i];
			if(s>0&&r[s]==-1)r[s]=i;
			else if(l[-s]==-1)l[-s]=i;
		}
		int sg=n;
		n=w[1];
		if(s==0)
		{
			long long ss=0;
			for(int i=1;i<=n;i++)
			{
				if(l[i]==-1&&r[n-i+1]==-1)
				{
					puts("-1");
					return 0;
				}
				if(l[i]==-1)ss+=r[n-i+1];
				else if(r[n-i+1]==-1)ss+=l[i];
				else if(l[i]<r[n-i+1])ss+=l[i];
				else ss+=r[n-i+1];
				ss=ss%1000000007;
			}
			printf("%lld\n",ss);
		}
		else if(s>0)
		{
			for(int i=n;i>=1;i--)
			{
				if(l[i]==-1&&r[n-i+1]==-1)
				{
					f[i]=(f[i+s]+sg)%1000000007;
				}
				else
				{
					if(l[i]==-1)f[i]=r[n-i+1];
					else if(r[n-i+1]==-1)f[i]=l[i];
					else if(l[i]<r[n-i+1])f[i]=l[i];
					else f[i]=r[n-i+1];
				}
				ss=(ss+f[i])%1000000007;
			}
			printf("%lld\n",ss);
		}
		else
		{
			for(int i=1;i<=n;i++)
			{
				if(l[i]==-1&&r[n-i+1]==-1)
				{
					f[i]=(f[i+s]+sg)%1000000007;
				}
				else
				{
					if(l[i]==-1)f[i]=r[n-i+1];
					else if(r[n-i+1]==-1)f[i]=l[i];
					else if(l[i]<r[n-i+1])f[i]=l[i];
					else f[i]=r[n-i+1];
				}
				ss=(ss+f[i])%1000000007;
			}
			printf("%lld\n",ss);
		}
		return 0;
	}
	ss=0;
	dfs(1);
	printf("%lld\n",ss);
	return 0;
}
