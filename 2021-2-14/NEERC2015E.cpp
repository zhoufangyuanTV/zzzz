#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
struct Query{int x,y;}Q[110000];
int Ans[110000];
inline int mymin(int x,int y){return x<y?x:y;}
struct edge{int x,y;};
struct node
{
	int x,y,next;
}a[210000];int len,last[51000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int d[51000];
queue<int> Que;
inline int mymax(int x,int y){return x>y?x:y;}
int id[51000];
void solve(vector<int> &V,vector<edge> &E,vector<int> &q)
{
	int n=V.size();
	if(n==3)
	{
		for(int i:q)Ans[i]=1;
		return ;
	}
	int f=0x3f3f3f3f;edge ce;
	for(edge e:E)
	{
		auto xt=lower_bound(V.begin(),V.end(),e.x),yt=lower_bound(V.begin(),V.end(),e.y);
		int F=yt-xt;
		F=mymax(F,n-F);
		if(F<f)f=F,ce=e;
	}
	len=0;
	for(int i:V)last[i]=0;
	for(edge e:E)
	{
		ins(e.x,e.y);ins(e.y,e.x);
	}
	for(int i:V)d[i]=0x3f3f3f3f;
	d[ce.x]=0;Que.push(ce.x);
	while(!Que.empty())
	{
		int x=Que.front();Que.pop();
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(d[y]==0x3f3f3f3f)d[y]=d[x]+1,Que.push(y);
		}
	}
	for(int i:q)Ans[i]=mymin(Ans[i],d[Q[i].x]+d[Q[i].y]);
	for(int i:V)d[i]=0x3f3f3f3f;
	d[ce.y]=0;Que.push(ce.y);
	while(!Que.empty())
	{
		int x=Que.front();Que.pop();
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(d[y]==0x3f3f3f3f)d[y]=d[x]+1,Que.push(y);
		}
	}
	for(int i:q)Ans[i]=mymin(Ans[i],d[Q[i].x]+d[Q[i].y]);
	vector<int> vv,QQ;
	vector<edge> ee;
	for(int i:V)
	{
		id[i]=0;
		if(ce.x<=i&&i<=ce.y)id[i]+=1;
		if(i<=ce.x||ce.y<=i)id[i]-=1;
	}
	for(int i:V)if(id[i]>=0)vv.push_back(i);
	for(edge e:E)if(id[e.x]>=0&&id[e.y]>=0)ee.push_back(e);
	for(int i:q)if(id[Q[i].x]>0&&id[Q[i].y]>0)QQ.push_back(i);
	solve(vv,ee,QQ);
	vv.clear();
	ee.clear();
	QQ.clear();
	for(int i:V)if(id[i]<=0)vv.push_back(i);
	for(edge e:E)if(id[e.x]<=0&&id[e.y]<=0)ee.push_back(e);
	for(int i:q)if(id[Q[i].x]<0&&id[Q[i].y]<0)QQ.push_back(i);
	solve(vv,ee,QQ);
}
vector<int> mv,mQ;
vector<edge> me;
int main()
{
	freopen("distance.in","r",stdin);
	freopen("distance.out","w",stdout);
	int n,m;scanf("%d",&n);
	me.push_back({1,n});
	for(int i=1;i<n;i++)me.push_back({i,i+1}),mv.push_back(i);
	mv.push_back(n);
	for(int i=1;i<=n-3;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		if(x<y)me.push_back({x,y});
		else me.push_back({y,x});
	}
	scanf("%d",&m);
	memset(Ans,63,sizeof(Ans));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&Q[i].x,&Q[i].y);
		if(Q[i].x==Q[i].y)Ans[i]=0;
		else mQ.push_back(i);
	}
	solve(mv,me,mQ);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}