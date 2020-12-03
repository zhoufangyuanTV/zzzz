#include<cstdio>
#include<cstring>
using namespace std;
inline long long S(int xx,int yy,int xxx,int yyy)
{
	return (1ll*xx*yyy-1ll*xxx*yy)/2;
}
int gcd(int x,int y)
{
	if(x<0)x=-x;
	if(y<0)y=-y;
	return y==0?x:gcd(y,x%y);
}
int main()
{
	freopen("delta.in","r",stdin);
	freopen("delta.out","w",stdout);
	int n,m,kk;scanf("%d%d%d",&n,&m,&kk);
	long long ss=0;
	for(int i=0;i<(n+1)*(m+1);i++)
	{
		for(int j=i+1;j<(n+1)*(m+1);j++)
		{
			for(int k=j+1;k<(n+1)*(m+1);k++)
			{
				int x=i/(m+1),y=i%(m+1);
				int xx=j/(m+1)-x,yy=j%(m+1)-y;
				int xxx=k/(m+1)-x,yyy=k%(m+1)-y;
				if(gcd(gcd(xx,yy),gcd(xxx,yyy))==1)
				{
					long long SG=S(xx,yy,xxx,yyy);
					if(SG%kk==0&&SG!=0)ss++;
				}
			}
		}
	}
	printf("%lld\n",ss%1000000007);
	return 0;
}
