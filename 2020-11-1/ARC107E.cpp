#include<cstdio>
#include<cstring>
using namespace std;
int a[1010000];
long long cnt[3];
inline int mex(int x,int y){return x==0?(y&1)+1:y==0?(x&1)+1:0;}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n*2-1;i++)scanf("%d",&a[i]);
	memset(cnt,0,sizeof(cnt));
	for(int i=1;n>1&&i<=3;i++,n--)
	{
		for(int j=1;j<=n*2-1;j++)cnt[a[j]]++;
		a[1]=mex(a[2],a[n+1]);
		for(int j=2;j<n;j++)a[j]=mex(a[j-1],a[j+1]);
		a[n]=mex(a[1],a[n+2]);
		for(int j=n+1;j<=n*2-3;j++)a[j]=mex(a[j-1],a[j+2]);
	}
	for(int i=1,j=n;i<=n;i++,j--)cnt[a[i]]+=j;
	for(int i=n+1,j=n-1;i<=n*2-1;i++,j--)cnt[a[i]]+=j;
	printf("%lld %lld %lld\n",cnt[0],cnt[1],cnt[2]);
	return 0;
}