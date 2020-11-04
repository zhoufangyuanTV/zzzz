#include<cstdio>
#include<cstring>
using namespace std;
/*
long long jc[2510],fjc[2510];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
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
int to[100010];
int sta[51000],top;
int f[50010][2510];
int ff[2510];
int g[100010];*/
char s[100010];
int p[2510];
int main()
{
	freopen("operator.in","r",stdin);
	freopen("operator.out","w",stdout);
	/*jc[0]=1;
	for(int i=1;i<=2500;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[2500]=ksm(jc[2500],1000000005);
	for(int i=2499;i>=0;i--)jc[i]=jc[i+1]*(i+1)%1000000007;*/
	int n,m;scanf("%d%d%s",&n,&m,s+1);
	long long ss=1;
	for(int i=1;i<=n;i++)if(s[i]>='0'&&s[i]<='9')ss=ss*(s[i]-'0')%1000000007;
	/*top=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='(')sta[++top]=i;
		else if(s[i]==')')
		{
			int x=sta[top--];
			to[x]=i;
			int plen=0;
			for(int j=x+1;j<i;j++)
			{
				if(s[j]=='-'){p[++plen]=j;continue;}
				memset(ff,0,sizeof(ff));
				for(int k=plen;k>=1;k--)
				{
					for(int l=0;l<=g[p[k]-1]&&l+g[j]<=m;l++)
					{
						for(int ll=0;ll<=g[j]&&l+ll<=m;ll++)
						{
							ff[l+ll]=(f[j][l+ll]+(f[p[k]-1][l]*C(g[j],ll)%1000000007+f[j][ll]*C(g[p[k]-1],l)%1000000007)%1000000007)%1000000007;
						}
					}
					for(int l=0;l<=
				}
				if(s[j]=='(')j=to[j];
			}
		}
		else f[i][0]=s[i]-'0',g[i]=0;
	}*/
	printf("%lld",ss);
	return 0;
}
