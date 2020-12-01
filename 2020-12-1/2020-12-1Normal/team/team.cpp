#include<cstdio>
#include<cstring>
using namespace std;
int a[210000],l[210000],r[210000];
int main()
{
	freopen("team.in","r",stdin);
	freopen("team.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	while(m--)
	{
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)a[x]=y;
		else
		{
			for(int i=1;i<=n;i++)l[i]=y+1;
			long long ss=0;
			r[y+1]=y;
			for(int i=y;i>=x;i--)
			{
				r[i]=l[a[i]]-1;
				l[a[i]]=i;
				if(r[i+1]<r[i])r[i]=r[i+1];
				ss=ss+r[i]-i+1;
			}
			printf("%lld\n",ss);
		}
	}
	return 0;
}
