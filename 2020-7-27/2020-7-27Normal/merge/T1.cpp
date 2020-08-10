#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct node
{
	int x,y,next;
}a[110000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,fa[110000],f[5100][5100];
struct tie
{
	int k,c;
};vector<tie> t[110000];
inline int mymin(int x,int y){return x<y?x:y;}
void treedp(int x)
{
	if(x!=1)
	{
		f[x][0]=0x3f3f3f3f;
		for(tie ti:t[x])
		{
			f[x][0]=mymin(f[x][0],f[fa[x]][ti.k-1]+ti.c);
		}
		for(int k=1;k<=n;k++)
		{
			f[x][k]=mymin(f[x][0],f[fa[x]][k-1]);
		}
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])treedp(y);
	}
}
int main()
{
	int m;scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(y,x);fa[x]=y;
	}
	for(int i=1;i<=m;i++)
	{
		int v,k,c;scanf("%d%d%d",&v,&k,&c);
		t[v].push_back((tie){k,c});
	}
	for(int i=0;i<=n;i++)f[1][i]=0;
	treedp(1);
	int tt;scanf("%d",&tt);
	while(tt--)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",f[x][0]);
	}
	return 0;
}
