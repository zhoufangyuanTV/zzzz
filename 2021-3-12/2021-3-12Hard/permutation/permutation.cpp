#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next,other;
}a[11000];int len,last[1100];
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
int S,T;
int dep[1100];
int list[1100];
bool build()
{
	memset(dep,63,sizeof(dep));dep[S]=1;
	int head=1,tail=2;list[1]=S;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(a[k].c>0&&dep[x]+1<dep[y])
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[T]!=0x3f3f3f3f;
}
bool b[1100];
int cur[1100];
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==T)return f;
	if(b[x]==false)return 0;
	int used=0;
	for(int &k=cur[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(a[k].c>0&&dep[y]==dep[x]+1&&used<f)
		{
			int tt=find(y,mymin(a[k].c,f-used));
			used+=tt;
			a[k].c-=tt;
			a[a[k].other].c+=tt;
			if(used==f)break;
		}
	}
	return used;
}
int main()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	S=2*n+1;T=2*n+2;
	int ss=0;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		if(x<0)ins(i,n+i,-x);
		else ss+=x,ins(S,i,x),ins(n+i,T,x);
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y,0x3f3f3f3f);ins(n+x,n+y,0x3f3f3f3f);
	}
	while(build())
	{
		memset(b,true,sizeof(b));
		for(int i=1;i<=2*n+2;i++)cur[i]=last[i];
		ss-=find(S,0x3f3f3f3f);
	}
	printf("%d\n",ss);
	return 0;
}