#include<cstdio>
#include<cstring>
using namespace std;
long long f[1100];
bool b[110];
int Ans[1100],len=0;
int main()
{
	long long n;scanf("%lld",&n);
	if(n<130)
	{
		printf("%lld\n",n);
		for(int i=1;i<=n;i++)puts("1");
		return 0;
	}
	f[1]=f[2]=1;
	int t=2;
	while(f[t]+f[t-1]<=n)
	{
		f[t+1]=f[t-1]+f[t];
		t++;
	}
	memset(b,false,sizeof(b));
	for(int i=t;i>=1;i--)
	{
		if(f[i]<=n)
		{
			n-=f[i];
			b[i]=true;
		}
	}
	if(t%2==1)
	{
		if(b[t])
		{
			Ans[++len]=1;
			Ans[++len]=4;
		}
		for(int i=t-1;i>=1;i-=2)
		{
			if(b[i-1])Ans[++len]=1;
			if(b[i])Ans[++len]=2;
			Ans[++len]=3;
			Ans[++len]=4;
		}
	}
	else
	{
		for(int i=t;i>=1;i-=2)
		{
			if(b[i-1])Ans[++len]=1;
			if(b[i])Ans[++len]=2;
			Ans[++len]=3;
			Ans[++len]=4;
		}
	}
	while(n>0)
	{
		n--;
		Ans[++len]=1;
	}
	printf("%d\n",len);
	for(int i=1;i<=len;i++)printf("%d\n",Ans[i]);
	return 0;
}