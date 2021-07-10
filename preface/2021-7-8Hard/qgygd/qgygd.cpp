#include<cstdio>
#include<cstring>
using namespace std;
long long f[110][2][2][2];
long long S(long long x,long long y,long long z)
{
	for(int i=0;i<=1;i++)
	{
		for(int j=0;j<=1;j++)
		{
			for(int k=0;k<=1;k++)
			{
				int s=0;
				if(i==1||(x&1)==1)s++;
				if(j==1||(y&1)==1)s++;
				if(k==1||(z&1)==1)s++;
				if(s<2)f[0][i][j][k]=1;
				else if(s==2)f[0][i][j][k]=2;
				else f[0][i][j][k]=4;
			}
		}
	}
	for(int t=1;t<=60;t++)
	{
		for(int i=0;i<=1;i++)
		{
			for(int j=0;j<=1;j++)
			{
				for(int k=0;k<=1;k++)
				{
					f[t][i][j][k]=0;
					int ii=i,jj=j,kk=k;
					if(i==0&&(x>>t&1)==1)ii=1;
					if(j==0&&(y>>t&1)==1)jj=1;
					if(k==0&&(z>>t&1)==1)kk=1;
					f[t][i][j][k]=(f[t][i][j][k]+f[t-1][ii][jj][kk])%998244353;
					if((i==1||(x>>t&1)==1)&&(j==1||(y>>t&1)==1))
					{
						int kk=k;
						if(k==0&&(z>>t&1)==1)kk=1;
						f[t][i][j][k]=(f[t][i][j][k]+f[t-1][i][j][kk])%998244353;
					}
					if((i==1||(x>>t&1)==1)&&(k==1||(z>>t&1)==1))
					{
						int jj=j;
						if(j==0&&(y>>t&1)==1)jj=1;
						f[t][i][j][k]=(f[t][i][j][k]+f[t-1][i][jj][k])%998244353;
					}
					if((k==1||(z>>t&1)==1)&&(j==1||(y>>t&1)==1))
					{
						int ii=i;
						if(i==0&&(x>>t&1)==1)ii=1;
						f[t][i][j][k]=(f[t][i][j][k]+f[t-1][ii][j][k])%998244353;
					}
				}
			}
		}
	}
	return f[60][0][0][0];
}
int main()
{
	freopen("qgygd.in","r",stdin);
	freopen("qgygd.out","w",stdout);
	long long ss=1;
    long long l1=0,r1=1000000000000000000ll,l2,r2,l3=0,r3=1000000000000000000ll;
	for(int i=1;i<=3;i++)
	{
		long long x,y;scanf("%lld%lld",&x,&y);
		ss=ss*((y-x+1)%998244353)%998244353;
		if(x>l1)l1=x;
		if(y<r1)r1=y;
	}
	scanf("%lld%lld",&l2,&r2);
	ss=ss*((r2-l2+1)%998244353)%998244353;
	for(int i=1;i<=3;i++)
	{
		long long x,y;scanf("%lld%lld",&x,&y);
		ss=ss*((y-x+1)%998244353)%998244353;
		if(x>l3)l3=x;
		if(y<r3)r3=y;
	}
	if(l1>r1||l3>r3)
	{
		printf("%lld\n",ss);
		return 0;
	}
	ss-=S(r1,r2,r3);
	if(l1>0)ss+=S(l1-1,r2,r3);
	if(l2>0)ss+=S(r1,l2-1,r3);
	if(l3>0)ss+=S(r1,r2,l3-1);
	if(l1>0&&l2>0)ss-=S(l1-1,l2-1,r3);
	if(l1>0&&l3>0)ss-=S(l1-1,r2,l3-1);
	if(l2>0&&l3>0)ss-=S(r1,l2-1,l3-1);
	if(l1>0&&l2>0&&l3>0)ss+=S(l1-1,l2-1,l3-1);
	printf("%lld\n",(ss%998244353+998244353)%998244353);
	return 0;
}
