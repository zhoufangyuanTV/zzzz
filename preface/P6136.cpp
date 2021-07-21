#include<cstdio>
#include<cstring>
#include<algorithm>
int root;
struct SBT
{
	int l,r,c,size;
}tr[1110000];int len;
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
		if(tr[tr[tr[x].l].l].size>tr[tr[x].r].size)
		{
			r_rotate(x);
		}
		else if(tr[tr[tr[x].l].r].size>tr[tr[x].r].size)
		{
			l_rotate(tr[x].l);
			r_rotate(x);
		}
		else return ;
	}
	else
	{
		if(tr[tr[tr[x].r].r].size>tr[tr[x].l].size)
		{
			l_rotate(x);
		}
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
void add(int &x,int c)
{
	if(x==0)
	{
		x=new_node(c);
	}
	else
	{
		tr[x].size++;
		if(c<tr[x].c)add(tr[x].l,c);
		else add(tr[x].r,c);
		maintain(x,c>=tr[x].c);
	}
}
int del(int &x,int c)
{
	int re;
	tr[x].size--;
	if((c==tr[x].c)||(c<tr[x].c&&tr[x].l==0)||(c>tr[x].c&&tr[x].r==0))
	{
		re=tr[x].c;
		if((tr[x].l==0)||(tr[x].r==0))
		{
			x=tr[x].l+tr[x].r;
		}
		else
		{
			tr[x].c=del(tr[x].l,tr[x].c+1);
		}
	}
	else
	{
		if(c<tr[x].c)re=del(tr[x].l,c);
		else re=del(tr[x].r,c);
	}
	return re;
}
bool find(int x,int c)
{
	if(x==0)return false;
	if(c==tr[x].c)return true;
	if(c<tr[x].c)return find(tr[x].l,c);
	else return find(tr[x].r,c);
}
int rank(int x,int c)
{
	if(x==0)return 1;
	if(c<=tr[x].c)return rank(tr[x].l,c);
	else return tr[tr[x].l].size+rank(tr[x].r,c)+1;
}
int select(int x,int k)
{
	if(k==tr[tr[x].l].size+1)return tr[x].c;
	else
	{
		if(k<=tr[tr[x].l].size)return select(tr[x].l,k);
		else return select(tr[x].r,k-tr[tr[x].l].size-1);
	}
}
int pred(int x,int c)
{
	if(x==0)return -1;
	if(c<=tr[x].c)return pred(tr[x].l,c);
	else
	{
		int t=pred(tr[x].r,c);
		if(t==-1)return tr[x].c;
		else return t;
	}
}
int succ(int x,int c)
{
	if(x==0)return -1;
	if(c>=tr[x].c)return succ(tr[x].r,c);
	else
	{
		int t=succ(tr[x].l,c);
		if(t==-1)return tr[x].c;
		else return t;
	}
}
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int a[110000];
int build(int l,int r)
{
	if(l>r)return 0;
	int mid=(l+r)/2;
	int x=new_node(a[mid]);
	tr[x].l=build(l,mid-1);
	tr[x].r=build(mid+1,r);
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	return x;
}
int main()
{
	int n,m,opt,x;read(n);read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	std::sort(a+1,a+n+1);
	len=0;root=build(1,n);
	int last=0,ss=0;
	for(int i=1;i<=m;i++)
	{
		read(opt);read(x);
		x^=last;
		if(opt==1)add(root,x);
		else if(opt==2)del(root,x);
		else if(opt==3)ss^=last=rank(root,x);
		else if(opt==4)ss^=last=select(root,x);
		else if(opt==5)ss^=last=pred(root,x);
		else if(opt==6)ss^=last=succ(root,x);
	}
	printf("%d\n",ss);
	return 0;
}