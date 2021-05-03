#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char s[310];
struct node
{
	int x,y,next;
}a[110000];int len,last[310];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int p[310];
vector<int> in[310];
int list[310];
int g[310];
inline int mymax(int x,int y){return x>y?x:y;}
long long f[210000];
int main()
{
	freopen("gametwice.in","r",stdin);
	freopen("gametwice.out","w",stdout);
	int n,m;scanf("%d%d%s",&n,&m,s+1);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);
		p[x]++;
		in[y].push_back(x);
	}
	int head=1,tail=1;
	for(int i=1;i<=n;i++)if(p[i]==0)list[tail++]=i;
	while(head<tail)
	{
		int x=list[head];
		g[x]=0;
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(s[x]==s[y])g[x]=mymax(g[x],g[y]+1);
			else
			{
				if(g[y]==0)g[x]=mymax(g[x],1);
			}
		}
		for(int i=0;i<in[x].size();i++)
		{
			p[in[x][i]]--;
			if(p[in[x][i]]==0)list[tail++]=in[x][i];
		}
		head++;
	}
	memset(f,0,sizeof(f));f[100000]=1;
	for(int i=1;i<=n;i++)
	{
		if(g[i]==0)
		{
			for(int j=100000-n*n;j<=100000+n*n;j++)f[j]=f[j]*2%998244353;
		}
		else
		{
			if(s[i]=='W')
			{
				for(int j=100000+n*n;j>=100000-n*n;j--)f[j]=(f[j]+f[j-g[i]])%998244353;
			}
			else
			{
				for(int j=100000-n*n;j<=100000+n*n;j++)f[j]=(f[j]+f[j+g[i]])%998244353;
			}
		}
	}
	long long ss=0;
	for(int i=100001;i<=100000+n*n;i++)ss=(ss+f[i])%998244353;
	printf("%lld\n",ss);
	return 0;
}
