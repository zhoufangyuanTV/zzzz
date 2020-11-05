#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
struct SegmentTree
{
	struct node
	{
		int l,r,lc,rc,c,cc;
	}tr[2010000];int len;
	void bt(int l,int r)
	{
		len++;int now=len;
		tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].c=tr[now].cc=0;
		if(l<r)
		{
			int mid=(l+r)/2;
			tr[now].lc=len+1;bt(l,mid);
			tr[now].rc=len+1;bt(mid+1,r);
		}
	}
	void change(int now,int x,int c)
	{
		if(tr[now].l==tr[now].r){tr[now].c=tr[now].cc=c;return ;}
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(x<=mid)change(lc,x,c);
		else change(rc,x,c);
		tr[now].c=mymax(tr[lc].c,tr[rc].c);
		tr[now].cc=mymin(tr[lc].cc,tr[rc].cc);
	}
	int pred(int now,int x,int c)
	{
		if(tr[now].c<c)return -1;
		if(tr[now].l==tr[now].r)return tr[now].l;
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(x<=mid)return pred(lc,x,c);
		else
		{
			int t=pred(rc,x,c);
			if(t==-1)return pred(lc,x,c);
			else return t;
		}
	}
	int succ(int now,int x,int c)
	{
		if(tr[now].c<c)return -1;
		if(tr[now].l==tr[now].r)return tr[now].l;
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(x<=mid)
		{
			int t=succ(lc,x,c);
			if(t==-1)return succ(rc,x,c);
			else return t;
		}
		else return succ(rc,x,c);
	}
	int findmin(int now,int l,int r)
	{
		if(tr[now].l==l&&tr[now].r==r)return tr[now].cc;
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(r<=mid)return findmin(lc,l,r);
		else if(l>=mid+1)return findmin(rc,l,r);
		else return mymin(findmin(lc,l,mid),findmin(rc,mid+1,r));
	}
}H,L;
inline int dis(int x1,int y1,int x2,int y2){return abs(x1-x2)+abs(y1-y2);}
int h[1010000],l[1010000];
int main()
{
	freopen("snow.in","r",stdin);
	freopen("snow.out","w",stdout);
	int n,m,t;read(n);read(m);read(t);
	H.len=0;H.bt(1,n);
	L.len=0;L.bt(1,m);
	memset(h,0,sizeof(h));
	memset(l,0,sizeof(l));
	for(int i=1;i<=t;i++)
	{
		int opt;read(opt);
		if(opt==1)
		{
			int x;read(x);
			H.change(1,x,i);
			h[x]=i;
		}
		else if(opt==2)
		{
			int x;read(x);
			L.change(1,x,i);
			l[x]=i;
		}
		else
		{
			int x1,y1,x2,y2,k;
			read(x1);read(y1);read(x2);read(y2);read(k);
			k=i-k;int d=dis(x1,y1,x2,y2);
			if(k<=h[x1]&&k<=l[y2]||k<=h[x2]&&k<=l[y1])printf("%d\n",d);
			else if(k<=h[x1]&&k<=h[x2])
			{
				if(x1>x2)x1^=x2^=x1^=x2,y1^=y2^=y1^=y2;
				if(k<=H.findmin(1,x1,x2)){printf("%d\n",d);continue;}
				if(y1>y2)x1^=x2^=x1^=x2,y1^=y2^=y1^=y2;
				int y=L.pred(1,y2,k);
				if(y1<y){printf("%d\n",d);continue;}
				int ss=0x3f3f3f3f;
				if(y!=-1)ss=(y1-y)*2;
				y=L.succ(1,y2,k);
				if(y!=-1)ss=mymin(ss,(y-y2)*2);
				if(ss==0x3f3f3f3f)puts("-1");
				else printf("%d\n",d+ss);
			}
			else if(k<=l[y1]&&k<=l[y2])
			{
				if(y1>y2)x1^=x2^=x1^=x2,y1^=y2^=y1^=y2;
				if(k<=L.findmin(1,y1,y2)){printf("%d\n",d);continue;}
				if(x1>x2)x1^=x2^=x1^=x2,y1^=y2^=y1^=y2;
				int x=H.pred(1,x2,k);
				if(x1<x){printf("%d\n",d);continue;}
				int ss=0x3f3f3f3f;
				if(x!=-1)ss=(x1-x)*2;
				x=H.succ(1,x2,k);
				if(x!=-1)ss=mymin(ss,(x-x2)*2);
				if(ss==0x3f3f3f3f)puts("-1");
				else printf("%d\n",d+ss);
			}
			else puts("-1");
		}
	}
	return 0;
}