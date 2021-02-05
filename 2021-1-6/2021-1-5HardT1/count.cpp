#include<cstdio>
#include<cstring>
using namespace std;
int x[11000],y[11000],w[11000];
long long M[110][110],MM[110][110];
inline long long ksm(long long x,long long k)
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
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&x[i],&y[i],&w[i]);
	long long Ans=0;
	for(int i=1;i<256;i<<=1)
	{
		memset(M,0,sizeof(M));
		memset(MM,0,sizeof(MM));
		for(int j=1;j<=m;j++)
		{
			M[x[j]][y[j]]--;M[y[j]][x[j]]--;M[x[j]][x[j]]++;M[y[j]][y[j]]++;
			if(i&w[j])MM[x[j]][y[j]]++,MM[y[j]][x[j]]++,MM[x[j]][x[j]]--,MM[y[j]][y[j]]--;
			else MM[x[j]][y[j]]--,MM[y[j]][x[j]]--,MM[x[j]][x[j]]++,MM[y[j]][y[j]]++;
		}
		for(int j=1;j<n;j++)
		{
			for(int k=1;k<n;k++)
			{
				M[j][k]=(M[j][k]+998244353)%998244353;
				MM[j][k]=(MM[j][k]+998244353)%998244353;
			}
		}
		for(int j=1;j<n;j++)
		{
			if(M[j][j]==0)
			{
				for(int k=j+1;k<n;k++)
				{
					if(M[k][j]!=0)
					{
						for(int l=1;l<n;l++)M[j][l]=(M[j][l]+M[k][l])%998244353;
						break;
					}
				}
			}
			long long fj=998244353-ksm(M[j][j],998244351);
			for(int k=1;k<n;k++)
			{
				if(j==k)continue;
				long long fk=M[k][j]*fj%998244353;
				for(int l=1;l<n;l++)M[k][l]=(M[k][l]+M[j][l]*fk)%998244353;
			}
		}
		for(int j=1;j<n;j++)
		{
			if(MM[j][j]==0)
			{
				for(int k=j+1;k<n;k++)
				{
					if(MM[k][j]!=0)
					{
						for(int l=1;l<n;l++)MM[j][l]=(MM[j][l]+MM[k][l])%998244353;
						break;
					}
				}
			}
			long long fj=998244353-ksm(MM[j][j],998244351);
			for(int k=1;k<n;k++)
			{
				if(j==k)continue;
				long long fk=MM[k][j]*fj%998244353;
				for(int l=1;l<n;l++)MM[k][l]=(MM[k][l]+MM[j][l]*fk)%998244353;
			}
		}
		long long s=1,ss=1;
		for(int j=1;j<n;j++)s=s*M[j][j]%998244353,ss=ss*MM[j][j]%998244353;
		Ans=(Ans+499122177*(s-ss+998244353)%998244353*i%998244353)%998244353;
	}
	printf("%lld\n",Ans);
	return 0;
}