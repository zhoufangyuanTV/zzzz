#include<cstdio>
#include<cstring>
#include<list>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
bool b[510000];
int Z[510000];
struct node
{
	int l,r,c,p;
}A[510000],B[510000];
vector<node> V[510000];
inline bool cmp1(const node &x,const node &y){return x.r>y.r;}
struct cmp2
{
	inline bool operator()(const node &x,const node &y)const{return x.l<y.l;}
};
inline bool cmp3(const node &x,const node &y){return x.r<y.r;}
inline bool cmp4(const node &x,const node &y){return x.l<y.l;}
struct cmp5
{
	inline bool operator()(const node &x,const node &y)const{return x.r>y.r;}
};
priority_queue<node,vector<node>,cmp2> Q1;
priority_queue<node,vector<node>,cmp5> Q2[510000];
list<int> L;
int main()
{
	freopen("gym.in","r",stdin);
	freopen("gym.out","w",stdout);
	int n;scanf("%d%*d",&n);
	for(int i=1;i<=n;i++)
	{
		node x;scanf("%d%d%d",&x.l,&x.r,&x.c);
		x.p=i;
		Z[i]=x.c;
		A[i]=B[i]=x;
	}
	sort(Z+1,Z+n+1);
	int k=unique(Z+1,Z+n+1)-Z-1;
	for(int i=1;i<=n;i++)
	{
		A[i].c=B[i].c=lower_bound(Z+1,Z+k+1,A[i].c)-Z;
		V[A[i].c].push_back(A[i]);
	}
	int N=0;
	for(int t=1;t<=k;t++)
	{
		sort(V[t].begin(),V[t].end(),cmp1);
		int j=0;
		for(int i=1000000000;i>=1;i--)
		{
			while(j<V[t].size()&&V[t][j].r==i)
			{
				Q1.push(V[t][j]);
				j++;
			}
			if(Q1.empty())
			{
				if(j<V[t].size())i=V[t][j].r+1;
				else break;
			}
			else
			{
				node x=Q1.top();Q1.pop();
				if(i<x.l)
				{
					puts("-1");
					return 0;
				}
				x.r=i;
				N++;A[N]=B[N]=x;
			}
		}
		if(!Q1.empty())
		{
			puts("-1");
			return 0;
		}
	}
	int j=1,ss=0;
	memset(b,false,sizeof(b));
	sort(A+1,A+n+1,cmp3);
	sort(B+1,B+n+1,cmp4);
	for(int i=1;i<=n;i++)
	{
		if(b[A[i].p]==false)
		{
			ss++;
			while(j<=n&&B[j].l<=A[i].r)
			{
				if(Q2[B[j].c].empty())L.push_back(B[j].c);
				Q2[B[j].c].push(B[j]);
				j++;
			}
			for(auto it=L.begin();it!=L.end();Q2[*it].empty()?it=L.erase(it):it++)
			{
				node x=Q2[*it].top();Q2[*it].pop();
				b[x.p]=true;
			}
		}
	}
	printf("%d\n",ss);
	return 0;
}