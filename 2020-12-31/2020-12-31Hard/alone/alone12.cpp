#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();};
}
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool mp[2100][2100];
int ss=0,Ans[1010000];
int p[1010000];
void dfs(int k)
{
	if(k-1>ss)
	{
		ss=k-1;
		for(int i=1;i<k;i++)Ans[i]=p[i];
	}
	for(int kk=last[p[k-1]];kk>0;kk=a[kk].next)
	{
		int y=a[kk].y;
		bool bk=true;
		for(int i=1;i<k;i++)if(mp[p[i]][y]){bk=false;break;}
		if(bk)
		{
			p[k]=y;
			dfs(k+1);
			p[k]=0;
		}
	}
}
int main(int argc,char* argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	int n,m;read(n);read(n);read(m);
	len=0;memset(last,0,sizeof(last));
	memset(mp,true,sizeof(mp));
	for(int i=1;i<=m;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
		mp[x][y]=mp[y][x]=false;
	}
	for(int i=1;i<=n;i++)
	{
		p[1]=i;
		dfs(2);
	}
	printf("%d\n",ss);
	for(int i=1;i<=ss;i++)printf("%d\n",Ans[i]);
	return 0;
}