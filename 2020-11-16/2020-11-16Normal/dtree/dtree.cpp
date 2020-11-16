#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110],l[110],r[110];
int sta[110],top;
int main()
{
	freopen("dtree.in","r",stdin);
	freopen("dtree.out","w",stdout);
	int n,p;scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)a[i]=i;
	int ss=0;
	do
	{
		top=0;
		for(int i=1;i<=n;i++)
		{
			if(i==1||a[i]<a[i-1])l[i]=0;
			else
			{
				while(top>0&&a[sta[top]]<a[i])top--;
				l[i]=sta[top+1];
			}
			sta[++top]=i;
		}
		top=0;
		for(int i=n;i>=1;i--)
		{
			if(i==n||a[i]<a[i+1])r[i]=0;
			else
			{
				while(top>0&&a[sta[top]]<a[i])top--;
				r[i]=sta[top+1];
			}
			sta[++top]=i;
		}
		for(int i=1;i<=n;i++)
		{
			if(l[i]!=0&&r[i]!=0)ss=(ss+r[i]-l[i])%p;
		}
	}while(next_permutation(a+1,a+n+1));
	printf("%d\n",ss);
	return 0;
}