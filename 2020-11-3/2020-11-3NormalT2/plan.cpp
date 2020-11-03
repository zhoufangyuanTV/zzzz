#include<cstdio>
#include<cstring>
using namespace std;
int fl[51000],fr[51000],l[51000],r[51000],a[51000],c[51000];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("plan.in","r",stdin);
	freopen("plan.out","w",stdout);
	int n,L,R;scanf("%d%d%d",&n,&L,&R);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++)l[i]=L-a[i]-a[i+1],r[i]=R-a[i]-a[i+1];
	fl[1]=0;fr[1]=0x3f3f3f3f;
	for(int i=2;i<=n;i++)
	{
		fl[i]=mymax(l[i-1]-fr[i-1],0);
		fr[i]=r[i-1]-fl[i-1];
	}
	if(fl[n]>fr[n]){puts("-1");return 0;}
	long long ss=fl[n];c[n]=fl[n];
	for(int j=n-1;j>=1;j--)
	{
		c[j]=mymax(l[j]-c[j+1],fl[j]);
		ss=ss+c[j];
	}
	printf("%lld\n",ss);
	for(int i=1;i<n;i++)printf("%d ",a[i]+c[i]);
	printf("%d\n",a[n]+c[n]);
	return 0;
}