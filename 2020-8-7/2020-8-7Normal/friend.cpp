//#pragma GCC optimize("Ofast")
#include<cmath>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
using namespace std;
int block[310000];
struct QAQ
{
	int l,r,p;
}Q[51000];
inline bool cmp(QAQ x,QAQ y){return block[x.l]^block[y.l]?x.l<y.l:block[x.l]&1?x.r<y.r:x.r>y.r;}
int Ans[51000];
struct node
{
	int u,v;
}a[310000];
int n,mmp[151][151];bitset<151> map[151],fmap[151];
int sta[151],top;bitset<151> v;
void Kosaraju(int x)
{
	v[x]=0;
	for(int y=(v&map[x])._Find_first();y!=151;y=(v&map[x])._Find_next(y))Kosaraju(y);
	sta[++top]=x;
}
int ss,s;
void fKosaraju(int x)
{
	s++;v[x]=0;
	for(int y=(v&fmap[x])._Find_first();y!=151;y=(v&fmap[x])._Find_next(y))fKosaraju(y);
}
inline void add(int x)
{
	int u=a[x].u,v=a[x].v;
	if(mmp[u][v]==0)map[u][v]=1,fmap[v][u]=1;
	mmp[u][v]++;
}
inline void del(int x)
{
	int u=a[x].u,v=a[x].v;
	mmp[u][v]--;
	if(mmp[u][v]==0)map[u][v]=0,fmap[v][u]=0;
}
int main()
{
	freopen("friend.in","r",stdin);
	freopen("friend.out","w",stdout);
	int m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)scanf("%d%d",&a[i].u,&a[i].v);
	for(int i=1;i<=q;i++)scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].p=i;
	int bk=424/*m/sqrt(q*3/4.0)*/;
	for(int i=1;i<=m;i++)block[i]=(i-1)/bk+1;
	sort(Q+1,Q+q+1,cmp);
	memset(mmp,0,sizeof(mmp));
	for(int i=Q[1].l;i<=Q[1].r;i++)add(i);
	int l=Q[1].l,r=Q[1].r;
	for(int i=1;i<=q;i++)
	{
		while(l>Q[i].l)add(--l);
		while(r<Q[i].r)add(++r);
		while(l<Q[i].l)del(l++);
		while(r>Q[i].r)del(r--);
		v.set();
		for(int j=1;j<=n;j++)if(v[j]==1)Kosaraju(j);
		v.set();
		ss=0;
		while(top>0)
		{
			if(v[sta[top]]==1)
			{
				s=0;
				fKosaraju(sta[top]);
				ss+=s*(s-1)/2;
			}
			top--;
		}
		Ans[Q[i].p]=ss;
	}
	for(int i=1;i<=q;i++)printf("%d\n",Ans[i]);
	return 0;
}