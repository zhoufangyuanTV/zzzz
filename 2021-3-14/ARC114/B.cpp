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
bool b[210000];
void dfs(int x)
{
	b[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y]==false)dfs(y);
	}
}
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
int main()
{
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		ins(i,x);ins(x,i);
	}
	memset(b,false,sizeof(b));
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		if(b[i]==false){dfs(i);ss++;}
	}
	printf("%lld\n",(ksm(2,ss)+998244352)%998244353);
	return 0;
}