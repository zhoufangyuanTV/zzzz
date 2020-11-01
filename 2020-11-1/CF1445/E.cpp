#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<set>
#include<vector>
#include<utility>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,next;
	bool br;
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
	a[len].br=true;
}
int bb=0,bol[510000];
int tt[510000];
int col[510000];
bool dfs(int x,int c,int bbc)
{
	bol[x]=bbc;
	if(col[x]!=-1)
	{
		if(col[x]==c)return true;
		else return false;
	}
	col[x]=c;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(tt[x]!=tt[y])continue;
		bool bk=dfs(y,1-c,bbc);
		if(bk==false)return false;
	}
	return true;
}
vector<int> tim[510000];
map<pair<int,int>,int> M;
set<pair<int,int>> S;
bool bbb[510000];
int cg[510000];
int Ap,Be,CC;
bool brh;
void colorr(int x,int cc)
{
	if(cg[x]==CC||cg[x]==CC+1)
	{
		if(cg[x]==cc)return ;
		else
		{
			brh=false;
			return ;
		}
	}
	cg[x]=cc;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(tt[y]!=Ap&&tt[y]!=Be)continue;
		if(a[k].br==false&&cg[y]!=CC&&cg[y]!=CC+1)
		{
			printf("%d\n",k);
			exit(0);
		}
		a[k].br=false;
		if(k%2==1)a[k+1].br=false;
		else a[k-1].br=false;
		colorr(y,cc^1);
	}
}
int main()
{
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&tt[i]);
		tim[tt[i]].push_back(i);
	}
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	memset(col,-1,sizeof(col));
	memset(bbb,true,sizeof(bbb));
	for(int i=1;i<=n;i++)
	{
		if(col[i]!=-1)continue;
		bool bk=dfs(i,0,++bb);
		if(bk==false)
		{
			if(bbb[tt[i]]==true)k--;
			bbb[tt[i]]=false;
		}
	}
	CC=0;
	for(int i=1;i<=m*2;i+=2)
	{
		int x=a[i].x,y=a[i].y;
		if(a[i].br&&tt[x]!=tt[y]&&bbb[tt[x]]&&bbb[tt[y]])
		{
			CC+=2;brh=true;Ap=tt[x];Be=tt[y];
			colorr(x,CC);
			if(brh==false)S.insert({tt[x],tt[y]});
		}
	}
	printf("%lld\n",1ll*k*(k-1)/2-S.size());
	return 0;
}