#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int> son[310000];
int S[310000],tot[310000];
int z,in[310000],out[310000];
void dfs(int x)
{
	in[x]=++z;
	S[x]=0;tot[x]=1;
	for(int i=0;i<son[x].size();i++)
	{
		int y=son[x][i];
		dfs(y);
		if(tot[S[x]]<tot[y])S[x]=y;
		tot[x]+=tot[y];
	}
	out[x]=z;
}
struct node
{
	int x,y;
}a[310000];
inline bool operator<(node x,node y){return x.y*y.x>y.y*x.x;}
/*
int root;
struct SBT
{
	int l,r,c,size;
}tr[310000];int len;
inline void r_rotate(int &x)
{
	int l=tr[x].l;
	tr[x].l=tr[l].r;
	tr[l].r=x;
	tr[l].size=tr[x].size;
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	x=l;
}
inline void l_rotate(int &x)
{
	int r=tr[x].r;
	tr[x].r=tr[r].l;
	tr[r].l=x;
	tr[r].size=tr[x].size;
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	x=r;
}
inline int new_node(int c)
{
	len++;
	tr[len].l=tr[len].r=0;
	tr[len].c=c;tr[len].size=1;
	return len;
}
void maintain(int &x,bool bk)
{
	if(bk==false)
	{
		if(tr[tr[tr[x].l].l].size>tr[tr[x].r].size)r_rotate(x);
		else if(tr[tr[tr[x].l].r].size>tr[tr[x].r].size)
		{
			l_rotate(tr[x].l);
			r_rotate(x);
		}
		else return ;
	}
	else
	{
		if(tr[tr[tr[x].r].r].size>tr[tr[x].l].size)l_rotate(x);
		else if(tr[tr[tr[x].r].l].size>tr[tr[x].l].size)
		{
			r_rotate(tr[x].r);
			l_rotate(x);
		}
		else return ;
	}
	maintain(tr[x].l,false);
	maintain(tr[x].r,true);
	maintain(x,false);
	maintain(x,true);
}
void add(int &x,int k,int pos)
{
	if(x==0)x=new_node(pos);
	else
	{
		tr[x].size++;
		bool bk=k>tr[tr[x].l].size+1;
		if(bk==false)add(tr[x].l,k,pos);
		else add(tr[x].r,k-tr[tr[x].l].size-1,pos);
		maintain(x,bk);
	}
}
int rank(int x,int k,int pos)
{
	if(x==0)return 1;
	if(k<=tr[tr[x].l].size)
	{
		if(a[pos]<a[tr[x].c])return rank(tr[x].l,k,pos);
	}
	else return tr[tr[x].l].size+1+rank(tr[x].r,k-tr[tr[x].l].size-1,pos);
}*/
int p[310000];
/*
void print(int x,int first)
{
	if(x==0)return ;
	print(tr[x].l,first);
	p[first+tr[tr[x].l].size]=tr[x].c;
	print(tr[x].r,first+tr[tr[x].l].size+1);
}
*/
int pp[310000];
void dsu(int x)
{
	int head=in[x]+1,tail=in[x];
	for(int i=0;i<son[x].size();i++)
	{
		int y=son[x][i];
		dsu(y);
		int j=head,k=in[y],l=head;
		while(j<=tail&&k<=out[y])
		{
			if(a[p[j]]<a[p[k]])pp[l++]=p[j++];
			else pp[l++]=p[k++];
		}
		while(j<=tail)pp[l++]=p[j++];
		while(k<=out[y])pp[l++]=p[k++];
		tail=out[y];
		for(l=head;l<=tail;l++)p[l]=pp[l];
	}
	p[in[x]]=x;
}
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		int f;scanf("%d",&f);
		son[f].push_back(i);
	}
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	z=0;dfs(1);
	//root=len=0;
	dsu(1);
	long long ss=0,s=0;
	for(int i=n;i>=1;i--)
	{
		ss=ss+a[p[i]].y*s;
		s=s+a[p[i]].x;
	}
	printf("%lld\n",ss);
	return 0;
}
