#include<cstdio>
#include<cstring>
using namespace std;
double f[3100][3100],a[3100];
inline double mymin(double x,double y){return x<y?x:y;}
int main()
{
	int n;double t;scanf("%d%lf",&n,&t);
	for(int i=1;i<=n;i++)scanf("%lf",&a[i]),a[i]=1-a[i];
	f[n][n]=0;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=n;j>=i+1;j--)
		{
			double ff=t,pp=1;
			for(int k=i+1;k<=j;k++)
			{
				pp=pp*a[k];
				ff=ff+pp*(k<j?1-a[k+1]:1)*(f[k][k]+j-k);
			}
			f[i][j]=(ff+2*(1-a[i+1])*(j-i))/a[i+1];
			if(j<n)f[i][j]=mymin(f[i][j],f[i][j+1]+1);
			printf("%lf\n",f[i][j]);
		}
		f[i][i]=f[i][i+1]+1;
	}
	printf("%.15lf\n",f[0][0]);
	return 0;
}