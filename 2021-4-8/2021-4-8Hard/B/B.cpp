#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,w;
}a[110000],b[110000];
inline bool operator<(node x,node y){return x.x<y.x;}
int Y[210000];
struct Query{int l,r,p;};
int Ans[510000];
vector<Query> aQ[110000],Qb[110000];
int block,blk[110000];
inline bool cmp1(Query x,Query y){return x.r<y.r;}
inline bool cmp2(Query x,Query y){return x.r>y.r;}
int N,c[210000];
inline int lowbit(int x){return x&-x;}
inline int mymax(int x,int y){return x>y?x:y;}
inline void change(int x,int s)
{
	while(x<=N)
	{
		if(c[x]<s)c[x]=s;
		else break;
		x+=lowbit(x);
	}
}
inline int findmax(int x)
{
	int s=0xc0c0c0c0;
	while(x>0)
	{
		s=mymax(s,c[x]);
		x-=lowbit(x);
	}
	return s;
}
int cc[210000];
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	int n,q;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
		a[i].x=-a[i].x;
		Y[i]=a[i].y;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].w);
		Y[n+i]=b[i].y;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	sort(Y+1,Y+n*2+1);
	for(int i=1;i<=n;i++)a[i].y=lower_bound(Y+1,Y+n*2+1,a[i].y)-Y;
	for(int i=1;i<=n;i++)b[i].y=lower_bound(Y+1,Y+n*2+1,b[i].y)-Y;
	scanf("%d",&q);
	block=ceil(n/sqrt(0.7*q));
	if(block==0)block=1;
	for(int i=1;i<=n;i++)blk[i]=(i-1)/block+1;
	for(int i=1;i<=q;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		l=lower_bound(a+1,a+n+1,(node){-l,0,0})-a;
		r=lower_bound(b+1,b+n+1,(node){r,0,0})-b;
		if(l<=n&&r<=n)aQ[blk[l]].push_back((Query){l,r,i});
		l--;r--;
		if(l>0&&r>0)Qb[blk[l]].push_back((Query){l,r,i});
	}
	memset(Ans,-1,sizeof(Ans));
	N=n*2;
	memset(cc,-64,sizeof(cc));
	int l=n;
	for(int i=blk[n];i>=1;i--)
	{
		if(aQ[i].size()>0)
		{
			for(int j=2;j<=n*2;j++)cc[j]=mymax(cc[j],cc[j-1]);
			sort(aQ[i].begin(),aQ[i].end(),cmp2);
			memset(c,-64,(n*2+1)*4);
			int r=n,s=0xc0c0c0c0;
			for(int j=0;j<aQ[i].size();j++)
			{
				while(r>0&&aQ[i][j].r<=r)
				{
					s=mymax(s,b[r].w+cc[b[r].y]);
					change(n*2-b[r].y+1,b[r].w);
					r--;
				}
				int sss=s;
				for(int k=aQ[i][j].l;k<=l;k++)sss=mymax(sss,findmax(n*2-a[k].y+1)+a[k].w);
				Ans[aQ[i][j].p]=mymax(Ans[aQ[i][j].p],sss);
			}
		}
		while(l>0&&blk[l]==i)
		{
			cc[a[l].y]=a[l].w;
			l--;
		}
	}
	memset(cc,-64,sizeof(cc));
	l=1;
	for(int i=1;i<=blk[n];i++)
	{
		if(Qb[i].size()>0)
		{
			for(int j=2;j<=n*2;j++)cc[j]=mymax(cc[j],cc[j-1]);
			sort(Qb[i].begin(),Qb[i].end(),cmp1);
			memset(c,-64,(n*2+1)*4);
			int r=1,s=0xc0c0c0c0;
			for(int j=0;j<Qb[i].size();j++)
			{
				while(r<=n&&r<=Qb[i][j].r)
				{
					s=mymax(s,b[r].w+cc[b[r].y]);
					change(n*2-b[r].y+1,b[r].w);
					r++;
				}
				int sss=s;
				for(int k=l;k<=Qb[i][j].l;k++)sss=mymax(sss,findmax(n*2-a[k].y+1)+a[k].w);
				Ans[Qb[i][j].p]=mymax(Ans[Qb[i][j].p],sss);
			}
		}
		while(l<=n&&blk[l]==i)
		{
			cc[a[l].y]=a[l].w;
			l++;
		}
	}
	for(int i=1;i<=q;i++)printf("%d\n",Ans[i]);
	return 0;
}
