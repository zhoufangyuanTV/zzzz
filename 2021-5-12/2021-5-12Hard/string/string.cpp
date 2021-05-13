#include<cstdio>
#include<cstring>
using namespace std;
inline long long mymax(long long x,long long y){return x>y?x:y;}
template<int n,int m>
struct matrix{long long a[n][m];};
template<int n,int m,int nm>
inline matrix<n,m> operator*(matrix<n,nm> x,matrix<nm,m> y)
{
	matrix<n,m> z;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			z.a[i][j]=-1;
			for(int k=0;k<nm;k++)
			{
				if(x.a[i][k]!=-1&&y.a[k][j]!=-1)z.a[i][j]=mymax(z.a[i][j],x.a[i][k]+y.a[k][j]);
			}
		}
	}
	return z;
}
template<int n>
inline matrix<n,1> ksm(matrix<n,1> s,matrix<n,n> x,long long k)
{
	while(k>0)
	{
		if(k&1)s=x*s;
		x=x*x;
		k>>=1;
	}
	return s;
}
char s[110000];
bool b[4][4][10],v[4][4][65536];
long long f[11][4];
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	long long n;scanf("%lld%s",&n,s+1);
	bool bk1=false,bk2=false,bk3=false,bk4=false;
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
	{
		if(s[i]=='A')bk1=true;
		else if(s[i]=='B')bk2=true;
		else if(s[i]=='C')bk3=true;
		else if(s[i]=='D')bk4=true;
	}
	if(!bk1||!bk2||!bk3||!bk4)
	{
		int ss=0,t=1000000000;
		while(t--)ss^=t;
		printf("%d\n",ss);
		return 0;
	}
	for(int i=0;i<=8;i++)
	{
		memset(v,false,sizeof(v));
		for(int j=1;j+i+1<=len;j++)
		{
			int ss=0;
			for(int k=1;k<=i;k++)ss=ss*4+s[j+k]-'A';
			v[s[j]-'A'][s[j+i+1]-'A'][ss]=true;
		}
		int ss=1;
		for(int k=1;k<=i;k++)ss=ss*4;
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				b[j][k][i]=false;
				for(int l=0;l<ss;l++)
				{
					if(v[j][k][l]==false){b[j][k][i]=true;break;}
				}
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			b[i][j][9]=true;
		}
	}
	matrix<40,40> A;
	memset(A.a,-1,sizeof(A.a));
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<=9;k++)
			{
				if(b[i][j][k]==true)A.a[i][k*4+j]=1;
			}
		}
	}
	for(int i=4;i<40;i++)A.a[i][i-4]=0;
	matrix<40,1> B;
	for(int i=1;i<=10;i++)
	{
		for(int j=0;j<4;j++)
		{
			f[i][j]=1;
			for(int k=1;k<i;k++)
			{
				for(int l=0;l<4;l++)
				{
					if(b[j][l][k-1]==true)f[i][j]=mymax(f[i][j],f[i-k][l]+1);
				}
			}
			B.a[(10-i)*4+j][0]=f[i][j];
		}
	}
	matrix<40,1> S=ksm(B,A,n-1);
	printf("%lld\n",mymax(mymax(S.a[36][0],S.a[37][0]),mymax(S.a[38][0],S.a[39][0])));
	return 0;
}
