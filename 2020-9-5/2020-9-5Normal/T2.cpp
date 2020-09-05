#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int lowbit(int x){return x&-x;}
int n,c[51000];
inline int mymax(int x,int y){return x>y?x:y;}
void change(int x,int s)
{
	while(x<=n)
	{
		c[x]=mymax(c[x],s);
		x=x+lowbit(x);
	}
}
int ans(int x)
{
	int s=0;
	while(x>0)
	{
		s=mymax(s,c[x]);
		x=x-lowbit(x);
	}
	return s;
}
struct Query{int l,r,p;}Q[51000];
inline bool cmp(Query x,Query y){return x.l>y.l;}
int Ans[51000];
int a[51000];
int sta[51000],tap,sti[51000],tip;
int main()
{
	int m;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].p=i;
	sort(Q+1,Q+m+1,cmp);
	for(int i=1;i<=n;i++)c[i]=1;
	sta[1]=sti[1]=n;tap=tip=1;
	int j=1;
	while(j<=n&&Q[j].l==n)
	{
		Ans[Q[j].p]=ans(Q[j].r);
		j++;
	}
	for(int i=n-1;i>=1;i--)
	{
		while(tap>0&&a[i]>a[sta[tap]])tap--;
		while(tip>0&&a[i]<a[sti[tip]])tip--;
		int ap=tap,ip=tip;
		while(ap>0&&a[i]>=a[sta[ap]])ap--;
		while(ip>0&&a[i]<=a[sti[ip]])ip--;
		for(int k=tap;k>=1;k--)if(ip>0&&sta[k]>sti[ip])break;else change(sta[k],sta[k]-i+1);
		for(int k=tip;k>=1;k--)if(ap>0&&sti[k]>sta[ap])break;else change(sti[k],sti[k]-i+1);
		sta[++tap]=sti[++tip]=i;
		while(j<=n&&Q[j].l==i)
		{
			Ans[Q[j].p]=ans(Q[j].r);
			j++;
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}