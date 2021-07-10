#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
double Ans[110000];
struct point{double x,y;};
struct segment{point x,y;}S1[110000],S2[110000];
struct Query{point x;int p;}Q1[410000],Q2[410000];
inline void GS(int p,double c){p<0?Ans[-p]-=c:Ans[p]+=c;}
inline double sqr(double x){return x*x;}
inline double lenS(segment s){return sqrt(sqr(s.x.x-s.y.x)+sqr(s.x.y-s.y.y));}
inline double f(segment s,double x){return s.x.y+(x-s.x.x)*(s.x.y-s.y.y)/(s.x.x-s.y.x);}
namespace Alice
{
	double X;
	int root;
	struct treap
	{
		int l,r,c,size;
		segment key;
		double k,b;
	}tr[110000];int len;
	inline void update(int x)
	{
		tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
		double e=lenS(tr[x].key)/(tr[x].key.y.x-tr[x].key.x.x);
		tr[x].k=tr[tr[x].l].k+tr[tr[x].r].k+e;
		tr[x].b=tr[tr[x].l].b+tr[tr[x].r].b-e*tr[x].key.x.x;
	};
	void split(int now,double c,int &x,int &y)
	{
		if(now==0)x=y=0;
		else
		{
			if(c<f(tr[now].key,X))
			{
				y=now;split(tr[now].l,c,x,tr[y].l);
			}
			else
			{
				x=now;split(tr[now].r,c,tr[x].r,y);
			}
			update(now);
		}
	}
	int merge(int x,int y)
	{
		if(x==0||y==0)return x+y;
		if(tr[x].c<tr[y].c)
		{
			tr[x].r=merge(tr[x].r,y);
			update(x);
			return x;
		}
		else
		{
			tr[y].l=merge(x,tr[y].l);
			update(y);
			return y;
		}
	}
	inline int new_node(segment key)
	{
		len++;
		tr[len].key=key;
		tr[len].c=rand();
		tr[len].l=tr[len].r=0;
		update(len);
		return len;
	}
	inline void add(segment key)
	{
		int a,b;split(root,key.x.y,a,b);
		root=merge(merge(a,new_node(key)),b);
	}
	inline void del(segment key)
	{
		int a,b,c,d;split(root,key.y.y+1e-9,a,b);
		split(a,key.y.y-1e-9,c,d);
		d=merge(tr[d].l,tr[d].r);
		root=merge(merge(c,merge(tr[d].l,tr[d].r)),b);
	}
	inline double sum(double c)
	{
		int a,b;split(root,c,a,b);
		double re=tr[a].k*X+tr[a].b;
		root=merge(a,b);
		return re;
	}
}
namespace Beatrice
{
	int root;
	struct treap
	{
		int l,r,c,size;
		double key,cc,L;
	}tr[110000];int len;
	inline void update(int x)
	{
		tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
		tr[x].cc=tr[tr[x].l].cc+tr[tr[x].r].cc+tr[x].L;
	};
	void split(int now,double c,int &x,int &y)
	{
		if(now==0)x=y=0;
		else
		{
			if(c<tr[now].key)
			{
				y=now;split(tr[now].l,c,x,tr[y].l);
			}
			else
			{
				x=now;split(tr[now].r,c,tr[x].r,y);
			}
			update(now);
		}
	}
	int merge(int x,int y)
	{
		if(x==0||y==0)return x+y;
		if(tr[x].c<tr[y].c)
		{
			tr[x].r=merge(tr[x].r,y);
			update(x);
			return x;
		}
		else
		{
			tr[y].l=merge(x,tr[y].l);
			update(y);
			return y;
		}
	}
	inline int new_node(double key,double L)
	{
		len++;
		tr[len].size=1;
		tr[len].key=key;
		tr[len].c=rand();
		tr[len].l=tr[len].r=0;
		tr[len].cc=tr[len].L=L;
		return len;
	}
	inline void add(segment s)
	{
		int a,b;split(root,s.y.y,a,b);
		root=merge(merge(a,new_node(s.y.y,lenS(s))),b);
	}
	inline double sum(double c)
	{
		int a,b;split(root,c,a,b);
		double re=tr[a].cc;
		root=merge(a,b);
		return re;
	}
}
struct Third
{
	double x;int p,id;
}T[510000];int tl;
inline bool operator<(Third x,Third y){return x.x<y.x;}
int main()
{
	freopen("dezhoupuke.in","r",stdin);
	freopen("dezhoupuke.out","w",stdout);
	int n;scanf("%d",&n);
	int N1=0,N2=0;
	for(int i=1;i<=n;i++)
	{
		double x1,y1,x2,y2;scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		x1+=2e-4*rand()/RAND_MAX-1e-4;
		y1+=2e-4*rand()/RAND_MAX-1e-4;
		x2+=2e-4*rand()/RAND_MAX-1e-4;
		y2+=2e-4*rand()/RAND_MAX-1e-4;
		if((y1-y2)/(x1-x2)>0)
		{
			if(x1>x2)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
			S1[++N1]=(segment){(point){x1,y1},(point){x2,y2}};
		}
		else
		{
			x1=1e6-x1;x2=1e6-x2;
			if(x1>x2)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
			S2[++N2]=(segment){(point){x1,y1},(point){x2,y2}};
		}
	}
	int m;scanf("%d",&m);
	int M=0;
	for(int i=1;i<=m;i++)
	{
		double x1,y1,x2,y2;scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		x1+=2e-4*rand()/RAND_MAX-1e-4;
		y1+=2e-4*rand()/RAND_MAX-1e-4;
		x2+=2e-4*rand()/RAND_MAX-1e-4;
		y2+=2e-4*rand()/RAND_MAX-1e-4;
		Q1[M+1]=(Query){(point){x1,y1},i};
		Q1[M+2]=(Query){(point){x2,y2},i};
		Q1[M+3]=(Query){(point){x1,y2},-i};
		Q1[M+4]=(Query){(point){x2,y1},-i};
		x1=1e6-x1;x2=1e6-x2;
		swap(x1,x2);
		Q2[M+1]=(Query){(point){x1,y1},i};
		Q2[M+2]=(Query){(point){x2,y2},i};
		Q2[M+3]=(Query){(point){x1,y2},-i};
		Q2[M+4]=(Query){(point){x2,y1},-i};
		M+=4;
	}
	//partA
	{
		using namespace Beatrice;
		tl=0;
		for(int i=1;i<=N1;i++)T[++tl]=(Third){S1[i].y.x,i,1};
		for(int i=1;i<=M;i++)T[++tl]=(Third){Q1[i].x.x,i,2};
		sort(T+1,T+tl+1);
		root=len=0;
		for(int i=1;i<=tl;i++)
		{
			if(T[i].id==1)add(S1[T[i].p]);
			else GS(Q1[T[i].p].p,sum(Q1[T[i].p].x.y));
		}
	}
	//partB
	{
		using namespace Alice;
		tl=0;
		for(int i=1;i<=N1;i++)
		{
			T[++tl]=(Third){S1[i].x.x,i,1};
			T[++tl]=(Third){S1[i].y.x,i,2};
		}
		for(int i=1;i<=M;i++)T[++tl]=(Third){Q1[i].x.x,i,3};
		sort(T+1,T+tl+1);
		root=len=0;
		for(int i=1;i<=tl;i++)
		{
			X=T[i].x;
			if(T[i].id==1)add(S1[T[i].p]);
			else if(T[i].id==2)del(S1[T[i].p]);
			else GS(Q1[T[i].p].p,sum(Q1[T[i].p].x.y));
		}
		tl=0;
		for(int i=1;i<=N1;i++)
		{
			swap(S1[i].x.x,S1[i].x.y);
			swap(S1[i].y.x,S1[i].y.y);
			T[++tl]=(Third){S1[i].x.x,i,1};
			T[++tl]=(Third){S1[i].y.x,i,2};
		}
		for(int i=1;i<=M;i++)
		{
			swap(Q1[i].x.x,Q1[i].x.y);
			T[++tl]=(Third){Q1[i].x.x,i,3};
		}
		sort(T+1,T+tl+1);
		root=len=0;
		for(int i=1;i<=tl;i++)
		{
			X=T[i].x;
			if(T[i].id==1)add(S1[T[i].p]);
			else if(T[i].id==2)del(S1[T[i].p]);
			else GS(Q1[T[i].p].p,sum(Q1[T[i].p].x.y));
		}
	}
	//partC
	{
		using namespace Beatrice;
		tl=0;
		for(int i=1;i<=N2;i++)T[++tl]=(Third){S2[i].y.x,i,1};
		for(int i=1;i<=M;i++)T[++tl]=(Third){Q2[i].x.x,i,2};
		sort(T+1,T+tl+1);
		root=len=0;
		for(int i=1;i<=tl;i++)
		{
			if(T[i].id==1)add(S2[T[i].p]);
			else GS(Q2[T[i].p].p,sum(Q2[T[i].p].x.y));
		}
	}
	//partD
	{
		using namespace Alice;
		tl=0;
		for(int i=1;i<=N2;i++)
		{
			T[++tl]=(Third){S2[i].x.x,i,1};
			T[++tl]=(Third){S2[i].y.x,i,2};
		}
		for(int i=1;i<=M;i++)T[++tl]=(Third){Q2[i].x.x,i,3};
		sort(T+1,T+tl+1);
		root=len=0;
		for(int i=1;i<=tl;i++)
		{
			X=T[i].x;
			if(T[i].id==1)add(S2[T[i].p]);
			else if(T[i].id==2)del(S2[T[i].p]);
			else GS(Q2[T[i].p].p,sum(Q2[T[i].p].x.y));
		}
		tl=0;
		for(int i=1;i<=N2;i++)
		{
			swap(S2[i].x.x,S2[i].x.y);
			swap(S2[i].y.x,S2[i].y.y);
			T[++tl]=(Third){S2[i].x.x,i,1};
			T[++tl]=(Third){S2[i].y.x,i,2};
		}
		for(int i=1;i<=M;i++)
		{
			swap(Q2[i].x.x,Q2[i].x.y);
			T[++tl]=(Third){Q2[i].x.x,i,3};
		}
		sort(T+1,T+tl+1);
		root=len=0;
		for(int i=1;i<=tl;i++)
		{
			X=T[i].x;
			if(T[i].id==1)add(S2[T[i].p]);
			else if(T[i].id==2)del(S2[T[i].p]);
			else GS(Q2[T[i].p].p,sum(Q2[T[i].p].x.y));
		}
	}
	double ss=0;
	for(int i=1;i<=N1;i++)ss+=lenS(S1[i]);
	for(int i=1;i<=N2;i++)ss+=lenS(S2[i]);
	for(int i=1;i<=m;i++)printf("%.6lf\n",Ans[i]/ss);
	return 0;
}