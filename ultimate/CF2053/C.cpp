#include<cstdio>
#include<cstring>
using namespace std;
void dfs(int x,int k,long long &s,long long &ss)
{
	if(x<k){s=ss=0;return ;}
	if(x&1)
	{
		int m=(x+1)/2;
		s=1;ss=m;
		long long gs=0,gss=0;
		dfs(m-1,k,gs,gss);
		s+=gs*2;ss+=gss*2+gs*m;
	}
	else
	{
		int m=x/2;
		long long gs=0,gss=0;
		dfs(m,k,gs,gss);
		s=gs*2;ss=gss*2+m*gs;
	}
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,k;scanf("%d%d",&n,&k);
		long long s=0,ss=0;
		dfs(n,k,s,ss);
		printf("%lld\n",ss);
	}
	return 0;
}