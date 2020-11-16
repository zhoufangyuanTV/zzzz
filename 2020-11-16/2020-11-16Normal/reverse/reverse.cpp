#include<cstdio>
#include<cstring>
using namespace std;
int f[21][1048576];
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
char a[110];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int type,n,m;scanf("%d%d%d",&type,&n,&m);
	if(type==1)scanf("%s",a+1);
	else
	{
		/*n=2*n+1;
		for(int i=1;i<=n;i++)a[i]=i%2+'0';*/
		long long jc=1,fjc=1,F=1;
		for(int i=n-m+2;i<=n+m+1;i++)jc=jc*i%998244353;
		for(int i=1;i<=m*2;i++)fjc=fjc*i%998244353;
		fjc=ksm(fjc,998244351);
		for(int i=1;i<=m;i++)F=F*(2*i-1)%998244353;
		printf("%lld\n",jc*fjc%998244353*F%998244353);
		return 0;
	}
	memset(f,0,sizeof(f));
	int g=0;
	for(int i=1;i<=n;i++)g|=a[i]-'0'<<i-1;
	f[0][g]=1;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<1<<n;j++)
		{
			if(f[i][j]==0)continue;
			for(int k=1;k<=n;k++)a[k]=j>>k-1&1;
			for(int l=1;l<=n;l++)
			{
				if(a[l]==1)
				{
					g=1<<l-1;
					f[i+1][j^g]=(f[i+1][j^g]+f[i][j])%998244353;
					for(int r=l+2;r<=n;r+=2)
					{
						if(a[r-1]!=0||a[r]!=1)break;
						g|=1<<r-2|1<<r-1;
						f[i+1][j^g]=(f[i+1][j^g]+f[i][j])%998244353;
					}
				}
			}
		}
	}
	int ss=0;
	for(int i=0;i<1<<n;i++)ss=(ss+f[m][i])%998244353;
	printf("%d\n",ss);
	return 0;
}