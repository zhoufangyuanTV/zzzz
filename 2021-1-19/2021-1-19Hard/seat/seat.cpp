#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
long long a[110000];
struct Query{long long x;int p;}Q[110000];
long long Ans[110000];
inline bool cmp(Query x,Query y){return x.x<y.x;}
struct range{long long l,r;};
inline bool operator<(range x,range y){return x.r-x.l==y.r-y.l?x.l>y.l:x.r-x.l<y.r-y.l;}
priority_queue<range> PQ;
int main()
{
	//freopen("seat.in","r",stdin);
	//freopen("seat.out","w",stdout);
	long long m;int n,q;scanf("%lld%d%d",&m,&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=q;i++)scanf("%lld",&Q[i].x);
	int qq=q;q=0;
	for(int i=1;i<=qq;i++)
	{
		if(Q[i].x<=n)Ans[i]=a[Q[i].x];
		else Q[++q]=(Query){Q[i].x,i};
	}
	sort(a+1,a+n+1);
	sort(Q+1,Q+q+1,cmp);
	if(Q[q].x<=1000000)
	{
		a[0]=0;a[n+1]=m+1;
		for(int i=0;i<=n;i++)
		{
			if(a[i+1]-a[i]>1)PQ.push((range){a[i]+1,a[i+1]-1});
		}
		int j=n;long long mid=0;
		for(int i=1;i<=q;i++)
		{
			while(j<Q[i].x)
			{
				j++;
				range x=PQ.top();PQ.pop();
				mid=(x.l+x.r)/2;
				if(x.l<mid)PQ.push((range){x.l,mid-1});
				if(mid<x.r)PQ.push((range){mid+1,x.r});
			}
			Ans[Q[i].p]=mid;
		}
	}
	else
	{
		a[0]=0;a[n+1]=m+1;
		long long k=n;int l=1;
		for(long long i=140737488355328ll;i>1;i>>=1)
		{
			for(int j=0;j<=n;j++)
			{
				if(i<=a[j+1]-a[j])
				{
					long long kk=k+(a[j+1]-a[j])/i;
					while(l<=q&&Q[l].x<=kk)
					{
						Ans[Q[l].p]=a[j]+i/2+(Q[l].x-k-1)*i;
						l++;
					}
				}
			}
		}
	}
	for(int i=1;i<=qq;i++)printf("%lld\n",Ans[i]);
	return 0;
}