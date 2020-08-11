#include<cstdio>
#include<cstring>
using namespace std;
long double f[3100][3100],a[3100];
inline long double mymin(long double x,long double y){return x<y?x:y;}
int main()
{
	int n;long double t;scanf("%d%Lf",&n,&t);
	for(int i=1;i<=n;i++)scanf("%Lf",&a[i]),a[i]=1-a[i];
	f[n][n]=0;
	for(int i=n-1;i>=0;i--)
	{
		long double ss=0,ps=1,su=a[i+1];
		for(int j=i+1;j<=n;j++)
		{
			ps=ps*a[j];
			ss=ss+ps*(j<n?1-a[j+1]:1)*f[j][j]+ps*(j<n?1-a[j+1]:1)*(n-j);
		}
		for(int j=n;j>=i+1;j--)
		{
			long double ff=t+ss;
			f[i][j]=(ff+2*(1-a[i+1])*(j-i))/a[i+1];
 			if(j<n)f[i][j]=mymin(f[i][j],f[i][j+1]+1);
			ss=ss-ps*f[j][j]-su+ps;
			ss=ss+ps*f[j-1][j-1];
			ps=ps/a[j];
		}
		f[i][i]=f[i][i+1]+1;
	}
	printf("%.15Lf\n",f[0][0]);
	return 0;
}