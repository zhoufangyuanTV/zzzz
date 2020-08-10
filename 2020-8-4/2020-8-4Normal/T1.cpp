#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
int root[51000];
struct trie
{
	int son[2],size;
}tr[1610000];int len;
int bt(int x,int a)
{
	int re=++len;
	tr[len]=tr[x];
	x=len;
	tr[x].size++;
	for(int i=29;i>=0;i--)
	{
		int c=(a&1<<i)>>i;
		len++;
		if(tr[x].son[c]!=0)tr[len]=tr[tr[x].son[c]];
		tr[x].son[c]=len;x=len;
		tr[x].size++;
	}
	return re;
}
int find(int l,int r,int g)
{
	int x=root[l-1],y=root[r];
	int ss=0;
	for(int i=29;i>=0;i--)
	{
		int c=(g&1<<i)>>i;
		if(tr[tr[y].son[c^1]].size-tr[tr[x].son[c^1]].size>0)
		{
			ss+=1<<i;
			x=tr[x].son[c^1];
			y=tr[y].son[c^1];
		}
		else
		{
			x=tr[x].son[c];
			y=tr[y].son[c];
		}
	}
	return ss;
}
int a[51000],p[51000],l[51000],ll[51000],r[51000],rr[51000];
inline bool cmp(int x,int y){return a[x]>a[y];}
set<int> S;
int main()
{
	int n;scanf("%d",&n);
	len=0;root[0]=0;
	memset(tr,0,sizeof(tr));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);p[i]=i;
		root[i]=bt(root[i-1],a[i]);
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		set<int>::iterator it=S.lower_bound(p[i]);
		if(it!=S.end())
		{
			r[p[i]]=*it;
			set<int>::iterator j=it;j++;
			if(j!=S.end())rr[p[i]]=*j;
			else rr[p[i]]=n+1;
		}
		else r[p[i]]=rr[p[i]]=n+1;
		if(it!=S.begin())
		{
			it--;
			l[p[i]]=*it;
			if(it!=S.begin())it--,ll[p[i]]=*it;
			else ll[p[i]]=0;
		}
		else l[p[i]]=ll[p[i]]=0;
		S.insert(p[i]);
	}
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		if(l[i]==0&&r[i]==n+1)continue;
		int g=find(ll[i]+1,rr[i]-1,a[i]);
		if(ss<g)ss=g;
	}
	printf("%d\n",ss);
	return 0;
}