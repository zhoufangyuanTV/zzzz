#include"highway.h"
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c,next;
}a[310000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int f[110000],dep[110000];
void dfs(int x,int fa)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			f[y]=a[k].c;
			dep[y]=dep[x]+1;
			dfs(y,x);
		}
	}
}
int p[110000];
inline bool cmp(int x,int y){return dep[x]>dep[y];}
vector<int> As;
long long S;
int solve(int l,int r)
{
	if(l==r)return p[l];
	int mid=(l+r)/2;
	for(vector<int>::iterator it=As.begin();it!=As.end();it++)*it=0;
	for(int i=l;i<=mid;i++)As[f[p[i]]]=1;
	if(S<ask(As))return solve(l,mid);
	else return solve(mid+1,r);
}
void find_pair(int n,vector<int> U,vector<int> V,int A,int B)
{
	int m=U.size();
	len=0;memset(last,0,sizeof(last));
	for(int i=0;i<m;i++)
	{
		ins(U[i],V[i],i);
		ins(V[i],U[i],i);
	}
	As.resize(m);
	for(int i=0;i<m;i++)As[i]=0;
	S=ask(As);
	dep[0]=0;dfs(0,-1);
	for(int i=0;i<n;i++)p[i]=i;
	sort(p,p+n,cmp);
	int X=solve(0,n-2);
	dep[X]=0;dfs(X,-1);
	sort(p,p+n,cmp);
	int Y=solve(0,n-2);
	answer(X,Y);
}
