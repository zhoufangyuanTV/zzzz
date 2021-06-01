#include<cstdio>
#include<cstring>
using namespace std;
int a[110],n;
int A,B,C,D,s;
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x,int k)
{
	if(C<=x&&x<=D){s=mymin(s,k);return ;}
	int i;
	for(i=x-1;i>=0;i--)if(a[x]<a[i])break;
	if(i>=0)dfs(i,k+1);
	for(i=x+1;i<n;i++)if(a[x]<a[i])break;
	if(i<n)dfs(i,k+1);
}
int main()
{
	freopen("jumps.in","r",stdin);
	freopen("jumps.ans","w",stdout);
	int m;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&A,&B,&C,&D);
		s=0x3f3f3f3f;
		for(int j=A;j<=B;j++)dfs(j,0);
		if(s==0x3f3f3f3f)puts("-1");
		else printf("%d\n",s);
	}
	return 0;
}
