#include<cstdio>
#include<cstring>
using namespace std;
int p[1010000],s;
bool b[10010000];
int phi[10010000];
void Euler(int n)
{
	memset(b,true,sizeof(b));
	b[1]=false;phi[1]=1;s=0;
	for(int i=2;i<=n;i++)
	{
		if(b[i])p[++s]=i,phi[i]=i-1;
		for(int j=1;j<=s&&i*p[j]<=n;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}
bool bk;
long long ksm(long long x,long long k,long long p)
{
	long long s=1;
	if(p<=s)bk=true;
	s=s%p;
	while(k>0)
	{
		if(k&1)
		{
			s=s*x;
			if(p<=s)bk=true;
			s=s%p;
		}
		x=x*x%p;
		k>>=1;
	}
	return s;
}
int n;
long long dfs(int k,int p)
{
	if(k==n+1)return 1%p;
	int ak;scanf("%d",&ak);
	long long ss=dfs(k+1,phi[p]);
	if(bk)
	{
		if(ak==1||ak==0)bk=false;
		return ksm(ak,ss,p)*ksm(ak,phi[p],p)%p;
	}
	else return ksm(ak,ss,p);
}
int main()
{
	Euler(10000000);
	int t;scanf("%d",&t);
	while(t--)
	{
		bk=false;
		int p;scanf("%d%d",&n,&p);
		printf("%lld\n",dfs(1,p));
	}
	return 0;
}