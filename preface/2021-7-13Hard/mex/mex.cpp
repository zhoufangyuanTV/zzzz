#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct val{int k1,k2;};
inline bool operator<(val x,val y){return x.k1==y.k1?x.k2<y.k2:x.k1<y.k1;}
inline bool operator==(val x,val y){return x.k1==y.k1&&x.k2==y.k2;}
struct SizeBalancedTree
{
	int l,r,c,size;
	val v;
}tr[3410000];
int sta[3410000],top;
inline int mymax(int x,int y){return x>y?x:y;}
inline void update(int x)
{
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	tr[x].c=mymax(mymax(tr[tr[x].l].c,tr[tr[x].r].c),tr[x].v.k2);
}
inline void r_rotate(int &x)
{
	int l=tr[x].l;
	tr[x].l=tr[l].r;
	tr[l].r=x;
	update(x);
	update(x=l);
}
inline void l_rotate(int &x)
{
	int r=tr[x].r;
	tr[x].r=tr[r].l;
	tr[r].l=x;
	update(x);
	update(x=r);
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
inline int new_node(val v)
{
	int now=sta[top--];
	tr[now].v=v;tr[now].c=v.k2;
	tr[now].l=tr[now].r=0;tr[now].size=1;
	return now;
}
void add(int &x,val v)
{
	if(x==0)x=new_node(v);
	else
	{
		bool bk=!(v<tr[x].v);
		if(bk==false)add(tr[x].l,v);
		else add(tr[x].r,v);
		update(x);
		maintain(x,bk);
	}
}
val del(int &x,val v)
{
	val re;
	if(tr[x].v==v||v<tr[x].v&&tr[x].l==0||tr[x].v<v&&tr[x].r==0)
	{
		re=tr[x].v;
		if(tr[x].l==0||tr[x].r==0)
		{
			sta[++top]=x;
			x=tr[x].l+tr[x].r;
		}
		else
		{
			tr[x].v=del(tr[x].l,v);
			update(x);
		}
	}
	else
	{
		if(v<tr[x].v)re=del(tr[x].l,v);
		else re=del(tr[x].r,v);
		update(x);
	}
	return re;
}
bool pand(int x,int l,int r)
{
	if(x==0)return false;
	if(l<tr[x].v.k1)return pand(tr[x].l,l,r);
	else
	{
		if(r<=tr[tr[x].l].c||r<=tr[x].v.k2)return true;
		return pand(tr[x].r,l,r);
	}
}
inline int lowbit(int x){return x&-x;}
int n,a[110000],c[110000];
set<int> S[110000];
inline void ChangeAdd(int x,val s)
{
	while(x<=n)
	{
		add(c[x],s);
		x+=lowbit(x);
	}
}
inline void ChangeDel(int x,val s)
{
	while(x<=n)
	{
		del(c[x],s);
		x+=lowbit(x);
	}
}
int main()
{
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	int T,m;read(T);read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		if(a[i]!=n)S[a[i]].insert(i);
	}
	memset(c,0,sizeof(c));
	for(int i=1;i<=3400000;i++)sta[i]=i;
	top=3400000;
	for(int i=0;i<n;i++)
	{
		int last=0;
		S[i].insert(n+1);
		for(set<int>::iterator it=S[i].begin();it!=S[i].end();it++)
		{
			if(last+1<=*it-1)ChangeAdd(i+1,(val){last+1,*it-1});
			last=*it;
		}
		S[i].insert(0);
	}
	int last=0;
	for(int i=1;i<=m;i++)
	{
		int opt,x,y;read(opt);read(x);read(y);
		if(opt==0)
		{
			x=(x+T*last)%n+1;y=(y+T*last)%n;
			if(a[x]!=n)
			{
				set<int>::iterator it=S[a[x]].find(x);
				set<int>::iterator jt=it;it--;jt++;
				if(*it+1<=x-1)ChangeDel(a[x]+1,(val){*it+1,x-1});
				if(x+1<=*jt-1)ChangeDel(a[x]+1,(val){x+1,*jt-1});
				ChangeAdd(a[x]+1,(val){*it+1,*jt-1});
				S[a[x]].erase(x);
			}
			a[x]=y;
			if(y!=n)
			{
				set<int>::iterator it=S[y].insert(x).first;
				set<int>::iterator jt=it;it--;jt++;
				ChangeDel(y+1,(val){*it+1,*jt-1});
				if(*it+1<=x-1)ChangeAdd(y+1,(val){*it+1,x-1});
				if(x+1<=*jt-1)ChangeAdd(y+1,(val){x+1,*jt-1});
			}
		}
		else
		{
			x=(x+T*last)%n+1;y=(y+T*last)%n+1;
			if(x>y)x^=y^=x^=y;
			int p=65536;
			while(lowbit(p)>1)
			{
				if(p>n)p-=lowbit(p)>>1;
				else if(pand(c[p],x,y))p-=lowbit(p)>>1;
				else p+=lowbit(p)>>1;
			}
			if(p<=n&&!pand(c[p],x,y))p++;
			printf("%d\n",last=p-1);
		}
	}
	return 0;
}