#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
inline void write(int x)
{
	int y=10;
	while(y<=x)y*=10;
	while(y!=1){y/=10;putchar(x/y+'0');x%=y;}
	putchar('\n');
}
struct node
{
	int l,r,lc,rc,c;
	int e,ei,ne,nei;
	int p,pi,np,npi;
	int n1,n2,n3,n4;
	bool bk;
}tr[410000];int len;
int a[210000];
inline void update(int x)
{
	tr[x].e=tr[tr[x].lc].e+tr[tr[x].rc].e;
	tr[x].ei=tr[tr[x].lc].ei+tr[tr[x].rc].ei;
	tr[x].ne=tr[tr[x].lc].ne+tr[tr[x].rc].ne;
	tr[x].nei=tr[tr[x].lc].nei+tr[tr[x].rc].nei;
	tr[x].p=tr[tr[x].lc].p+tr[tr[x].rc].p;
	tr[x].pi=tr[tr[x].lc].pi+tr[tr[x].rc].pi;
	tr[x].np=tr[tr[x].lc].np+tr[tr[x].rc].np;
	tr[x].npi=tr[tr[x].lc].npi+tr[tr[x].rc].npi;
	tr[x].n1=tr[tr[x].lc].n1+tr[tr[x].rc].n1;
	tr[x].n2=tr[tr[x].lc].n2+tr[tr[x].rc].n2;
	tr[x].n3=tr[tr[x].lc].n3+tr[tr[x].rc].n3;
	tr[x].n4=tr[tr[x].lc].n4+tr[tr[x].rc].n4;
}
inline void change(int x,bool bk,int c)
{
	if(c==0)tr[x].c=tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=tr[x].p=tr[x].pi=tr[x].np=tr[x].npi=tr[x].n1=tr[x].n2=tr[x].n3=tr[x].n4=0;
	else if(bk)
	{
		if(c==2)
		{
			if(tr[x].c==1)tr[x].c=2;
			else if(tr[x].c==2)tr[x].c=3;
			else if(tr[x].c==3)tr[x].c=4;
			else if(tr[x].c==4)tr[x].c=1;
			else if(tr[x].c==5)tr[x].c=6;
			else if(tr[x].c==6)tr[x].c=7;
			else if(tr[x].c==7)tr[x].c=8;
			else if(tr[x].c==8)tr[x].c=5;
			else if(tr[x].c==9)tr[x].c=10;
			else if(tr[x].c==10)tr[x].c=11;
			else if(tr[x].c==11)tr[x].c=12;
			else if(tr[x].c==12)tr[x].c=9;
			int e=tr[x].e;tr[x].e=tr[x].nei;tr[x].nei=tr[x].ne;tr[x].ne=tr[x].ei;tr[x].ei=e;
			int p=tr[x].p;tr[x].p=tr[x].npi;tr[x].npi=tr[x].np;tr[x].np=tr[x].pi;tr[x].pi=p;
			int n1=tr[x].n1;tr[x].n1=tr[x].n4;tr[x].n4=tr[x].n3;tr[x].n3=tr[x].n2;tr[x].n2=n1;
		}
		else if(c==3)
		{
			if(tr[x].c==1)tr[x].c=3;
			else if(tr[x].c==2)tr[x].c=4;
			else if(tr[x].c==3)tr[x].c=1;
			else if(tr[x].c==4)tr[x].c=2;
			else if(tr[x].c==5)tr[x].c=7;
			else if(tr[x].c==6)tr[x].c=8;
			else if(tr[x].c==7)tr[x].c=5;
			else if(tr[x].c==8)tr[x].c=6;
			else if(tr[x].c==9)tr[x].c=11;
			else if(tr[x].c==10)tr[x].c=12;
			else if(tr[x].c==11)tr[x].c=9;
			else if(tr[x].c==12)tr[x].c=10;
			int e=tr[x].e;tr[x].e=tr[x].ne;tr[x].ne=e;
			int ei=tr[x].ei;tr[x].ei=tr[x].nei;tr[x].nei=ei;
			int p=tr[x].p;tr[x].p=tr[x].np;tr[x].np=p;
			int pi=tr[x].pi;tr[x].pi=tr[x].npi;tr[x].npi=pi;
			int n1=tr[x].n1;tr[x].n1=tr[x].n3;tr[x].n3=n1;
			int n2=tr[x].n2;tr[x].n2=tr[x].n4;tr[x].n4=n2;
		}
		else if(c==4)
		{
			if(tr[x].c==1)tr[x].c=4;
			else if(tr[x].c==2)tr[x].c=1;
			else if(tr[x].c==3)tr[x].c=2;
			else if(tr[x].c==4)tr[x].c=3;
			else if(tr[x].c==5)tr[x].c=8;
			else if(tr[x].c==6)tr[x].c=5;
			else if(tr[x].c==7)tr[x].c=6;
			else if(tr[x].c==8)tr[x].c=7;
			else if(tr[x].c==9)tr[x].c=12;
			else if(tr[x].c==10)tr[x].c=9;
			else if(tr[x].c==11)tr[x].c=10;
			else if(tr[x].c==12)tr[x].c=11;
			int e=tr[x].e;tr[x].e=tr[x].ei;tr[x].ei=tr[x].ne;tr[x].ne=tr[x].nei;tr[x].nei=e;
			int p=tr[x].p;tr[x].p=tr[x].pi;tr[x].pi=tr[x].np;tr[x].np=tr[x].npi;tr[x].npi=p;
			int n1=tr[x].n1;tr[x].n1=tr[x].n2;tr[x].n2=tr[x].n3;tr[x].n3=tr[x].n4;tr[x].n4=n1;
		}
		else if(c==5)
		{
			if(tr[x].c==1)tr[x].c=5;
			else if(tr[x].c==2)tr[x].c=6;
			else if(tr[x].c==3)tr[x].c=7;
			else if(tr[x].c==4)tr[x].c=8;
			else tr[x].c=0;
			tr[x].p=tr[x].e;tr[x].pi=tr[x].ei;tr[x].np=tr[x].ne;tr[x].npi=tr[x].nei;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=tr[x].n1=tr[x].n2=tr[x].n3=tr[x].n4=0;
		}
		else if(c==6)
		{
			if(tr[x].c==1)tr[x].c=6;
			else if(tr[x].c==2)tr[x].c=7;
			else if(tr[x].c==3)tr[x].c=8;
			else if(tr[x].c==4)tr[x].c=5;
			else tr[x].c=0;
			tr[x].p=tr[x].nei;tr[x].pi=tr[x].e;tr[x].np=tr[x].ei;tr[x].npi=tr[x].ne;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=tr[x].n1=tr[x].n2=tr[x].n3=tr[x].n4=0;
		}
		else if(c==7)
		{
			if(tr[x].c==1)tr[x].c=7;
			else if(tr[x].c==2)tr[x].c=8;
			else if(tr[x].c==3)tr[x].c=5;
			else if(tr[x].c==4)tr[x].c=6;
			else tr[x].c=0;
			tr[x].p=tr[x].ne;tr[x].pi=tr[x].nei;tr[x].np=tr[x].e;tr[x].npi=tr[x].ei;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=tr[x].n1=tr[x].n2=tr[x].n3=tr[x].n4=0;
		}
		else if(c==8)
		{
			if(tr[x].c==1)tr[x].c=8;
			else if(tr[x].c==2)tr[x].c=5;
			else if(tr[x].c==3)tr[x].c=6;
			else if(tr[x].c==4)tr[x].c=7;
			else tr[x].c=0;
			tr[x].p=tr[x].ei;tr[x].pi=tr[x].ne;tr[x].np=tr[x].nei;tr[x].npi=tr[x].e;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=tr[x].n1=tr[x].n2=tr[x].n3=tr[x].n4=0;
		}
		else if(c==9)
		{
			if(tr[x].c==1)tr[x].c=9;
			else if(tr[x].c==2)tr[x].c=10;
			else if(tr[x].c==3)tr[x].c=11;
			else if(tr[x].c==4)tr[x].c=12;
			else if(tr[x].c==9)tr[x].c=6;
			else if(tr[x].c==10)tr[x].c=7;
			else if(tr[x].c==11)tr[x].c=8;
			else if(tr[x].c==12)tr[x].c=5;
			else tr[x].c=0;
			tr[x].p=tr[x].n4;tr[x].pi=tr[x].n1;tr[x].np=tr[x].n2;tr[x].npi=tr[x].n3;
			tr[x].n1=tr[x].e;tr[x].n2=tr[x].ei;tr[x].n3=tr[x].ne;tr[x].n4=tr[x].nei;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=0;
		}
		else if(c==10)
		{
			if(tr[x].c==1)tr[x].c=10;
			else if(tr[x].c==2)tr[x].c=11;
			else if(tr[x].c==3)tr[x].c=12;
			else if(tr[x].c==4)tr[x].c=9;
			else if(tr[x].c==9)tr[x].c=7;
			else if(tr[x].c==10)tr[x].c=8;
			else if(tr[x].c==11)tr[x].c=5;
			else if(tr[x].c==12)tr[x].c=6;
			else tr[x].c=0;
			tr[x].p=tr[x].n3;tr[x].pi=tr[x].n4;tr[x].np=tr[x].n1;tr[x].npi=tr[x].n2;
			tr[x].n1=tr[x].e;tr[x].n2=tr[x].ei;tr[x].n3=tr[x].ne;tr[x].n4=tr[x].nei;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=0;
		}
		else if(c==11)
		{
			if(tr[x].c==1)tr[x].c=11;
			else if(tr[x].c==2)tr[x].c=12;
			else if(tr[x].c==3)tr[x].c=9;
			else if(tr[x].c==4)tr[x].c=10;
			else if(tr[x].c==9)tr[x].c=8;
			else if(tr[x].c==10)tr[x].c=5;
			else if(tr[x].c==11)tr[x].c=6;
			else if(tr[x].c==12)tr[x].c=7;
			else tr[x].c=0;
			tr[x].p=tr[x].n2;tr[x].pi=tr[x].n3;tr[x].np=tr[x].n4;tr[x].npi=tr[x].n1;
			tr[x].n1=tr[x].e;tr[x].n2=tr[x].ei;tr[x].n3=tr[x].ne;tr[x].n4=tr[x].nei;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=0;
		}
		else if(c==12)
		{
			if(tr[x].c==1)tr[x].c=12;
			else if(tr[x].c==2)tr[x].c=9;
			else if(tr[x].c==3)tr[x].c=10;
			else if(tr[x].c==4)tr[x].c=11;
			else if(tr[x].c==9)tr[x].c=5;
			else if(tr[x].c==10)tr[x].c=6;
			else if(tr[x].c==11)tr[x].c=7;
			else if(tr[x].c==12)tr[x].c=8;
			else tr[x].c=0;
			tr[x].p=tr[x].n1;tr[x].pi=tr[x].n2;tr[x].np=tr[x].n3;tr[x].npi=tr[x].n4;
			tr[x].n1=tr[x].e;tr[x].n2=tr[x].ei;tr[x].n3=tr[x].ne;tr[x].n4=tr[x].nei;
			tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=0;
		}
	}
	else
	{
		tr[x].bk=false;tr[x].c=c;
		tr[x].e=tr[x].ei=tr[x].ne=tr[x].nei=tr[x].p=tr[x].pi=tr[x].np=tr[x].npi=tr[x].n1=tr[x].n2=tr[x].n3=tr[x].n4=0;
		if(c==1)tr[x].e=tr[x].r-tr[x].l+1;
		else if(c==2)tr[x].ei=tr[x].r-tr[x].l+1;
		else if(c==3)tr[x].ne=tr[x].r-tr[x].l+1;
		else if(c==4)tr[x].nei=tr[x].r-tr[x].l+1;
		else if(c==5)tr[x].p=tr[x].r-tr[x].l+1;
		else if(c==6)tr[x].pi=tr[x].r-tr[x].l+1;
		else if(c==7)tr[x].np=tr[x].r-tr[x].l+1;
		else if(c==8)tr[x].npi=tr[x].r-tr[x].l+1;
		else if(c==9)tr[x].n1=tr[x].r-tr[x].l+1;
		else if(c==10)tr[x].n2=tr[x].r-tr[x].l+1;
		else if(c==11)tr[x].n3=tr[x].r-tr[x].l+1;
		else tr[x].n4=tr[x].r-tr[x].l+1;
	}
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].bk=true;tr[now].c=1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else change(now,false,a[l]);
}
void change(int now,int l,int r,bool bk,int c)
{
	if(tr[now].l==l&&tr[now].r==r){change(now,bk,c);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	change(lc,tr[now].bk,tr[now].c);
	change(rc,tr[now].bk,tr[now].c);
	tr[now].bk=true;tr[now].c=1;
	if(r<=mid)change(lc,l,r,bk,c);
	else if(l>=mid+1)change(rc,l,r,bk,c);
	else change(lc,l,mid,bk,c),change(rc,mid+1,r,bk,c);
	update(now);
}
int find(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].p;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	change(lc,tr[now].bk,tr[now].c);
	change(rc,tr[now].bk,tr[now].c);
	tr[now].bk=true;tr[now].c=1;
	if(r<=mid)return find(lc,l,r);
	else if(l>=mid+1)return find(rc,l,r);
	else return find(lc,l,mid)+find(rc,mid+1,r);
}
bool b[5100];
int main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	int n,m;read(n);read(m);
	memset(b,true,sizeof(b));
	for(int i=2;i<=5000;i++)
	{
		if(b[i]==true)
		{
			for(int j=i*2;j<=5000;j+=i)b[j]=false;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int x,y;read(x);read(y);
		if(x==1&&y==0)a[i]=1;
		else if(x==0&&y==1)a[i]=2;
		else if(x==-1&&y==0)a[i]=3;
		else if(x==0&&y==-1)a[i]=4;
		else if(x>0&&b[x]&&y==0)a[i]=5;
		else if(x==0&&y>0&&b[y])a[i]=6;
		else if(x<0&&b[-x]&&y==0)a[i]=7;
		else if(x==0&&y<0&&b[-y])a[i]=8;
		else if(x==1&&y==1)a[i]=9;
		else if(x==-1&&y==1)a[i]=10;
		else if(x==-1&&y==-1)a[i]=11;
		else if(x==1&&y==-1)a[i]=12;
		else a[i]=0;
	}
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int opt,l,r;read(opt);read(l);read(r);
		if(opt==1||opt==2)
		{
			int x,y,c;read(x);read(y);
			if(x==1&&y==0)c=1;
			else if(x==0&&y==1)c=2;
			else if(x==-1&&y==0)c=3;
			else if(x==0&&y==-1)c=4;
			else if(x>0&&b[x]&&y==0)c=5;
			else if(x==0&&y>0&&b[y])c=6;
			else if(x<0&&b[-x]&&y==0)c=7;
			else if(x==0&&y<0&&b[-y])c=8;
			else if(x==1&&y==1)c=9;
			else if(x==-1&&y==1)c=10;
			else if(x==-1&&y==-1)c=11;
			else if(x==1&&y==-1)c=12;
			else c=0;
			change(1,l,r,opt==2,c);
		}
		else write(find(1,l,r));
	}
	return 0;
}