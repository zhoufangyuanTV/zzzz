#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int a[110000],b[110000];
char s[110000];
int main()
{
	freopen("T1.in","r",stdin);
	freopen("T1.ans","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=0;
	int t;scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='A')
		{
			int ll,rr,cg;scanf("%d%d%d",&ll,&rr,&cg);
			for(int i=ll;i<=rr;i++)
			{
				if(cg!=0){a[i]+=cg;b[i]++;}
			}
		}
		else if(s[1]=='M')
		{
			int ll,rr,cg;scanf("%d%d%d",&ll,&rr,&cg);
			for(int i=ll;i<=rr;i++)
			{
				if(cg>a[i])a[i]=cg,b[i]++;
			}
		}
		else if(s[1]=='Q')
		{
			int x;scanf("%d",&x);
			printf("%d %d\n",a[x],b[x]);
		}
	}
	return 0;
}