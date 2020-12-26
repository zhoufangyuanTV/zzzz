#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int A[210000];
double f[210000];
bool bk;
double Lambda;
void dfs(int x,int fa)
{
	f[x]=A[x]*Lambda;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			double wy=a[k].c/(2*f[y]);
			f[x]=f[x]+f[y]*wy*wy-a[k].c*wy;
		}
	}
	if(f[x]<0)bk=false;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	double l=0,r=100*n;
	while(r-l>1e-6)
	{
		double mid=(l+r)/2;
		bk=true;
		Lambda=mid;
		dfs(1,0);
		if(bk)r=mid;
		else l=mid;
	}
	printf("%.6lf\n",l);
	return 0;
}