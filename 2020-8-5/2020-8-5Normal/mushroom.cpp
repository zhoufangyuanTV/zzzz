#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
struct node
{
	int x,y,next;
}a[610000];int len,last[310000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int son[310000],tot[310000];
void dfs(int x,int fa)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
long long f[310000];
int c[310000];
map<int,int>& dsu(int x,int fa)
{
	if(son[x]==0)
	{
		f[x]=1;map<int,int> *p=new map<int,int>;
		(*p)[c[x]]=1;
		return *p;
	}
	f[x]=0;map<int,int> &M=dsu(son[x],x);
	f[x]+=f[son[x]];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&y!=son[x])
		{
			map<int,int> &MM=dsu(y,x);
			for(map<int,int>::iterator it=MM.begin();it!=MM.end();it++)
			{
				M[(*it).first]=M[(*it).first]+(*it).second;
			}
			delete &MM;
			f[x]+=f[y];
		}
	}
	f[x]+=tot[x]-M[c[x]];
	M[c[x]]=tot[x];
	return M;
}
int main()
{
	freopen("mushroom.in","r",stdin);
	freopen("mushroom.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(i,0);
		dsu(i,0);
		printf("%lld\n",f[i]);
	}
	return 0;
}