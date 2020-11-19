#include<cstdio>
#include<cstring>
using namespace std;
#define p 998244353
struct node
{
	long long a[131072];
	void fwt(int[2][2]);
}A,B,C;int len;
void node::fwt(int w[2][2])
{
	for(int i=1;i<len;i<<=1)
	{
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long jk=a[j+k],ijk=a[i+j+k];
				a[j+k]=(w[0][0]*jk+w[0][1]*ijk)%p;
				a[i+j+k]=(w[1][0]*jk+w[1][1]*ijk)%p;
			}
		}
	}
}
int OR[2][2]={1,0,1,1},AND[2][2]={1,1,0,1},XOR[2][2]={1,1,1,p-1};
int RO[2][2]={1,0,p-1,1},DNA[2][2]={1,p-1,0,1},ROX[2][2]={(p+1)/2,(p+1)/2,(p+1)/2,p/2};
int main()
{
	scanf("%d",&len);
	len=1<<len;
	for(int i=0;i<len;i++)scanf("%lld",&A.a[i]);
	for(int i=0;i<len;i++)scanf("%lld",&B.a[i]);
	A.fwt(OR);B.fwt(OR);
	for(int i=0;i<len;i++)C.a[i]=A.a[i]*B.a[i]%p;
	A.fwt(RO);B.fwt(RO);C.fwt(RO);
	for(int i=0;i<=len-2;i++)printf("%lld ",C.a[i]);
	printf("%lld\n",C.a[len-1]);
	A.fwt(AND);B.fwt(AND);
	for(int i=0;i<len;i++)C.a[i]=A.a[i]*B.a[i]%p;
	A.fwt(DNA);B.fwt(DNA);C.fwt(DNA);
	for(int i=0;i<=len-2;i++)printf("%lld ",C.a[i]);
	printf("%lld\n",C.a[len-1]);
	A.fwt(XOR);B.fwt(XOR);
	for(int i=0;i<len;i++)C.a[i]=A.a[i]*B.a[i]%p;
	A.fwt(ROX);B.fwt(ROX);C.fwt(ROX);
	for(int i=0;i<=len-2;i++)printf("%lld ",C.a[i]);
	printf("%lld\n",C.a[len-1]);
	return 0;
}