#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct node
{
	long long x,y;
	int p;
}a[310000];
struct cmp
{
	inline bool operator()(node x,node y){return x.y*y.x<y.y*x.x;}
};
priority_queue<node,vector<node>,cmp> Q;
int f[310000],fa[310000];
inline int find(int x){return f[x]!=x?find(f[x]):x;}
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=2;i<=n;i++)scanf("%d",&fa[i]);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i].x,&a[i].y);
		a[i].p=i;
		Q.push(a[i]);
	}
	long long ss=0;
	while(!Q.empty())
	{
		int x=Q.top().p;Q.pop();
		if(x==1||f[x]!=x)continue;
		int ff=find(fa[x]);
		f[x]=ff;
		ss=ss+a[ff].y*a[x].x;
		a[ff].x=a[ff].x+a[x].x;
		a[ff].y=a[ff].y+a[x].y;
		Q.push(a[ff]);
	}
	printf("%lld\n",ss);
	return 0;
}