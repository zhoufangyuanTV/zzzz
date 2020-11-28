#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,c,next,other;
}a[5010000];int len,last[5010000];
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
int st,ed,pts;
int dep[5010000];
int list[5010000];
bool build()
{
	for(int i=1;i<=pts;i++)dep[i]=-1;
	dep[st]=1;
	int head=1,tail=2;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(a[k].c>0&&dep[y]==-1)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed]!=-1;
}
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==ed)return f;
	int used=0;
	for(int k=last[x];k>0;k=a[k].next)
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
int ted[1010000];
int Ans0[5010000],Ans1[5010000];
int main()
{
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	int n,m;read(n);read(m);
	if(m>=500000)
	{
		puts("NO");
		return 0;
	}
	len=0;memset(last,0,sizeof(last));
	st=1;pts=1;
	for(int i=1;i<=n;i++)
	{
		ted[i]=++pts;
		ins(st,ted[i],1);
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;read(x);read(y);
		ins(ted[x],ted[y],1);
		int mid=++pts;
		ins(ted[y],mid,1);
		Ans0[i]=len+1;
		ted[x]=++pts;
		ins(mid,ted[x],1);
		Ans1[i]=len+1;
		ted[y]=++pts;
		ins(mid,ted[y],1);
	}
	ed=++pts;
	for(int i=1;i<=n;i++)ins(ted[i],ed,1);
	int ss=0;
	while(build())ss+=find(st,0x3f3f3f3f);
	if(ss>=(n+1)/2)
	{
		puts("YES");
		for(int i=1;i<=m;i++)
		{
			if(a[Ans0[i]].c==0)putchar('0');
			else putchar('1');
		}
		putchar('\n');
	}
	else puts("NO");
	return 0;
}