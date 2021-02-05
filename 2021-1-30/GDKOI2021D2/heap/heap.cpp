#include<cstdio>
#include<cstring>
using namespace std;
int a[110000],b[110000];
int N;
inline void down(int x)
{
	while(x*2<=N)
	{
		int y=x*2;
		if(y<N&&b[y+1]<b[y])y++;
		if(b[x]<b[y])break;
		b[x]^=b[y]^=b[x]^=b[y];
		x=y;
	}
}
int main()
{
	freopen("heap.in","r",stdin);
	freopen("heap.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int opt,l,r,x;scanf("%d%d%d%d",&opt,&l,&r,&x);
		for(int j=1;j<=r-l+1;j++)b[j]=a[l+j-1];
		N=r-l+1;
		for(int j=N;j>=1;j--)down(j);
		if(opt==1)printf("%d\n",b[x]);
		else
		{
			for(int j=1;j<=N;j++)
			{
				if(b[j]==x){printf("%d\n",j);break;}
			}
		}
	}
	return 0;
}
