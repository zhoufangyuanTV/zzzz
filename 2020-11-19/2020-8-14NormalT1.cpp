#include<cstdio>
#include<cstring>
using namespace std;
long long p;
inline long long mul(long long x,long long y){return x*y-(long long)((long double)x*y/p)*p;}
struct node
{
	long long a[262144];
	void fwt();
}F,A;int len;
void node::fwt()
{
	for(int i=1;i<len;i<<=1)
	{
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long jk=a[j+k],ijk=a[i+j+k];
				a[j+k]=(jk+ijk)%p;
				a[i+j+k]=(jk-ijk+p)%p;
			}
		}
	}
}
int cnt[262144],B[110];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=mul(s,x);
		x=mul(x,x);
		k>>=1;
	}
	return s;
}
int main()
{
	int g;
	scanf("%d%lld",&len,&p);
	g=len;
	long long phi=1,pp=p;
	bool bk=false;
	for(int i=2;i*i<=pp;i++)
	{
		if(pp%i==0)
		{
			if(i==2)bk=true;
			pp=pp/i;
			phi=phi*(i-1);
			while(pp%i==0)pp=pp/i,phi=phi*i;
		}
	}
	if(pp>1)phi=phi*(pp-1);
	p<<=len;
	phi<<=len-1;
	if(bk)phi<<=1;
	bk=false;
	len=1<<len;
	long long T=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){if(phi<=T*10+c-'0')bk=true;T=(T*10+c-'0')%phi;c=getchar();}
	if(bk==true)T+=phi;
	for(int i=0;i<len;i++)scanf("%lld",&F.a[i]);
	for(int i=0;i<len;i++)F.a[i]=F.a[i]%p;
	cnt[0]=0;
	for(int i=1;i<len;i++)cnt[i]=cnt[i>>1]+(i&1);
	for(int i=0;i<=g;i++)scanf("%d",&B[i]);
	scanf("%*d");
	for(int i=0;i<len;i++)A.a[i]=B[cnt[i]]%p;
	F.fwt();A.fwt();
	for(int i=0;i<len;i++)F.a[i]=mul(F.a[i],ksm(A.a[i],T));
	F.fwt();
	for(int i=0;i<len;i++)printf("%lld\n",F.a[i]>>g);
	return 0;
}