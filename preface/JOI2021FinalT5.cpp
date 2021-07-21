#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Query{int x,U,p;}Q[410000];
inline bool cmp(Query x,Query y){return x.x>y.x;}
long long Ans[410000];
long long a[210000],sa[210000],b[210000];
int lg2[210000];
int st[210000][18],ts[210000][18];
inline int mymin(int x,int y){return b[x]<b[y]?x:y;}
inline int mymax(int x,int y){return a[x]>a[y]?x:y;}
inline int findmin(int l,int r)
{
	int lr=lg2[r-l+1];
	return mymin(st[l][lr],st[r-(1<<lr)+1][lr]);
}
inline int findmax(int l,int r)
{
	int lr=lg2[r-l+1];
	return mymax(ts[l][lr],ts[r-(1<<lr)+1][lr]);
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	sa[1]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sa[i+1]=sa[i]+a[i];
	}
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	lg2[0]=-1;
	for(int i=1;i<=n;i++)lg2[i]=lg2[i/2]+1;
	for(int i=1;i<=n;i++)st[i][0]=ts[i][0]=i;
	for(int j=1;j<=lg2[n];j++)
	{
		for(int i=1;i<=n-(1<<j)+1;i++)
		{
			st[i][j]=mymin(st[i][j-1],st[i+(1<<j-1)][j-1]);
			ts[i][j]=mymax(ts[i][j-1],ts[i+(1<<j-1)][j-1]);
		}
	}
	int M=0;
	for(int i=1;i<=m;i++)
	{
		int x,y,U;scanf("%d%d%d",&x,&y,&U);
		if(U<a[findmax(x,y-1)])
		{
			Ans[i]=-1;
			continue;
		}
		int l=x,r=y-1;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(sa[y]-sa[mid]<=U)r=mid;
			else l=mid+1;
		}
		int mi=findmin(r,y-1);
		Ans[i]=b[mi]*(sa[y]-sa[mi]);
		Q[++M]=(Query){x,U,i};
		Q[++M]=(Query){mi,U,-i};
	}
	sort(Q+1,Q+M+1,cmp);
	return 0;
}