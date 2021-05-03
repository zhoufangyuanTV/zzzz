#include<cstdio>
#include<cstring>
using namespace std;
char s[510000];
long long a[510];
long long fa[510],fb[510],fc[510];
long long two[510],jc[510],fjc[510],C[510][510];
long long ksm(long long x,long long k)
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
int main()
{
	freopen("angry.in","r",stdin);
	freopen("angry.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	int m;scanf("%d",&m);
	for(int i=0;i<m;i++)scanf("%lld",&a[i]);
	two[0]=1;
	for(int i=1;i<=m;i++)two[i]=two[i-1]*2%1000000007;
	jc[0]=1;
	for(int i=1;i<=m;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[m]=ksm(jc[m],1000000005);
	for(int i=m-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	for(int i=0;i<=m;i++)
	{
		for(int j=0;j<=i;j++)C[i][j]=jc[i]*fjc[i-j]%1000000007*fjc[j]%1000000007;
	}
	int t=0;fc[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
		{
			fa[j]=fa[j]*two[j]%1000000007;
			fb[j]=fb[j]*two[j]%1000000007;
			fc[j]=fc[j]*two[j]%1000000007;
		}
		for(int j=m-1;j>=0;j--)
		{
			long long ga=fa[j],gb=fb[j];
			for(int k=0;k<=j;k++)ga=(ga+C[j][k]*fb[k])%1000000007;
			for(int k=0;k<=j;k++)gb=(gb+C[j][k]*fa[k])%1000000007;
			fa[j]=ga;fb[j]=gb;
		}
		if(s[i]=='1')
		{
			if(t==1)
			{
				for(int j=0;j<m;j++)fa[j]=(fa[j]+fc[j])%1000000007;
			}
			else
			{
				for(int j=0;j<m;j++)fb[j]=(fb[j]+fc[j])%1000000007;
			}
			t^=1;
			for(int j=m-1;j>=0;j--)
			{
				for(int k=0;k<j;k++)fc[j]=(fc[j]+C[j][k]*fc[k])%1000000007;
			}
		}
	}
	long long ss=0;
	for(int i=0;i<m;i++)ss=(ss+a[i]*fa[i])%1000000007;
	printf("%lld\n",ss);
	return 0;
}