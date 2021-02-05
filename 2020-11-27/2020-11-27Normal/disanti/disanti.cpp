#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long gcd(long long x,long long y){return y==0?x:gcd(y,x%y);}
struct node
{
	long long x;int p;
}a[110000];
inline bool cmp(node x,node y){return x.x>y.x;}
long long AnsA[110000],AnsB[110000];
int main()
{
	freopen("disanti.in","r",stdin);
	freopen("disanti.out","w",stdout);
	int n;long long C;scanf("%d%lld",&n,&C);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].x);
		a[i].p=i;
	}
	sort(a+1,a+n+1,cmp);
	int i;
	long long ss=0;
	for(i=1;i<=n;i++)
	{
		ss=ss+a[i].x;
		if(a[i].x*i+C-ss<0)break;
	}
	i--;ss=0;
	for(int j=1;j<=i;j++)ss=ss+a[j].x;
	ss=C-ss;
	for(int j=1;j<=i;j++)
	{
		long long A=a[j].x*i+ss,B=i;
		long long tt=gcd(A,B);
		AnsA[a[j].p]=A/tt;
		AnsB[a[j].p]=B/tt;
	}
	for(int j=i+1;j<=n;j++)AnsA[a[j].p]=0;
	for(i=1;i<=n;i++)
	{
		if(AnsA[i]==0)puts("0");
		else
		{
			if(AnsB[i]==1)printf("%lld\n",AnsA[i]);
			else printf("%lld/%lld\n",AnsA[i],AnsB[i]);
		}
	}
	return 0;
}