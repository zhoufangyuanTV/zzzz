#include<cstdio>
#include<cstring>
using namespace std;
struct number
{
	long long w,x,y,z;
}a[110][110],b[110][110],c[110][110];
inline number operator+(number x,number y)
{
	number z;
	z.w=x.w+y.w;
	z.x=x.x+y.x;
	z.y=x.y+y.y;
	z.z=x.z+y.z;
	if(z.z>=1000000000000000ll)z.y++,z.z-=1000000000000000ll;
	if(z.y>=1000000000000000ll)z.x++,z.y-=1000000000000000ll;
	if(z.x>=1000000000000000ll)z.w++,z.x-=1000000000000000ll;
	return z;
}
inline number operator-(number x,number y)
{
	number z;
	z.w=x.w-y.w;
	z.x=x.x-y.x;
	z.y=x.y-y.y;
	z.z=x.z-y.z;
	if(z.z<0)z.y--,z.z+=1000000000000000ll;
	if(z.y<0)z.x--,z.y+=1000000000000000ll;
	if(z.x<0)z.w--,z.x+=1000000000000000ll;
	return z;
}
int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)a[i][1]=a[n][i]=b[n][i]=c[n][i]=(number){0,0};
	number e;e.w=e.x=e.y=0;e.z=1;
	for(int i=n-1;i>=1;i--)
	{
		for(int j=2;j<=n;j++)
		{
			a[i][j]=b[i+1][j-1]-c[i+1][j]+e;
		}
		for(int j=n;j>=1;j--)
		{
			c[i][j]=c[i+1][j]+a[i][j];
			if(j==n)b[i][j]=c[i][j];
			else b[i][j]=b[i][j+1]+a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<n;j++)
		{
			printf("%lld%015lld%015lld%015lld ",a[i][j].w,a[i][j].x,a[i][j].y,a[i][j].z);
		}
		printf("%lld%015lld%015lld%015lld\n",a[i][n].w,a[i][n].x,a[i][n].y,a[i][n].z);
	}
	return 0;
}