#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
int lg2[110000];
int st[110000][20];
inline int mymax(int x,int y){return x>y?x:y;}
void yuchuli()
{
	for(int i=1;i<=lg2[100001];i++)
	{
		for(int j=1;j<=100001-(1<<i)+1;j++)
		{
			st[j][i]=mymax(st[j][i-1],st[j+(1<<i-1)][i-1]);
		}
	}
}
inline int llst(int l,int r)
{
	int lr=lg2[r-l+1];
	return mymax(st[l][lr],st[r-(1<<lr)+1][lr]);
}
int n,k,a[110000];
long long b;
vector<int> zxs[110000];
int pre[110000],last[110000];
inline int mymin(int x,int y){return x<y?x:y;}
struct node{int s,p;};
void dfs(vector<node> S,long long ss)
{
	for(node x:S)
	{
		if(x.p==0)break;
		int r=x.s;
		while(k>0&&r>0)
		{
			k--;r--;
			printf("%lld\n",ss);
		}
		if(k==0)exit(0);
	}
	int g=S.begin()->p,l=1,r=100001;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(g<llst(l,mid))r=mid;
		else l=mid+1;
	}
	while(r<=100000)
	{
		int ll=0,rr=zxs[r].size()-1;
		while(ll<rr)
		{
			int mid=(ll+rr)/2;
			if(zxs[r][mid]<=g)ll=mid+1;
			else rr=mid;
		}
		vector<node> U;
		U.clear();
		int j=0,sg=0;
		for(int i=rr;i<zxs[r].size();i++)
		{
			while(j<S.size()&&S[j].p<zxs[r][i])sg+=S[j++].s;
			U.push_back((node){sg,zxs[r][i]});
		}
		dfs(U,(ss*b+r)%998244353);
		l=r+1;r=100001;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(g<llst(l,mid))r=mid;
			else l=mid+1;
		}
	}
}
int main()
{
	freopen("ttds.in","r",stdin);
	freopen("ttds.out","w",stdout);
	scanf("%d%d%lld",&n,&k,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(zxs[a[i]].empty())pre[i]=-1;
		else pre[i]=*zxs[a[i]].rbegin();
		zxs[a[i]].push_back(i);
	}
	lg2[0]=-1;
	for(int i=1;i<=100001;i++)lg2[i]=lg2[i/2]+1;
	for(int i=1;i<=100000;i++)
	{
		if(zxs[i].empty())st[i][0]=-1;
		else st[i][0]=*zxs[i].rbegin();
	}
	st[100001][0]=n+1;
	yuchuli();
	vector<node> G;
	G.push_back((node){1,0});
	dfs(G,0);
	return 0;
}