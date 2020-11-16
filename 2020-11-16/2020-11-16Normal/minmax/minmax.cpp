#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long ss=0;int k;
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
void dfs(int x,int fa,int minn,int maxx)
{
	if(maxx-minn>k)return ;
	if(maxx-minn==k)ss++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			int mi=mymin(minn,a[k].c),ma=mymax(maxx,a[k].c);
			dfs(y,x,mi,ma);
		}
	}
}
int tong[210000],p[210000];
int main()
{
	freopen("minmax.in","r",stdin);
	freopen("minmax.out","w",stdout);
	int n;scanf("%d%d",&n,&k);
	len=0;memset(last,0,sizeof(last));
	memset(p,0,sizeof(p));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
		p[x]++;p[y]++;
	}
	int bk=0;
	for(int i=1;i<=n;i++)if(p[i]>1)bk++;
	if(bk==1)
	{
		for(int i=1;i<n;i++)
		{
			int c=a[2*i-1].c;
			if(k-c>=0)ss=ss+tong[k-c];
			tong[c]++;
		}
		printf("%lld\n",ss);
		return 0;
	}
	for(int i=1;i<=n;i++)dfs(i,0,n+1,0);
	printf("%lld\n",ss/2);
	return 0;
}