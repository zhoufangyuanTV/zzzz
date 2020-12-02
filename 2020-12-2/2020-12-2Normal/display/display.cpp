#include<cstdio>
#include<cstring>
using namespace std;
template<int n,int m>
struct matrix
{
	long long a[n][m];
	matrix(){memset(a,0,sizeof(a));}
};
template<int n,int nm,int m>
matrix<n,m> operator*(matrix<n,nm> x,matrix<nm,m> y)
{
	matrix<n,m> z;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			z.a[i][j]=0;
			for(int k=0;k<nm;k++)z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%1000000007;
		}
	}
	return z;
}
int popcount[1024];
int g[100];
int main()
{
	freopen("display.in","r",stdin);
	freopen("display.out","w",stdout);
	popcount[0]=0;
	for(int i=1;i<1024;i++)popcount[i]=popcount[i>>1]+(i&1);
	g[0]=2+8;
	g[1]=2;
	g[2]=1+8;
	g[3]=1+2+4;
	g[4]=2+16;
	g[5]=1+4+16;
	g[6]=4+8;
	g[7]=1+2;
	g[8]=1+4+8+16;
	g[9]=1+2+4+16;
	for(int i=10;i<100;i++)
	{
		int a=i/10,b=i%10;
		g[i]=g[b]+(g[a]<<5);
	}
	long long n,k;int m,x;scanf("%d%lld%lld%d",&m,&n,&k,&x);
	if(m==2)
	{
		for(int i=0;i<10;i++)g[i]=g[i]+(10<<5);
	}
	if(m==1)
	{
		matrix<1,6> S,SS;
		S.a[0][0]=1;SS.a[0][0]=1;
		matrix<6,6> A;
		for(int i=1;i<=5;i++)A.a[i][i-1]=6-i;
		for(int i=0;i<5;i++)A.a[i][i+1]=i+1;
		long long kk=k,kkk=n%k;
		while(kk>0)
		{
			if(kk&1)S=S*A;
			if(kkk&1)SS=SS*A;
			A=A*A;
			kk>>=1;
			kkk>>=1;
		}
		matrix<10,10> B,BB;
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<10;j++)
			{
				B.a[i][j]=S.a[0][popcount[g[i]^g[j]]];
				BB.a[i][j]=SS.a[0][popcount[g[i]^g[j]]];
			}
		}
		matrix<1,10> F;F.a[0][x]=1;
		k=n/k;
		while(k>0)
		{
			if(k&1)F=F*B;
			B=B*B;
			k>>=1;
		}
		F=F*BB;
		for(int i=0;i<10;i++)printf("%lld\n",F.a[0][i]);
	}
	else
	{
		matrix<1,11> S,SS;
		S.a[0][0]=1;SS.a[0][0]=1;
		matrix<11,11> A;
		for(int i=1;i<=10;i++)A.a[i][i-1]=11-i;
		for(int i=0;i<10;i++)A.a[i][i+1]=i+1;
		long long kk=k,kkk=n%k;
		while(kk>0)
		{
			if(kk&1)S=S*A;
			if(kkk&1)SS=SS*A;
			A=A*A;
			kk>>=1;
			kkk>>=1;
		}
		matrix<100,100> B,BB;
		for(int i=0;i<100;i++)
		{
			for(int j=0;j<100;j++)
			{
				B.a[i][j]=S.a[0][popcount[g[i]^g[j]]];
				BB.a[i][j]=SS.a[0][popcount[g[i]^g[j]]];
			}
		}
		matrix<1,100> F;F.a[0][x]=1;
		k=n/k;
		while(k>0)
		{
			if(k&1)F=F*B;
			B=B*B;
			k>>=1;
		}
		F=F*BB;
		for(int i=0;i<100;i++)printf("%lld\n",F.a[0][i]);
	}
	return 0;
}
