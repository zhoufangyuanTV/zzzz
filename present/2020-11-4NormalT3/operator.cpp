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
inline long long C(int n,int m){return jc[n]*jc[n-m]%1000000007*jc[m]%1000000007;}
int tol[100010],tor[100010];
int sta[100010],top;
char a[100010];
long long f[15010][2510],g[2510],gg[2510];
int s[15010];
int main()
{
	freopen("operator.in","r",stdin);
	freopen("operator.out","w",stdout);
	jc[0]=1;
	for(int i=1;i<=2500;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[2500]=ksm(jc[2500],1000000005);
	for(int i=2499;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	int n,m;scanf("%d%d%s",&m,&n,a+1);
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
	int nn=n;n=0;
	for(int i=1;i<=nn;i++)
	{
		if(tol[i]+1==tol[i-1])continue;
		if(tor[i+1]+1==tor[i])continue;
		if(tol[i]+2==i)continue;
		if(i+2==tor[i])continue;
		a[++n]=a[i];
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='(')sta[++top]=i;
		else if(a[i]==')')
		{
			tol[i]=sta[top--];
			tor[tol[i]]=i;
			s[i]=0;g[0]=1;
			for(int j=tol[i]+1;j<i;j++)
			{
				if(a[j]=='-')continue;
				if(a[j]=='(')
				{
					for(int k=0;k<=s[i]&&k<=m;k++){gg[k]=g[k];g[k]=0;}
					for(int k=0;k<=s[i]&&k<=m;k++)
					{
						for(int l=0;l<=s[j]&&l+k<=m;l++)
						{
							g[k+l]=(g[k+l]+gg[k]*f[j][l]+C(s[i],k)*f[j][l])%1000000007;
							f[i][k+l]=(f[i][k]*C())
						}
					}
				}
				if(a[j]=='(')j=tor[j];
			}
		}
		else if(a[i]!='-')
		{
			f[i][0]=a[i]-'0';
			s[i]=1;
		}
	}
	return 0;
}