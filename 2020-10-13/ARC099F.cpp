#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
struct node{long long g1,g2,g3,g4,g5,g6;int p;};
const int p1=1000000007,p2=1000000009,p3=1000000021;
long long x1p1[510000],x1p2[510000],x1p3[510000],x2p1[510000],x2p2[510000],x2p3[510000];
inline node operator+(node x,node y)
{
	return {(x.g1+y.g1*x1p1[x.p+250000])%p1,
			(x.g2+y.g2*x1p2[x.p+250000])%p2,
			(x.g3+y.g3*x1p3[x.p+250000])%p3,
			(x.g4+y.g4*x2p1[x.p+250000])%p1,
			(x.g5+y.g5*x2p2[x.p+250000])%p2,
			(x.g6+y.g6*x2p3[x.p+250000])%p3,
			x.p+y.p};
}
long long ksm(long long x,long long k,long long p)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
char s[260000];
map<long long,map<long long,map<long long,map<long long,map<long long,map<long long,int>>>>>> M;
int main()
{
	x1p1[249999]=ksm(3,p1-2,p1);x1p1[250000]=1;x1p1[250001]=3;
	for(int i=249998;i>=0;i--)x1p1[i]=x1p1[i+1]*x1p1[249999]%p1;
	for(int i=250002;i<=500000;i++)x1p1[i]=x1p1[i-1]*x1p1[250001]%p1;
	x1p2[249999]=ksm(3,p2-2,p2);x1p2[250000]=1;x1p2[250001]=3;
	for(int i=249998;i>=0;i--)x1p2[i]=x1p2[i+1]*x1p2[249999]%p2;
	for(int i=250002;i<=500000;i++)x1p2[i]=x1p2[i-1]*x1p2[250001]%p2;
	x1p3[249999]=ksm(3,p3-2,p3);x1p3[250000]=1;x1p3[250001]=3;
	for(int i=249998;i>=0;i--)x1p3[i]=x1p3[i+1]*x1p3[249999]%p3;
	for(int i=250002;i<=500000;i++)x1p3[i]=x1p3[i-1]*x1p3[250001]%p3;
	x2p1[249999]=ksm(7,p1-2,p1);x2p1[250000]=1;x2p1[250001]=7;
	for(int i=249998;i>=0;i--)x2p1[i]=x2p1[i+1]*x2p1[249999]%p1;
	for(int i=250002;i<=500000;i++)x2p1[i]=x2p1[i-1]*x2p1[250001]%p1;
	x2p2[249999]=ksm(7,p2-2,p2);x2p2[250000]=1;x2p2[250001]=7;
	for(int i=249998;i>=0;i--)x2p2[i]=x2p2[i+1]*x2p2[249999]%p2;
	for(int i=250002;i<=500000;i++)x2p2[i]=x2p2[i-1]*x2p2[250001]%p2;
	x2p3[249999]=ksm(7,p3-2,p3);x2p3[250000]=1;x2p3[250001]=7;
	for(int i=249998;i>=0;i--)x2p3[i]=x2p3[i+1]*x2p3[249999]%p3;
	for(int i=250002;i<=500000;i++)x2p3[i]=x2p3[i-1]*x2p3[250001]%p3;
	int n;scanf("%d%s",&n,s+1);
	node gs={0,0,0,0,0,0,0},pr={0,0,0,0,0,0,0};
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='+')gs=gs+(node){1,1,1,1,1,1,0};
		else if(s[i]=='-')gs=gs+(node){p1-1,p2-1,p3-1,p1-1,p2-1,p3-1,0};
		else if(s[i]=='>')gs.p++;
		else gs.p--;
	}
	long long ss=0;
	node rg=pr+gs;
	M[rg.g1][rg.g2][rg.g3][rg.g4][rg.g5][rg.g6]++;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='+')pr=pr+(node){1,1,1,1,1,1,0};
		else if(s[i]=='-')pr=pr+(node){p1-1,p2-1,p3-1,p1-1,p2-1,p3-1,0};
		else if(s[i]=='>')pr.p++;
		else pr.p--;
		ss=ss+M[pr.g1][pr.g2][pr.g3][pr.g4][pr.g5][pr.g6];
		rg=pr+gs;
		M[rg.g1][rg.g2][rg.g3][rg.g4][rg.g5][rg.g6]++;
	}
	printf("%lld\n",ss);
	return 0;
}