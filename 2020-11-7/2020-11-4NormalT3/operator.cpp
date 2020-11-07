#include<cstdio>
#include<cstring>
using namespace std;
long long jc[2510],fjc[2510];
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
inline long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
int tol[100010],tor[100010];
int sta[100010],top;
char a[100010];
long long f[15010][2510],ff[2510],g[2510],gg[2510];
int s[15010];
int main()
{
	freopen("operator.in","r",stdin);
	freopen("operator.out","w",stdout);
	jc[0]=1;
	for(int i=1;i<=2500;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[2500]=ksm(jc[2500],1000000005);
	for(int i=2499;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	int n,m;scanf("%d%d%s",&n,&m,a+1);
	memset(tol,-64,sizeof(tol));
	memset(tor,-64,sizeof(tor));
	top=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='(')sta[++top]=i;
		else if(a[i]==')')
		{
			tol[i]=sta[top--];
			tor[tol[i]]=i;
		}
	}
	int nn=n;n=0;a[0]='(';
	for(int i=1;i<=nn;i++)
	{
		if(tol[i]+1==tol[i-1])continue;
		if(tor[i+1]+1==tor[i])continue;
		if(tol[i]+2==i)continue;
		if(i+2==tor[i])continue;
		a[++n]=a[i];
	}
	a[++n]=')';
	memset(f,0,sizeof(f));
	for(int i=0;i<=n;i++)
	{
		if(a[i]=='(')sta[++top]=i;
		else if(a[i]==')')
		{
			tol[i]=sta[top--];
			tor[tol[i]]=i;
			memset(g,0,sizeof(g));
			s[i]=0;g[0]=1;
			for(int j=tol[i]+1;j<i;j++)
			{
				if(a[j]=='-')
				{
					s[i]++;
					for(int k=s[i];k>=1;k--)
					{
						f[i][k]=(f[i][k]+f[i][k-1]+g[k-1])%1000000007;
						g[k]=(g[k]+C(s[i]-1,k-1))%1000000007;
					}
					continue;
				}
				if(a[j]=='(')j=tor[j];
				for(int k=0;k<=s[i];k++)
				{
					ff[k]=f[i][k];gg[k]=g[k];
					f[i][k]=g[k]=0;
				}
				for(int k=s[i];k>=0;k--)
				{
					for(int l=s[j];l>=0;l--)
					{
						f[i][k+l]=(f[i][k+l]+ff[k]*C(s[j],l))%1000000007;
						g[k+l]=(g[k+l]+gg[k]*f[j][l])%1000000007;
					}
				}
				s[i]+=s[j];
			}
			for(int k=0;k<=s[i];k++)f[i][k]=(f[i][k]+g[k])%1000000007;
		}
		else if(a[i]!='-')
		{
			f[i][0]=a[i]-'0';
			s[i]=0;
		}
	}
	printf("%lld\n",f[n][m]);
	return 0;
}
