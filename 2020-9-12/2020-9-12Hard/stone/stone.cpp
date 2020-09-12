#include<cstdio>
#include<cstring>
using namespace std;
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
long long jc[110000],fjc[110000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
bool f[110][110][2];
int c[110000];
int main()
{
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	jc[0]=1;
	for(int i=1;i<=100000;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[100000]=ksm(jc[100000],1000000005);
	for(int i=99999;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	int n,a,b;scanf("%d%d%d",&n,&a,&b);
	int t=0;
	if(a>b){t=a;a=b;b=t;}
	int sa=0,sb=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		c[i]%=a+b;
		if(c[i]>=b)sb++;
		else if(c[i]>=a)sa++;
	}
	long long Alice=0,Bob=0,first=0,second=0;
	if(a==b)
	{
		for(int i=1;i<=sb;i+=2)first=(first+C(sb,i))%1000000007;
		second=(ksm(2,sb)-first+1000000007)%1000000007;
		long long k=ksm(2,n-sa-sb);
		printf("%lld %lld %lld %lld\n",k*Alice%1000000007,k*Bob%1000000007,k*first%1000000007,k*second%1000000007);
		return 0;
	}
	memset(f,false,sizeof(f));
	for(int i=0;i<=sa;i++)
	{
		for(int j=0;j<=sb;j++)
		{
			if(i>0&&f[i-1][j][1]==false)f[i][j][0]=true;
			if(j>0&&f[i][j-1][1]==false)f[i][j][0]=true;
			if(j>0&&f[i][j-1][0]==false)f[i][j][1]=true;
			if(f[i][j][0]==true&&f[i][j][1]==false)Alice=(Alice+C(sa,i)*C(sb,j)%1000000007)%1000000007;
			else if(f[i][j][0]==false&&f[i][j][1]==true)Bob=(Bob+C(sa,i)*C(sb,j)%1000000007)%1000000007;
			else if(f[i][j][0]==true&&f[i][j][1]==true)first=(first+C(sa,i)*C(sb,j)%1000000007)%1000000007;
			else second=(second+C(sa,i)*C(sb,j)%1000000007)%1000000007;
		}
	}
	if(t>0){t=Alice;Alice=Bob;Bob=t;}
	long long k=ksm(2,n-sa-sb);
	printf("%lld %lld %lld %lld\n",k*Alice%1000000007,k*Bob%1000000007,k*first%1000000007,k*second%1000000007);
	return 0;
}