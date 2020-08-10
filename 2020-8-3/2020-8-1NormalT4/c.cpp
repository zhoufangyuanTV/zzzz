#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int m;
//direction
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};
//line
struct line
{
	int x1,y1,x2,y2,d,p;
}L[110000];int n;
inline bool cmpl(line x,line y){return x.p<y.p;}
void readline()
{
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&L[i].x1,&L[i].y1,&L[i].x2,&L[i].y2);
		if(L[i].y1==L[i].y2)
		{
			if(L[i].x1>L[i].x2)L[i].d=0;
			else L[i].d=1;
		}
		else
		{
			if(L[i].y1>L[i].y2)L[i].d=2;
			else L[i].d=3;
		}
		L[i].p=i;
	}
}
//point
struct point
{
	int x,y,d,p;
	long long t;
}P[110000];int q;
inline bool cmpp(point x,point y){return x.p<y.p;}
char s[110000];
void readpoint()
{
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%s%lld",&P[i].x,&P[i].y,s+1,&P[i].t);
		if(s[1]=='L')P[i].d=0;
		else if(s[1]=='R')P[i].d=1;
		else if(s[1]=='D')P[i].d=2;
		else P[i].d=3;
		P[i].p=i;
	}
}
//segmentTree
struct node
{
	int l,r,lc,rc,c;
}tr[210000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=tr[now].c=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
void change(int now,int l,int r,int c)
{
	if(l>r)l^=r^=l^=r;
	if(tr[now].l==l&&tr[now].r==r){tr[now].c=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)
	{
		tr[lc].c=tr[now].c;
		tr[rc].c=tr[now].c;
	}
	if(r<=mid)change(lc,l,r,c);
	else if(l>=mid+1)change(rc,l,r,c);
	else change(lc,l,mid,c),change(rc,mid+1,r,c);
	if(tr[lc].c==tr[rc].c)tr[now].c=tr[lc].c;
	else tr[now].c=-1;
}
int findcol(int now,int x)
{
	if(tr[now].l==tr[now].r)return tr[now].c;
	if(tr[now].c!=-1)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(tr[now].c!=-1)
	{
		tr[lc].c=tr[now].c;
		tr[rc].c=tr[now].c;
	}
	if(x<=mid)return findcol(lc,x);
	else return findcol(rc,x);
}
//nextLine
int nxtl[110000],nxtp[110000];
//left
inline bool cmp0l(line x,line y){return x.x1<y.x1;}
inline bool cmp0p(point x,point y){return x.x<y.x;}
void leftLine()
{
	sort(L+1,L+n+1,cmp0l);
	sort(P+1,P+q+1,cmp0p);
	trlen=0;bt(0,m);
	int j=1,k=1;
	for(int x=0;x<=m;x++)
	{
		while(j<=n&&L[j].x1==x)
		{
			if(L[j].d==0)nxtl[L[j].p]=findcol(1,L[j].y1);
			else change(1,L[j].y1,L[j].y2,L[j].p);
			j++;
		}
		while(k<=q&&P[k].x==x)
		{
			if(P[k].d==0)nxtp[P[k].p]=findcol(1,P[k].y);
			k++;
		}
	}
}
//right
inline bool cmp1l(line x,line y){return x.x1>y.x1;}
inline bool cmp1p(point x,point y){return x.x>y.x;}
void rightLine()
{
	sort(L+1,L+n+1,cmp1l);
	sort(P+1,P+q+1,cmp1p);
	trlen=0;bt(0,m);
	int j=1,k=1;
	for(int x=m;x>=0;x--)
	{
		while(j<=n&&L[j].x1==x)
		{
			if(L[j].d==1)nxtl[L[j].p]=findcol(1,L[j].y1);
			else change(1,L[j].y1,L[j].y2,L[j].p);
			j++;
		}
		while(k<=q&&P[k].x==x)
		{
			if(P[k].d==1)nxtp[P[k].p]=findcol(1,P[k].y);
			k++;
		}
	}
}
//down
inline bool cmp2l(line x,line y){return x.y1<y.y1;}
inline bool cmp2p(point x,point y){return x.y<y.y;}
void downLine()
{
	sort(L+1,L+n+1,cmp2l);
	sort(P+1,P+q+1,cmp2p);
	trlen=0;bt(0,m);
	int j=1,k=1;
	for(int y=0;y<=m;y++)
	{
		while(j<=n&&L[j].y1==y)
		{
			if(L[j].d==2)nxtl[L[j].p]=findcol(1,L[j].x1);
			else change(1,L[j].x1,L[j].x2,L[j].p);
			j++;
		}
		while(k<=q&&P[k].y==y)
		{
			if(P[k].d==2)nxtp[P[k].p]=findcol(1,P[k].x);
			k++;
		}
	}
}
//up
inline bool cmp3l(line x,line y){return x.y1>y.y1;}
inline bool cmp3p(point x,point y){return x.y>y.y;}
void upLine()
{
	sort(L+1,L+n+1,cmp3l);
	sort(P+1,P+q+1,cmp3p);
	trlen=0;bt(0,m);
	int j=1,k=1;
	for(int y=m;y>=0;y--)
	{
		while(j<=n&&L[j].y1==y)
		{
			if(L[j].d==3)nxtl[L[j].p]=findcol(1,L[j].x1);
			else change(1,L[j].x1,L[j].x2,L[j].p);
			j++;
		}
		while(k<=q&&P[k].y==y)
		{
			if(P[k].d==3)nxtp[P[k].p]=findcol(1,P[k].x);
			k++;
		}
	}
}
//2^kthLineAndTime
int kthl[110000][50],kthx[110000][50],kthy[110000][50];
long long tl[110000][50];
void lineAndTime()
{
	sort(L+1,L+n+1,cmpl);
	for(int i=1;i<=n;i++)
	{
		kthl[i][0]=nxtl[i];
		if(nxtl[i]==-1)continue;
		if((L[i].d^1)==L[nxtl[i]].d)
		{
			kthx[i][0]=L[nxtl[i]].x2;
			kthy[i][0]=L[nxtl[i]].y2;
			if(L[i].d/2==0)tl[i][0]=abs(L[i].x2-L[nxtl[i]].x2);
			else tl[i][0]=abs(L[i].y2-L[nxtl[i]].y2);
		}
		else
		{
			if(L[i].d/2==0)
			{
				kthx[i][0]=L[nxtl[i]].x1;
				kthy[i][0]=L[i].y1;
				tl[i][0]=abs(L[i].x2-L[nxtl[i]].x2);
			}
			else
			{
				kthx[i][0]=L[i].x1;
				kthy[i][0]=L[nxtl[i]].y1;
				tl[i][0]=abs(L[i].y2-L[nxtl[i]].y2);
			}
		}
	}
	for(int i=1;i<50;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(kthl[j][i-1]==-1)kthl[j][i]=-1;
			else
			{
				kthl[j][i]=kthl[kthl[j][i-1]][i-1];
				kthx[j][i]=kthx[kthl[j][i-1]][i-1];
				kthy[j][i]=kthy[kthl[j][i-1]][i-1];
				tl[j][i]=tl[j][i-1]+tl[kthl[j][i-1]][i-1]+abs(kthx[j][i-1]-L[kthl[j][i-1]].x2)+abs(kthy[j][i-1]-L[kthl[j][i-1]].y2);
			}
		}
	}
}
//getAnswer
int nxtx[110000],nxty[110000];
long long Ansx[110000],Ansy[110000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
inline long long mymin(long long x,long long y){return x<y?x:y;}
void getans()
{
	sort(P+1,P+q+1,cmpp);
	for(int i=1;i<=q;i++)
	{
		if(nxtp[i]==-1)
		{
			Ansx[i]=P[i].x+dx[P[i].d]*P[i].t;
			Ansy[i]=P[i].y+dy[P[i].d]*P[i].t;
			Ansx[i]=mymax(0,mymin(m,Ansx[i]));
			Ansy[i]=mymax(0,mymin(m,Ansy[i]));
			continue;
		}
		if((P[i].d^1)==L[nxtp[i]].d)
		{
			nxtx[i]=L[nxtp[i]].x2;
			nxty[i]=L[nxtp[i]].y2;
			if((P[i].x-L[nxtp[i]].x2)*dx[P[i].d]>0)P[i].d=P[i].d^1;
			if((P[i].y-L[nxtp[i]].y2)*dy[P[i].d]>0)P[i].d=P[i].d^1;
		}
		else
		{
			if(P[i].d/2==0)
			{
				nxtx[i]=L[nxtp[i]].x1;
				nxty[i]=P[i].y;
			}
			else
			{
				nxtx[i]=P[i].x;
				nxty[i]=L[nxtp[i]].y1;
			}
		}
		long long t=abs(P[i].x-nxtx[i])+abs(P[i].y-nxty[i]);
		if(P[i].t<=t)
		{
			Ansx[i]=P[i].x+dx[P[i].d]*P[i].t;
			Ansy[i]=P[i].y+dy[P[i].d]*P[i].t;
			Ansx[i]=mymax(0,mymin(m,Ansx[i]));
			Ansy[i]=mymax(0,mymin(m,Ansy[i]));
		}
		else
		{
			P[i].t=P[i].t-t;
			int l=nxtp[i],x=nxtx[i],y=nxty[i];
			for(int j=49;j>=0;j--)
			{
				long long tt=abs(x-L[l].x2)+abs(y-L[l].y2);
				if(kthl[l][j]!=-1&&tt+tl[l][j]<=P[i].t)
				{
					x=kthx[l][j];y=kthy[l][j];
					P[i].t=P[i].t-tt-tl[l][j];
					l=kthl[l][j];
				}
			}
			Ansx[i]=x+dx[L[l].d]*P[i].t;
			Ansy[i]=y+dy[L[l].d]*P[i].t;
			Ansx[i]=mymax(0,mymin(m,Ansx[i]));
			Ansy[i]=mymax(0,mymin(m,Ansy[i]));
		}
	}
}
//main
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&n,&m);
	readline();
	scanf("%d",&q);
	readpoint();
	leftLine();
	rightLine();
	downLine();
	upLine();
	lineAndTime();
	getans();
	for(int i=1;i<=q;i++)printf("%d %d\n",Ansx[i],Ansy[i]);
	return 0;
}