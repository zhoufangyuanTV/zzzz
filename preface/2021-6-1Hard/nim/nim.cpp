#include<cstdio>
#include<cstring>
using namespace std;
char a[5010000];
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
long long jc[3100],fjc[3100];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
long long f[3100],g[3100][3100],h[3100];
int main()
{
	freopen("nim.in","r",stdin);
	freopen("nim.out","w",stdout);
	int n;scanf("%d%s",&n,a+1);
	int L=strlen(a+1);
	long long s=1,fs=1,m=0;
	memset(f,0,sizeof(f));f[0]=1;
	int p;
	for(p=1;p<=L;p++)if(a[p]=='1')break;
	for(int i=L;i>=1;i--,s=s*2%1000000007,fs=fs*500000004%1000000007)
	{
		if(a[i]=='1')
		{
			long long s1=1,s2=1,s3=1;
			for(int j=1;j<=n;j++)
			{
				s1=s1*(s+m)%1000000007;
				s2=s2*(s-m+1000000007)%1000000007;
				s3=s3*m%1000000007;
				if(j&1)
				{
					if(i<=p)f[j]=(f[j]+(s1+s2)*500000004%1000000007*fs)%1000000007;
				}
				else f[j]=(f[j]+((s1+s2)*500000004-s3+1000000007)%1000000007*fs)%1000000007;
			}
			m=(m+s)%1000000007;
		}
	}
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[n]=ksm(jc[n],1000000005);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	memset(g,0,sizeof(g));g[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		long long s1=0,s2=0;
		for(int j=i;j<=n;j++)
		{
			if(j&1)
			{
				s1=(s1+g[i-1][j-1]*fjc[j-1])%1000000007;
				g[i][j]=(g[i][j]+s1*jc[j-1])%1000000007;
			}
			else
			{
				s2=(s2+g[i-1][j-1]*fjc[j-1])%1000000007;
				g[i][j]=(g[i][j]+s2*jc[j-1])%1000000007;
			}
		}
	}
	memset(h,0,sizeof(h));h[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++)
		{
			if((i-j-1)&1)h[i]=(h[i]-h[j]*jc[i-1]%1000000007*fjc[j]%1000000007*m%1000000007+1000000007)%1000000007;
		}
	}
	long long ss=0;
	for(int i=0;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			ss=(ss+f[i]*C(n,j)%1000000007*g[i][j]%1000000007*h[n-j])%1000000007;
		}
	}
	printf("%lld\n",ss*fjc[n]%1000000007);
	return 0;
}