#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct qq{int opt,x1,y1,x2,y2,k;}q[310000];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
struct tree
{
	struct node
	{
		int l,r,lc,rc;
		set<int> c;
	}tr[610000];int len;
	void bt(int l,int r)
	{
		len++;int now=len;
		tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
		if(l<r)
		{
			int mid=(l+r)/2;
			tr[now].lc=len+1;bt(l,mid);
			tr[now].rc=len+1;bt(mid+1,r);
		}
	}
	void change(int now,int x,int c)
	{
		tr[now].c.insert(c);
		if(tr[now].l==tr[now].r)return ;
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(x<=mid)change(lc,x,c);
		else change(rc,x,c);
	}
	bool find(int now,int l,int r,int c)
	{
		if(tr[now].l==l&&tr[now].r==r)return tr[now].c.find(c)!=tr[now].c.end();
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(r<=mid)return find(lc,l,r,c);
		else if(l>=mid+1)return find(rc,l,r,c);
		else
		{
			if(find(lc,l,mid,c)==true)return true;
			else return find(rc,mid+1,r,c);
		}
	}
	int pred(int now,int l,int r,int c)
	{
		if(tr[now].l==l&&tr[now].r==r)
		{
			if(tr[now].c.size()==0)return -1;
			set<int>::iterator it=tr[now].c.lower_bound(c);
			if(it==tr[now].c.end())return *tr[now].c.rbegin();
			if(it==tr[now].c.begin())return -1;
			else
			{
				it--;
				return *it;
			}
		}
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(r<=mid)return pred(lc,l,r,c);
		else if(l>=mid+1)return pred(rc,l,r,c);
		else return mymax(pred(lc,l,mid,c),pred(rc,mid+1,r,c));
	}
	int succ(int now,int l,int r,int c)
	{
		if(tr[now].l==l&&tr[now].r==r)
		{
			set<int>::iterator it=tr[now].c.lower_bound(c);
			if(it==tr[now].c.end())return 999999999;
			else return *it;
		}
		int lc=tr[now].lc,rc=tr[now].rc;
		int mid=(tr[now].l+tr[now].r)/2;
		if(r<=mid)return succ(lc,l,r,c);
		else if(l>=mid+1)return succ(rc,l,r,c);
		else return mymin(succ(lc,l,mid,c),succ(rc,mid+1,r,c));
	}
}H,L;
int main()
{
	freopen("snow.in","r",stdin);
	freopen("snow.out","w",stdout);
	int n,m,t;read(n);read(m);read(t);
	for(int i=1;i<=t;i++)
	{
		read(q[i].opt);read(q[i].x1);
		if(q[i].opt==3)
		{
			read(q[i].y1);read(q[i].x2);read(q[i].y2);read(q[i].k);
		}
	}
	H.len=0;H.bt(1,n);
	L.len=0;L.bt(1,m);
	for(int i=1;i<=t;i++)
	{
		if(q[i].opt==1)H.change(1,i,q[i].x1);
		else if(q[i].opt==2)L.change(1,i,q[i].x1);
		else
		{
			if(q[i].k<=i){printf("%d\n",abs(q[i].x1-q[i].x2)+abs(q[i].y1-q[i].y2));continue;}
			bool h1=H.find(1,i-q[i].k,i,q[i].x1),h2=H.find(1,i-q[i].k,i,q[i].x2);
			bool l1=L.find(1,i-q[i].k,i,q[i].y1),l2=L.find(1,i-q[i].k,i,q[i].y2);
			if(h1==true&&l2==true||h2==true&&l1==true){printf("%d\n",abs(q[i].x1-q[i].x2)+abs(q[i].y1-q[i].y2));continue;}
			if(h1==true&&h2==true)
			{
				if(q[i].y1>q[i].y2)
				{
					int t=q[i].x1;q[i].x1=q[i].x2;q[i].x2=t;
					t=q[i].y1;q[i].y1=q[i].y2;q[i].y2=t;
				}
				int yy=L.pred(1,i-q[i].k,i,q[i].y2);
				int ss=0;
				if(yy>q[i].y1)printf("%d\n",abs(q[i].x1-q[i].x2)+abs(q[i].y1-q[i].y2));
				else
				{
					if(yy!=-1)ss=abs(q[i].x1-q[i].x2)+q[i].y1-yy+q[i].y2-yy;
					else ss=999999999;
					yy=L.succ(1,i-q[i].k,i,q[i].y2);
					if(ss==999999999&&yy==999999999){puts("-1");continue;}
					if(yy!=999999999)
					{
						if(ss!=999999999)ss=mymin(ss,abs(q[i].x1-q[i].x2)+yy-q[i].y1+yy-q[i].y2);
						else ss=abs(q[i].x1-q[i].x2)+yy-q[i].y1+yy-q[i].y2;
					}
					printf("%d\n",ss);
				}
			}
			else if(l1==true&&l2==true)
			{
				if(q[i].x1>q[i].x2)
				{
					int t=q[i].x1;q[i].x1=q[i].x2;q[i].x2=t;
					t=q[i].y1;q[i].y1=q[i].y2;q[i].y2=t;
				}
				int yy=H.pred(1,i-q[i].k,i,q[i].x2);
				int ss=0;
				if(yy>q[i].y1)printf("%d\n",abs(q[i].x1-q[i].x2)+abs(q[i].y1-q[i].y2));
				else
				{
					if(yy!=-1)ss=abs(q[i].y1-q[i].y2)+q[i].x1-yy+q[i].x2-yy;
					else ss=999999999;
					yy=H.succ(1,i-q[i].k,i,q[i].x2);
					if(ss==999999999&&yy==999999999){puts("-1");continue;}
					if(yy!=999999999)
					{
						if(ss!=999999999)ss=mymin(ss,abs(q[i].y1-q[i].y2)+yy-q[i].x1+yy-q[i].x2);
						else ss=abs(q[i].y1-q[i].y2)+yy-q[i].x1+yy-q[i].x2;
					}
					printf("%d\n",ss);
				}
			}
			else puts("-1");
		}
	}
	return 0;
}
