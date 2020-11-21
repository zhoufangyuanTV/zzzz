#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
long long M;
long long a[42768],A[110000],b[42768],B[110000];
long long h[110000];int x[110000],y[110000];
int main()
{
	freopen("satellite.in","r",stdin);
	freopen("satellite.out","w",stdout);
	int n,q;scanf("%d%d%*lld%*lld%lld%lld%lld",&n,&q,&M,&a[1],&b[1]);
	a[0]=A[0]=b[0]=B[0]=1;
	for(int i=2;i<=32768;i++)a[i]=a[i-1]*a[1]%M;
	A[1]=a[32768];
	for(int i=2;i<=100000;i++)A[i]=A[i-1]*A[1]%M;
	for(int i=2;i<=32768;i++)b[i]=b[i-1]*b[1]%M;
	B[1]=b[32768];
	for(int i=2;i<=100000;i++)B[i]=B[i-1]*B[1]%M;
	for(int i=1;i<=n;i++)scanf("%lld%d%d",&h[i],&x[i],&y[i]);
	while(q--)
	{
		int px,qy;scanf("%d%d",&px,&qy);
		long long ss=0;
		for(int i=1;i<=n;i++)
		{
			int xx=abs(px-x[i]),yy=abs(qy-y[i]);
			ss=(ss+h[i]*a[xx&32767]%M*A[xx>>15]%M*b[yy&32767]%M*B[yy>>15])%M;
		}
		printf("%lld\n",ss);
	}
	return 0;
}