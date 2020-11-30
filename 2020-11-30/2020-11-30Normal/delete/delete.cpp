#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
	int x,y;
}e[110000];
long long c[110000];
inline bool cmp(edge x,edge y){return c[x.x]<c[y.x];}
int f[110000];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int main()
{
	freopen("delete.in","r",stdin);
	freopen("delete.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&e[i].x,&e[i].y);
		if(c[e[i].x]<c[e[i].y])e[i].x^=e[i].y^=e[i].x^=e[i].y;
	}
	sort(e+1,e+n,cmp);
	long long ss=0;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<n;i++)
	{
		int fy=find(e[i].y);
		ss=ss+c[e[i].x]+c[fy];
		f[fy]=e[i].x;
	}
	printf("%lld\n",ss);
	return 0;
}
