#include<cstdio>
#include<cstring>
using namespace std;
inline long long mul(long long x,long long y){return x*y-(long long)((long double)x*y/100000000000000003ll)*100000000000000003ll;}
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int rt[51][1010000];
long long cc[210000][51];
struct node
{
	long long c;
	int cnt,next;
}tr[10010000];
int Q[10010000],head,tail;
inline int pop()
{
	int re=Q[head];
	if(head==10000000)head=1;
	else head++;
	return re;
}
inline void push(int c)
{
	Q[tail]=c;
	if(tail==10000000)tail=1;
	else tail++;
}
void ins(int len,long long c)
{
	int lst=-1;
	for(int x=rt[len][c%1000000];x!=-1;x=tr[x].next)
	{
		if(tr[x].c==c){tr[x].cnt++;return ;}
		lst=x;
	}
	int x=pop();
	tr[x].c=c;
	if(lst==-1)
	{
		rt[len][c%1000000]=x;
		tr[x].cnt=1;
		tr[x].next=-1;
	}
	else
	{
		tr[lst].next=x;
		tr[x].cnt=1;
		tr[x].next=-1;
	}
}
void era(int len,long long c)
{
	int lst=-1;
	for(int x=rt[len][c%1000000];x!=-1;x=tr[x].next)
	{
		if(tr[x].c==c)
		{
			tr[x].cnt--;
			if(tr[x].cnt==0)
			{
				if(lst==-1)rt[len][c%1000000]=-1;
				else tr[lst].next=tr[x].next;
				push(x);
			}
			break;
		}
		lst=x;
	}
}
int fin(int len,long long c)
{
	int s=0;
	for(int x=rt[len][c%1000000];x!=-1;x=tr[x].next)if(tr[x].c==c)s+=tr[x].cnt;
	return s;
}
struct Lian
{
	int last,next;
}L[210000];
int a[210000];
char st[10010000];
int main()
{
	freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);
	int n,m;read(n);read(m);
	memset(rt,-1,sizeof(rt));
	head=1;tail=10000000;
	for(int i=1;i<=10000000;i++)Q[i]=i;
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		cc[i][1]=a[i];
		ins(1,a[i]);
		L[i].last=L[i].next=-1;
	}
	for(int i=1;i<=m;i++)
	{
		int opt;read(opt);
		if(opt==1)
		{
			int x,y;read(x);read(y);
			L[x].next=y;L[y].last=x;
			for(int j=1,X=x;j<50&&X!=-1;j++,X=L[X].last)
			{
				for(int k=1,Y=y;j+k<=50&&Y!=-1;k++,Y=L[Y].next)
				{
					cc[X][j+k]=(cc[X][j+k-1]*7+a[Y])%100000000000000003ll;
					ins(j+k,cc[X][j+k]);
				}
			}
		}
		else if(opt==2)
		{
			int x;read(x);
			int k=1;
			for(int X=L[x].next;k<=50&&X!=-1;k++,X=L[X].next);
			k--;
			L[L[x].next].last=-1;
			L[x].next=-1;
			for(int j=1,X=x;j<50&&X!=-1;j++,X=L[X].last)
			{
				for(int kk=1;j+kk<=50&&kk<=k;kk++)era(j+kk,cc[X][j+kk]);
			}
		}
		else if(opt==3)
		{
			scanf("%s",st+1);
			int len=strlen(st+1);
			int k;read(k);
			long long c=0,g=1;
			for(int kk=1;kk<=k;kk++)c=(c*7+st[kk]-'0')%100000000000000003ll;
			for(int kk=1;kk<k;kk++)g=g*7%100000000000000003ll;
			long long ss=fin(k,c);
			for(int j=2;j+k-1<=len;j++)
			{
				c=((c-mul((st[j-1]-'0'),g)+100000000000000003ll)*7+st[j+k-1]-'0')%100000000000000003ll;
				ss=ss*fin(k,c)%998244353;
			}
			printf("%lld\n",ss);
		}
	}
	return 0;
}