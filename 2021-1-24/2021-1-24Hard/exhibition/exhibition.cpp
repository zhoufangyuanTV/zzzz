#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int l[110000],r[110000];
struct node
{
	int l,r;
}a[110000];
inline bool cm(node x,node y){return x.l<y.l;}
struct edge
{
	int x,y,c;
}e[1010000];int elen;
inline bool cmp(edge x,edge y){return x.c<y.c;}
int f[110000];
int findf(int x){return f[x]==x?x:f[x]=findf(f[x]);}
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("exhibition.in","r",stdin);
	freopen("exhibition.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&l[i],&r[i]);
	if(n<=1000)
	{
		elen=0;
		for(int i=1;i<=n;i++)
		{
			f[i]=i;
			for(int j=i+1;j<=n;j++)
			{
				int c=mymin(r[i],r[j])-mymax(l[i],l[j]);
				if(c>0)e[++elen]=(edge){i,j,c};
			}
		}
		sort(e+1,e+elen+1,cmp);
		int cnt=0;
		long long ss=0;
		for(int i=1;i<=elen;i++)
		{
			int fx=findf(e[i].x),fy=findf(e[i].y);
			if(fx!=fy)
			{
				cnt++;
				ss=ss+e[i].c;
				f[fx]=fy;
				if(cnt==n-1)break;
			}
		}
		if(cnt==n-1)printf("%lld\n",ss);
		else puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)a[i].l=l[i],a[i].r=r[i];
	sort(a+1,a+n+1,cm);
	a[0].l=a[0].r=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].l==a[i-1].l||a[i].r<=a[i-1].r)
		{
			puts("-1");
			return 0;
		}
		if(i>1&&a[i-1].r<=a[i].l){puts("-1");return 0;}
	}
	long long ss=0;
	for(int i=1;i<n;i++)
	{
		int l=i+1,r=n;
		while(l<r)
		{
			int mid=(l+r+1)/2;
			if(a[mid].l<a[i].r)l=mid;
			else r=mid-1;
		}
		ss=ss+a[i].r-a[l].l;
	}
	printf("%lld\n",ss);
	return 0;
}