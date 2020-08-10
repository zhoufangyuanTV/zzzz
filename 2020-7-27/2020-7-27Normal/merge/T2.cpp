#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int root;
struct FHQ_treap
{
	int l,r,c,size;char key;
	bool bk;
}tr[7350000];int len;
inline void update(int x){tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;}
inline void pushdown(int x)
{
	if(tr[x].bk)
	{
		tr[x].bk=false;
		tr[x].l^=tr[x].r^=tr[x].l^=tr[x].r;
		tr[tr[x].l].bk^=1;tr[tr[x].r].bk^=1;
	}
}
inline int new_node(char key)
{
	len++;
	tr[len].key=key;
	tr[len].size=1;
	tr[len].c=rand();
	tr[len].bk=false;
	tr[len].l=tr[len].r=0;
	return len;
}
void split(int now,int k,int &x,int &y)
{
	if(now==0)x=y=0;
	else
	{
		pushdown(now);
		if(k<=tr[tr[x].l].size)
		{
			y=now;split(tr[now].l,k,x,tr[y].l);
		}
		else
		{
			x=now;split(tr[now].r,k-tr[tr[x].l].size-1,tr[x].r,y);
		}
		update(now);
	}
}
int merge(int x,int y)
{
	if(x==0||y==0)return x+y;
	if(tr[x].c<tr[y].c)
	{
		pushdown(x);
		tr[x].r=merge(tr[x].r,y);
		update(x);
		return x;
	}
	else
	{
		pushdown(y);
		tr[y].l=merge(x,tr[y].l);
		update(y);
		return y;
	}
}
#define T {printf("T\n");return ;}
#define F {printf("F\n");return ;}
int L,R;
inline void Move_Left(char w)
{
	if(w=='L')
	{
		if(L==0)F
		else L--;
	}
	else
	{
		if(R==0)F
		else R--;
	}
	T
}
inline void Move_Right(char w)
{
	if(w=='L')
	{
		if(L==tr[root].size)F
		else L++;
	}
	else
	{
		if(R==tr[root].size)F
		else R++;
	}
	T
}
inline void Insert(char w,char c)
{
	if(w=='L')
	{
		int x,y;split(root,L,x,y);
		root=merge(x,merge(new_node(c),y));
		if(L<=R)R++;L++;
	}
	else
	{
		int x,y;split(root,R,x,y);
		root=merge(x,merge(new_node(c),y));
		if(R<=L)L++;R++;
	}
	T
}
inline void Delete(char w)
{
	if(w=='L')
	{
		if(L==tr[root].size)F
		int x,y,z;split(root,L,x,y);split(y,1,y,z);
		root=merge(x,z);
		if(L<R)R--;
	}
	else
	{
		if(R==tr[root].size)F
		int x,y,z;split(root,R,x,y);split(y,1,y,z);
		root=merge(x,z);
		if(R<L)L--;
	}
	T
}
inline void Reverse()
{
	if(L<R)
	{
		int x,y,z;split(root,R,x,z);split(root,L,x,y);
		tr[y].bk^=1;
		root=merge(x,merge(y,z));
	}
	else F
}
void show(int x)
{
	if(x==0)return ;
	pushdown(x);
	show(tr[x].l);
	putchar(tr[x].key);
	show(tr[x].r);
}
char str[4010000];
int build(int l,int r)
{
	if(l>r)return 0;
	int mid=(l+r)/2;
	int now=new_node(str[mid]);
	tr[now].l=build(l,mid-1);
	tr[now].r=build(mid+1,r);
	update(now);
	return now;
}
int main()
{
	scanf("%s",str+1);
	L=0;R=strlen(str+1);
	root=build(1,R);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		if(str[1]=='<')
		{
			scanf("%s",str+1);
			Move_Left(str[1]);
		}
		else if(str[1]=='>')
		{
			scanf("%s",str+1);
			Move_Right(str[1]);
		}
		else if(str[1]=='I')
		{
			scanf("%s",str+1);
			char w=str[1];
			scanf("%s",str+1);
			Insert(w,str[1]);
		}
		else if(str[1]=='D')
		{
			scanf("%s",str+1);
			Delete(str[1]);
		}
		else if(str[1]=='R')Reverse();
		else show(root);
	}
	return 0;
}
