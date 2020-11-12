#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int> g[110000],gg[110000];
int in[110000],out[110000];
long long p[110000],v[110000];
long long cc[110000];
int f[110000];
long long fr[110000],ag[110000];
long long A[110000];
int list[110000];
int main()
{
	freopen("call.in","r",stdin);
	freopen("call.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
	int m;scanf("%d",&m);
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	for(int i=1;i<=m;i++)
	{
		int t;scanf("%d",&t);
		if(t==1)
		{
			scanf("%lld%lld",&p[i],&v[i]);
		}
		else if(t==2)
		{
			p[i]=-1;
			scanf("%lld",&v[i]);
		}
		else
		{
			p[i]=-52;
			int c;scanf("%d",&c);
			for(int j=1;j<=c;j++)
			{
				int y;scanf("%d",&y);
				g[i].push_back(y);
				gg[y].push_back(i);
				out[i]++;in[y]++;
			}
		}
	}
	int head=1,tail=1;
	for(int i=1;i<=m;i++)
	{
		cc[i]=1;
		if(p[i]==-1)cc[i]=v[i];
		if(out[i]==0)list[tail++]=i;
	}
	while(head<tail)
	{
		int x=list[head];
		int siz=gg[x].size();
		for(int i=0;i<siz;i++)
		{
			int y=gg[x][i];
			cc[y]=cc[y]*cc[x]%998244353;
			out[y]--;
			if(out[y]==0)list[tail++]=y;
		}
		head++;
	}
	int q;scanf("%d",&q);
	for(int i=1;i<=q;i++)scanf("%d",&f[i]);
	long long ss=1;
	memset(fr,0,sizeof(fr));
	for(int i=q;i>=1;i--)
	{
		fr[f[i]]=(fr[f[i]]+ss)%998244353;
		ss=ss*cc[f[i]]%998244353;
	}
	memset(ag,0,sizeof(ag));
	head=1;tail=1;
	for(int i=1;i<=m;i++)
	{
		if(in[i]==0)list[tail++]=i;
	}
	while(head<tail)
	{
		int x=list[head];
		if(p[x]!=-1&&p[x]!=-52)
		{
			ag[p[x]]=(ag[p[x]]+v[x]*fr[x])%998244353;
		}
		int siz=g[x].size();
		long long s=fr[x];
		for(int i=siz-1;i>=0;i--)
		{
			int y=g[x][i];
			fr[y]=(fr[y]+s)%998244353;
			s=s*cc[y]%998244353;
			in[y]--;
			if(in[y]==0)list[tail++]=y;
		}
		head++;
	}
	for(int i=1;i<n;i++)
	{
		printf("%lld ",(A[i]*ss+ag[i])%998244353);
	}
	if(n>0)printf("%lld\n",(A[n]*ss+ag[n])%998244353);
	return 0;
}
