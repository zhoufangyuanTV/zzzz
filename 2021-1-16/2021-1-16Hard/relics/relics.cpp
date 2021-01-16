#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int a[210000];
int sta[210000],top;
inline long long mymax(long long x,long long y){return x>y?x:y;}
int main()
{
	freopen("relics.in","r",stdin);
	freopen("relics.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		int tt=a[l-1];a[l-1]=0;sta[top=1]=l-1;
		long long ss=0;
		for(int j=l;j<=r;j++)
		{
			while(top>0&&a[j]<=a[sta[top]])
			{
				ss=mymax(ss,1ll*(j-sta[top-1]-1)*a[sta[top]]);
				top--;
			}
			sta[++top]=j;
		}
		while(top>1)
		{
			ss=mymax(ss,1ll*(r-sta[top-1])*a[sta[top]]);
			top--;
		}
		printf("%lld\n",ss);
		a[l-1]=tt;
	}
	return 0;
}