#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
long long c[2][2]={{1,1},{1,-1}},cc[3][3]={{1,1,1},{1,115381398,884618610},{1,884618610,115381398}};
long long ic[2][2]={{500000005,500000005},{500000005,500000004}};
long long icc[3][3]={{666666673,666666673,666666673},{666666673,294872870,38460466},{666666673,38460466,294872870}};
long long a[2187][51][51],S[2187];
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%1000000009;
		x=x*x%1000000009;
		k>>=1;
	}
	return s;
}
long long det(int n,long long A[51][51])
{
	long long s=1;
	for(int i=1;i<=n;i++)
	{
		if(A[i][i]==0)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(A[j][i]!=0)
				{
					s=(1000000009-s)%1000000009;
					for(int k=i;k<=n;k++)A[i][k]^=A[j][k]^=A[i][k]^=A[j][k];
					break;
				}
			}
		}
		if(A[i][i]==0)return 0;
		s=s*A[i][i]%1000000009;
		long long f=ksm(A[i][i],1000000007);
		for(int j=i+1;j<=n;j++)
		{
			long long ff=(1000000009-f*A[j][i]%1000000009)%1000000009;
			for(int k=i;k<=n;k++)A[j][k]=(A[j][k]+A[i][k]*ff)%1000000009;
		}
	}
	return s;
}
int main()
{
	freopen("astrology.in","r",stdin);
	freopen("astrology.out","w",stdout);
	int n,k;scanf("%*d%d%d",&n,&k);
	if(k==2)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int x;scanf("%d",&x);
				long long v=rand()%1000000009;
				for(int y=0;y<128;y++)
				{
					long long vv=v;
					for(int l=0;l<7;l++)vv=vv*c[y>>l&1][x>>l&1]%1000000009;
					a[y][i][j]=vv;
				}
			}
		}
		for(int i=0;i<128;i++)S[i]=det(n,a[i]);
		for(int i=0;i<128;i++)
		{
			long long ss=0;
			for(int j=0;j<128;j++)
			{
				long long vv=S[j];
				for(int l=0;l<7;l++)vv=vv*ic[i>>l&1][j>>l&1]%1000000009;
				ss=(ss+vv)%1000000009;
			}
			if(ss!=0)printf("%d ",i);
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int x;scanf("%d",&x);
				long long v=rand()%1000000009;
				for(int y=0;y<2187;y++)
				{
					long long vv=v;
					int xx=x,yy=y;
					for(int l=0;l<7;l++)
					{
						vv=vv*cc[yy%3][xx%3]%1000000009;
						xx/=3;yy/=3;
					}
					a[y][i][j]=vv;
				}
			}
		}
		for(int i=0;i<2187;i++)S[i]=det(n,a[i]);
		for(int i=0;i<2187;i++)
		{
			long long ss=0;
			for(int j=0;j<2187;j++)
			{
				long long vv=S[j];
				int x=i,y=j;
				for(int l=0;l<7;l++)
				{
					vv=vv*icc[x%3][y%3]%1000000009;
					x/=3;y/=3;
				}
				ss=(ss+vv)%1000000009;
			}
			if(ss!=0)printf("%d ",i);
		}
	}
	return 0;
}