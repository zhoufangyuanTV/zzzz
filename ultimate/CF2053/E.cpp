#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int dep[210000],si[210000];
void dfs1(int x,int fa)
{
	dep[x]=si[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs1(y,x);
			if(dep[x]==0||dep[y]+1<dep[x])dep[x]=dep[y]+1;
			si[x]+=si[y];
		}
	}
	if(dep[x]>1)si[x]++;
}
int rt;long long ss;
void dfs2(int x,int fa)
{
	if(dep[x]==0)return ;
	if(dep[fa]==1)ss+=si[rt]-si[x];
	if(fa!=0&&dep[x]==1)ss+=si[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs2(y,x);
	}
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		len=0;
		for(int i=1;i<=n;i++)last[i]=0;
		for(int i=1;i<n;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			ins(x,y);ins(y,x);
		}
		if(n==2){puts("0");continue;}
		int s=0;
		for(int i=1;i<=n;i++)
		{
			if(a[last[i]].next!=0)rt=i;
			else s++;
		}
		dfs1(rt,0);
		ss=(long long)s*(n-s);
		dfs2(rt,0);
		printf("%lld\n",ss);
	}
	return 0;
}