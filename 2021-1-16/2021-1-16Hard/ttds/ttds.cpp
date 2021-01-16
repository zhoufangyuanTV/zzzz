#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110000];
int lg2[1048577];
int S[1048576];
inline int lowbit(int x){return x&-x;}
inline bool cmp(int x,int y)
{
	while(x>0&&y>0)
	{
		int xx=a[lg2[lowbit(x)]],yy=a[lg2[lowbit(y)]];
		if(xx<yy)return true;
		else if(xx>yy)return false;
		x-=lowbit(x);y-=lowbit(y);
	}
	if(y>0)return true;
	else return false;
}
int main()
{
	freopen("ttds.in","r",stdin);
	freopen("ttds.out","w",stdout);
	int n,k,b;scanf("%d%d%d",&n,&k,&b);
	lg2[0]=0;
	for(int i=1;i<=1<<n;i++)lg2[i]=lg2[i/2]+1;
	for(int i=1;i<1<<n;i++)S[i]=i;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(S+1,S+(1<<n),cmp);
	for(int i=1;i<=k;i++)
	{
		long long ss=0;int x=S[i];
		while(x>0)
		{
			ss=(ss*b+a[lg2[lowbit(x)]])%998244353;
			x-=lowbit(x);
		}
		printf("%lld\n",ss);
	}
	return 0;
}