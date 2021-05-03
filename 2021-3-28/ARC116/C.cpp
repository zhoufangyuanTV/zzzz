#include<cstdio>
#include<cstring>
using namespace std;
long long jc[410000],fjc[410000];
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
int p[210000],s;
bool b[210000];
long long f[210000],low[210000],lo[210000];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	jc[0]=1;
	for(int i=1;i<=400000;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[400000]=ksm(jc[400000],998244351);
	for(int i=399999;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	memset(b,true,sizeof(b));b[1]=false;
	s=0;f[1]=1;low[1]=1;lo[1]=0;
	for(int i=2;i<=m;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			f[i]=C(n,n-1);
			low[i]=i;
			lo[i]=1;
		}
		for(int j=1;j<=s&&i*p[j]<=m;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				f[i*p[j]]=C(lo[i]+n,n-1)*f[i/low[i]]%998244353;
				low[i*p[j]]=low[i]*p[j];
				lo[i*p[j]]=lo[i]+1;
				break;
			}
			else
			{
				f[i*p[j]]=C(n,n-1)*f[i]%998244353;
				low[i*p[j]]=p[j];
				lo[i*p[j]]=1;
			}
		}
	}
	long long ss=0;
	for(int i=1;i<=m;i++)ss=(ss+f[i])%998244353;
	printf("%lld\n",ss);
	return 0;
}