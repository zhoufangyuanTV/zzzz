#include<cstdio>
#include<cstring>
using namespace std;
struct node{int r1,c1,r2,c2;}Q[510000];
inline bool cmp1(node x,node y){return x.r1<y.r1;}
inline bool cmp2(node x,node y){return x.c1<y.c1;}
int main()
{
	freopen("roche.in","r",stdin);
	freopen("roche.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m,q;scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=q;i++)scanf("%d%d%d%d",&Q[i].r1,&Q[i].c1,&Q[i].r2,&Q[i].c2);
	}
	return 0;
}