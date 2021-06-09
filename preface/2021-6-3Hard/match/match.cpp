#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
using namespace std;
struct Bpoly
{
	bitset<314> x;
};
struct Spoly
{
	int x;
};
inline Bpoly operator+(Bpoly x,Bpoly y){return (Bpoly){x.x^y.x};}
inline Bpoly operator*(Bpoly x,Spoly y)
{
	Bpoly z;
	for(int i=0;i<=9;i++)
	{
		if(y.x>>i&1)z.x^=x.x<<i;
	}
	return z;
}
inline Bpoly operator%(Bpoly x,Bpoly y)
{
	int n;
	for(n=313;n>=0;n--)if(y.x[n])break;
	for(int i=313;i>=n;i--)
	{
		if(x.x[i])x.x^=y.x<<i-n;
	}
	return x;
}
inline Spoly operator+(Spoly x,Spoly y){return (Spoly){x.x^y.x};}
inline Spoly operator*(Spoly x,Spoly y)
{
	Spoly z;z.x=0;
	for(int i=0;i<=9;i++)
	{
		if(x.x>>i&1)z.x^=y.x<<i;
	}
	return z;
}
inline Spoly operator%(Spoly x,Spoly y)
{
	int n;
	for(n=9;n>=0;n--)if(y.x>>n&1)break;
	for(int i=18;i>=n;i--)
	{
		if(x.x>>i&1)x.x^=y.x<<i-n;
	}
	return x;
}
bool b[1024];
Spoly S[35];
int M=34;
Spoly mul[512][512],fc[512];
char Ai[310][310],Bi[310][310];
Spoly Z[310][310];
int main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%s",Ai[i]+1);
	for(int i=1;i<=n;i++)scanf("%s",Bi[i]+1);
	memset(b,true,sizeof(b));
	for(int i=1;i<=8;i++)
	{
		for(int j=0;j<1<<i;j++)
		{
			Spoly x;x.x=1<<i|j;
			if(b[x.x])
			{
				for(int k=1;k<=9-i;k++)
				{
					for(int l=0;l<1<<k;l++)
					{
						Spoly y;y.x=1<<k|l;
						b[(x*y).x]=false;
					}
				}
			}
		}
	}
	for(int i=512;i<=1023;i++)
	{
		if(M==0)break;
		if(b[i])S[M--].x=i;
	}
	Bpoly ss;
	for(int i=1;i<=34;i++)
	{
		for(int j=0;j<=511;j++)
		{
			Spoly x;x.x=j;
			for(int k=0;k<=511;k++)
			{
				Spoly y;y.x=k;
				mul[j][k]=x*y%S[i];
				if(mul[j][k].x==1)fc[j]=y;
			}
		}
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				Z[j][k].x=Ai[j][k]-'0'<<1|Bi[j][k]-'0';
			}
		}
		Spoly s;s.x=1;
		for(int j=1;j<=n;j++)
		{
			if(Z[j][j].x==0)
			{
				for(int k=j+1;k<=n;k++)
				{
					if(Z[k][j].x!=0)
					{
						for(int l=j;l<=n;l++)swap(Z[j][l],Z[k][l]);
						break;
					}
				}
				if(Z[j][j].x==0){s.x=0;break;}
			}
			Spoly f=fc[Z[j][j].x];
			for(int k=j+1;k<=n;k++)
			{
				Spoly g=mul[f.x][Z[k][j].x];
				for(int l=j;l<=n;l++)Z[k][l]=Z[k][l]+mul[Z[j][l].x][g.x];
			}
			s=mul[s.x][Z[j][j].x];
		}
		Bpoly Mi;Spoly mi;
		Mi.x[0]=1;mi.x=1;
		for(int j=1;j<=34;j++)
		{
			if(i!=j)
			{
				Mi=Mi*S[j];
				mi=mul[mi.x][S[j].x^S[i].x];
			}
		}
		mi=fc[mi.x];
		Mi=Mi*mi*s;
		ss=ss+Mi;
	}
	Bpoly cj;cj.x[0]=1;
	for(int i=1;i<=34;i++)cj=cj*S[i];
	ss=ss%cj;
	int q;scanf("%d",&q);
	while(q--)
	{
		int x;scanf("%d",&x);
		printf("%d\n",ss.x.test(x));
	}
	return 0;
}