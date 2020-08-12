#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int c[110000];
long long ANDS,ORS,XORS;
void dfs(int x,int fa,int AND,int OR,int XOR)
{
	AND&=c[x];OR|=c[x];XOR^=c[x];
	ANDS+=AND;ORS+=OR;XORS+=XOR;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,AND,OR,XOR);
	}
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&c[i]);
		len=0;memset(last,0,sizeof(last));
		for(int i=1;i<n;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			ins(x,y);ins(y,x);
		}
		ANDS=0;ORS=0;XORS=0;
		for(int i=1;i<=n;i++)dfs(i,0,(1<<20)-1,0,0);
		printf("%.3lf %.3lf %.3lf\n",(double)ANDS/n/n,(double)ORS/n/n,(double)XORS/n/n);
	}
	return 0;
}