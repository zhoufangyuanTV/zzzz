#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long M;
long long a[42768],A[110000],b[42768],B[110000];
struct node
{
	long long h;int x,y;
}c[2100];
inline bool operator<(node x,node y){return x.x==y.x?x.y<y.y:x.x<y.x;}
struct Query
{
	int x,y,p;
}Q[210000];
int Ans[210000];
inline bool operator<(Query x,Query y){return x.x==y.x?x.y<y.y:x.x<y.x;}
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
	for(int i=1;i<=n;i++)scanf("%lld%d%d",&c[i].h,&c[i].x,&c[i].y);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&Q[i].x,&Q[i].y);
		Q[i].p=i;
	}
	sort(c+1,c+n+1);
	sort(Q+1,Q+q+1);
	return 0;
}