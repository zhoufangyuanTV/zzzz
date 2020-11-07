#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct Query{int l,r,p;};
int Ans[110000];
struct node
{
	int l,r,lc,rc;
	vector<Query> q;
}tr[210000];int len;
void bt(int l,int r)
{
	len++;int now=len;
}
inline int lowbit(int x){return x&-x;}
int a[110000];
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	return 0;
}
