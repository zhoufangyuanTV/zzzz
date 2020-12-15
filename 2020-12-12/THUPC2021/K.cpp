#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<utility>
using namespace std;
template<typename T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,next,other;
	long long c;
}a[510000];int len,last[160000],g[160000];
inline void ins(int x,int y,long long c)
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
int list[160000],dep[160000];
bool bt()
{
	memset(dep,63,sizeof(dep));
	memset(list,0,sizeof(list));
	list[1]=st;dep[st]=0;
	int head=1,tail=2;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			if(a[k].c>0)
			{
				int y=a[k].y;
				if(dep[x]+1<dep[y])
				{
					dep[y]=dep[x]+1;
					list[tail++]=y;
				}
			}
		}
		head++;
	}
	if(dep[ed]==1061109567)return false;
	else return true;
}
bool b[160000];
inline long long mymin(long long x,long long y){return x<y?x:y;}
long long find(int x,long long f)
{
	if(b[x]==false)return 0;
	if(x==ed)return f;
	long long used=0;
	int k=g[x];
	do
	{
		int y=a[k].y;
		if(a[k].c>0&&dep[x]+1==dep[y]&&used<f)
		{
			int tt=find(y,mymin(a[k].c,f-used));
			used+=tt;
			a[k].c-=tt;
			if(used==f)break;
		}
		k=a[k].next;
		if(k==0)k=last[x];
	}while(k!=g[x]);
	g[x]=k;
	if(used==0)b[x]=false;
	return used;
}
const long long q=101,B=137,p=1000000007;
long long A[110000];
long long x[110000],y[110000],z[110000];
set<pair<int,int>> S;
int main()
{
	int n,m;
	long long ss=0;
	read(n);read(m);read(x[0]);read(y[0]);read(A[0]);read(z[0]);
	for(int i=1;i<=n;i++)
	{
		A[i]=(A[i-1]*q+B)%p;
		ss=ss+A[i];
	}
	for(int i=1;i<=m;i++)
	{
		x[i]=(x[i-1]*q+B)%p;
		y[i]=(y[i-1]*q+B)%p;
		z[i]=(z[i-1]*q+B)%p;
	}
	int M=m;
	for(int i=1,r=1;i<=m;i++,r++)
	{
		x[i]=x[i]%n+1;
		y[i]=y[i]%n+1;
		if(x[i]==y[i])M--,r--;
		else if(S.find({x[i],y[i]})==S.end())
		{
			S.insert({x[i],y[i]});
			x[r]=x[i];y[r]=y[i];z[r]=z[i];
		}
		else M--,r--;
	}
	m=M;
	len=0;memset(last,0,sizeof(last));
	st=n+m+1;ed=n+m+2;
	for(int i=1;i<=n;i++)ins(st,i,A[i]);
	for(int i=1;i<=m;i++)
	{
		ins(x[i],n+i,0x3f3f3f3f3f3f3f3fll);
		ins(y[i],n+i,0x3f3f3f3f3f3f3f3fll);
		ins(n+i,ed,z[i]);
	}
    for(int i=1;i<=ed;i++)g[i]=last[i];
	while(bt()==true)
	{
		memset(b,true,sizeof(b));
		ss=ss-find(st,4557430888798830399ll);
	}
	printf("%lld\n",ss);
	return 0;
}