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
	int sa=0,sb=0,sc=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		c[i]%=a+b;
		if(c[i]<a)continue;
		if(c[i]<b)sa++;
		else if(c[i]<2*a)sb++;
		else sc++;
	}
	long long Alice=(ksm(2,sa)*ksm(2,sb)%1000000007*ksm(2,sc)%1000000007-ksm(2,sb)*(sc+1)%1000000007+1000000007)%1000000007,Bob=0,first=0,second=0;
	for(int i=0;i<=sb;i++)
	{
		if(i&1)first=(first+C(sb,i))%1000000007;
		else second=(second+C(sb,i))%1000000007;
	}
	Alice=(Alice+first*sc%1000000007)%1000000007;
	first=(first+second*sc%1000000007)%1000000007;
	long long k=ksm(2,n-sa-sb-sc);
	long long tt=0;
	if(t>0){tt=Alice;Alice=Bob;Bob=tt;}
	printf("%lld %lld %lld %lld\n",k*Alice%1000000007,k*Bob%1000000007,k*first%1000000007,k*second%1000000007);
	return 0;
}