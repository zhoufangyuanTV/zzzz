#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c,next,other;
}a[202001];int len,last[51003];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[len-1].other=len;
	a[len].other=len-1;
}
int st,ed;
int dep[51003];
int list[51003];
bool pand()
{
	memset(dep,-1,sizeof(dep));
	int head=1,tail=2;
	dep[st]=1;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(dep[y]==-1&&a[k].c>0)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed]!=-1;
}
bool b[51003];
int cur[51003];
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==ed)return f;
	if(b[x]==false)return 0;
	int used=0;
	for(int &k=cur[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(dep[y]==dep[x]+1&&a[k].c>0&&used<f)
		{
			int tt=find(y,mymin(f-used,a[k].c));
			used+=tt;
			a[k].c-=tt;
			a[a[k].other].c+=tt;
			if(used==f)break;
		}
	}
	if(used==0)b[x]=false;
	return used;
}
vector<int> E[1001];
int A[1001],B[1001];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)scanf("%d",&B[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		E[x].push_back(y);
	}
	for(int i=1;i<=n;i++)sort(E[i].begin(),E[i].end(),[](int x,int y){return A[x]<A[y];});
	len=0;memset(last,0,sizeof(last));
	st=m+n+1;ed=m+n+2;
	for(int i=1;i<=n;i++)ins(st,i,B[i]);
	int Elen=0;
	for(int i=1;i<=n;i++)
	{
		int k=0;
		for(int j:E[i])
		{
			Elen++;
			ins(j,n+Elen,0x3f3f3f3f);
			if(k>0)ins(n+Elen-1,n+Elen,A[k]);
			k=j;
		}
		if(k>0)ins(n+Elen,ed,A[k]);
	}
	int ss=0;
	while(pand())
	{
		memset(b,true,sizeof(b));
		for(int i=1;i<=ed;i++)cur[i]=last[i];
		ss+=find(st,0x3f3f3f3f);
	}
	printf("%d\n",ss);
	return 0;
}