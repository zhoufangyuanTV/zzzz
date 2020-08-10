#include<cstdio>
#include<cstring>
#include<utility>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,c,next;
}a[8010000];int len,last[4010000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long O[4010000],P[4010000],Q[4010000],R[4010000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
inline long long mymin(long long x,long long y){return x<y?x:y;}
void dfs(int x,int fa)
{
	P[x]=0;long long S=0,SS=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			R[y]=(k+1)/2;
			dfs(y,x);
			long long SR=O[y]+a[k].c;
			if(P[y]>P[x])P[x]=P[y];
			if(SR>S)SS=S,S=SR;
			else if(SR>SS)SS=SR;
		}
	}
	P[x]=mymax(P[x],S+SS);
	O[x]=S;
}
void dfs(int x,int fa,long long SSR)
{
	pair<long long,int> S,SS,SSS,PS,PSS;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			long long SR=O[y]+a[k].c;
			if(P[y]>PS.first)PSS=PS,PS=make_pair(P[y],y);
			else if(P[y]>PSS.first)PSS=make_pair(P[y],y);
			if(SR>S.first)SSS=SS,SS=S,S=make_pair(SR,y);
			else if(SR>SS.first)SSS=SS,SS=make_pair(SR,y);
			else if(SR>SSS.first)SSS=make_pair(SR,y);
		}
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			long long QS=mymax(PS.second==y?PSS.first:PS.first,(S.second==y?SS.first:S.first)+SSR);
			if(S.second==y)QS=mymax(QS,SS.first+SSS.first);
			else if(SS.second==y)QS=mymax(QS,S.first+SSS.first);
			else QS=mymax(QS,S.first+SS.first);
			Q[y]=mymax(Q[x],QS);
			dfs(y,x,mymax(SSR,S.second==y?SS.first:S.first)+a[k].c);
		}
	}
}
int main()
{
	freopen("cheese.in","r",stdin);
	freopen("cheese.out","w",stdout);
	int n;read(n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;read(x);read(y);read(c);
		ins(x,y,c);ins(y,x,c);
	}
	dfs(1,0);dfs(1,0,0);
	long long ss=0;
	for(int i=2;i<=n;i++)
	{
		//printf("%lld %lld\n",P[i],Q[i]);
		ss=(ss+mymax(P[i],Q[i])*23333+mymin(P[i],Q[i])*2333+R[i]*R[i]*233+R[i]*23+2)%2333333333333333;
	}
	printf("%lld\n",ss);
	return 0;
}