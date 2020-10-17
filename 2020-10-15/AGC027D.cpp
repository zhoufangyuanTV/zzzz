#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
long long a[510][510],p[510];
long long gcd(long long x,long long y){return y==0?x:gcd(y,x%y);}
inline long long lcm(long long x,long long y){return x/gcd(x,y)*y;}
set<long long> M;
int main()
{
	int n;scanf("%d",&n);
	M.clear();
	for(int i=1;i<=n;i++)a[0][i]=a[i][0]=a[n+1][i]=a[i][n+1]=1;
	int cnt=1;p[0]=1;
	while(cnt<=n)
	{
		p[cnt]=p[cnt-1]+1;
		bool bk=true;
		for(int i=2;i*i<=p[cnt];i++)if(p[cnt]%i==0){bk=false;break;}
		while(bk==false)
		{
			p[cnt]++;
			bk=true;
			for(int i=2;i*i<=p[cnt];i++)if(p[cnt]%i==0){bk=false;break;}
		}
		cnt++;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)%2==0)
			{
				a[i][j]=p[(i+j)/2]*p[(n-i+j)/2];
				while(M.find(a[i][j])!=M.end())a[i][j]+=p[(i+j)/2]*p[(n-i+j)/2];
				M.insert(a[i][j]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)%2==1)
			{
				long long p=lcm(lcm(a[i-1][j],a[i][j-1]),lcm(a[i+1][j],a[i][j+1]));
				a[i][j]=p+1;
				while(M.find(a[i][j])!=M.end())a[i][j]+=p;
				M.insert(a[i][j]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)printf("%lld%c",a[i][j],j==n?'\n':' ');
	}
	return 0;
}