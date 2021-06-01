#include<cstdio>
#include<cstring>
using namespace std;
int p[3010000],s;
bool b[10010000];
int mu[10010000];
int ph[2100],phi[2100];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
	freopen("cyclic.in","r",stdin);
	freopen("cyclic.out","w",stdout);
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)ph[i]=gcd(i,k)==1;
	phi[0]=0;
	for(int i=1;i<=k;i++)phi[i]=phi[i-1]+ph[i];
	memset(b,true,sizeof(b));b[1]=false;
	mu[1]=1;s=0;
	for(int i=2;i<=n;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			mu[i]=-1;
		}
		for(int j=1;i*p[j]<=n&&j<=s;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				mu[i*p[j]]=0;
				break;
			}
			else mu[i*p[j]]=-mu[i];
		}
	}
	long long ss=0;
	for(int d=1;d<=n;d++)
	{
		if(gcd(d,k)!=1)continue;
		int M=m/d;
		long long s1=1ll*phi[k]*(M/k)+phi[M%k];
		ss+=s1*mu[d]*(n/d);
	}
	printf("%lld\n",ss);
	return 0;
}
