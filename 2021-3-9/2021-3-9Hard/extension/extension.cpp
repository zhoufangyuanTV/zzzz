#include<cstdio>
#include<cstring>
using namespace std;
int n,a[1010000];
int f[1023521];
bool dfs()
{
	int sh=0;
	for(int i=1;i<=n;i++)sh=(sh*31+a[i])%1023521;
	if(f[sh]!=-1)return f[sh];
	for(int i=1;i<=n;i++)
	{
		if(i<=a[i])
		{
			a[i]-=i;
			bool bk=dfs();
			a[i]+=i;
			if(bk==false)return f[sh]=true;
		}
		else if(a[i]>0)
		{
			a[i]--;
			bool bk=dfs();
			a[i]++;
			if(bk==false)return f[sh]=true;
		}
		if(a[i]>0)
		{
			for(int j=1;j<i;j+=2)
			{
				a[i]--;
				a[j]++;a[i-j]++;
				bool bk=dfs();
				a[i]++;
				a[j]--;a[i-j]--;
				if(bk==false)return f[sh]=true;
			}
		}
	}
	return f[sh]=false;
}
int main()
{
	freopen("extension.in","r",stdin);
	freopen("extension.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	bool bk=true;
	for(int i=2;i<=n;i+=2)if(a[i]!=0)bk=false;
	memset(f,-1,sizeof(f));
	if(bk)
	{
		long long s=0;
		for(int i=1;i<=n;i+=2)s+=a[i];
		puts(s%2==1?"tomato fish+1s":"rainy day+1s");
	}
	else puts(dfs()?"tomato fish+1s":"rainy day+1s");
	return 0;
}