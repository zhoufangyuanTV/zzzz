#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[510000],Ans[510000];
int main()
{
	freopen("shepherd.in","r",stdin);
	freopen("shepherd.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)scanf("%*d%*d");
	for(int i=1;i<=m;i++)scanf("%d",&a[i]);
	sort(a+1,a+m+1);
	int ss=0;bool bk=false;
	for(int i=1;i<=m;i++)
	{
		if(bk)
		{
			if((a[i-1]+a[i])%2==0)Ans[ss]=(a[i-1]+a[i])/2,bk=false;
			else Ans[++ss]=a[i],bk=true;
		}
		else Ans[++ss]=a[i],bk=true;
	}
	printf("%d\n",ss);
	for(int i=1;i<ss;i++)printf("%d ",Ans[i]);
	printf("%d\n",Ans[ss]);
	return 0;
}
