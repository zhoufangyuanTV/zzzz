#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
char s[510000];
int cnt[510000][26];
vector<int> d[510000];
long long hashs[510000];
long long base29[510000];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
	int n,m;scanf("%d%s%d",&n,s+1,&m);
	base29[0]=1;base29[1]=29;
	for(int i=2;i<=n;i++)
	{
		base29[i]=base29[i-1]*29%1000000007;
		if(d[i].size()==0)for(int j=i;j<=n;j+=i)d[j].push_back(i);
	}
	memset(cnt[0],0,sizeof(cnt[0]));
	hashs[0]=0;
	for(int i=1;i<=n;i++)
	{
		hashs[i]=(hashs[i-1]*29+s[i]-'a')%1000000007;
		for(int j=0;j<26;j++)cnt[i][j]=cnt[i-1][j];
		cnt[i][s[i]-'a']++;
	}
	for(int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		if(r==n+1){printf("%d\n",r-l+1);continue;}
		int g=r-l+1;
		for(int j=0;j<26;j++)g=gcd(g,cnt[r][j]-cnt[l-1][j]);
		int ss=1;
		for(int j:d[g])
		{
			long long jj;
			for(jj=j;(r-l+1)%jj==0;jj*=j)
			{
				int k=(r-l+1)/jj;
				if((hashs[r-k]-hashs[l-1]*base29[r-k-l+1]%1000000007+1000000007)%1000000007!=(hashs[r]-hashs[l+k-1]*base29[r-k-l+1]%1000000007+1000000007)%1000000007)break;
			}
			ss=ss*(jj/j);
		}
		printf("%d\n",(r-l+1)/ss);
	}
	return 0;
}