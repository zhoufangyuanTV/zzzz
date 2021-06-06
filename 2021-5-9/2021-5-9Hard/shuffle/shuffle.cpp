#include<cstdio>
#include<cstring>
using namespace std;
inline int mymax(int x,int y){return x>y?x:y;}
inline long long mymin(long long x,long long y){return x<y?x:y;}
char a[110000];
int n,rnxt[110000][2],lnxt[110000][2];
struct seg
{
	int x;
	inline int r(){return x+1;}
	inline int l(){return x>0?x:n;}
	inline seg operator+(int y){return (seg){x+y<n?x+y:x+y-n};}
	inline seg operator-(int y){return (seg){x<y?x-y+n:x-y};}
	inline int rt(int v){return rnxt[x][v];}
	inline int lt(int v){return lnxt[x][v];}
};
inline seg r(int x){return (seg){x<n?x:0};}
inline seg l(int x){return (seg){x-1};}
inline int operator-(seg x,seg y){return x.x<y.x?x.x-y.x+n:x.x-y.x;}
int S,s1[110000];
inline int s(seg l,seg r){return l.x<=r.x?s1[r.x]-s1[l.x]:s1[r.x]-s1[l.x]+S;}
inline bool in(seg l,seg r,int x){return l.x<=r.x?l.x<x&&x<=r.x:l.x<x||x<=r.x;}
inline int calc1(seg A,seg B,seg C)
{
	if(A-C==s(C,A))return 0;
	else if(in(A-S,A,1))
	{
		if(in(C,A,1)&&in(C,r(1),r(C.rt(0)).rt(1)))return A-l(C.rt(0))-1;
		else return A-l(C.rt(0));
	}
	else
	{
		if(in(C,r(1),r(C.rt(0)).rt(1)))return A-l(C.rt(0))-1;
		else return A-l(C.rt(0));
	}
}
inline int calc2(seg A,seg B,seg C)
{
	if(C-(A-S)==s(A-S,C))return 0;
	else if(in(A-S,A,1))
	{
		if(r(1)-r(B.rt(1))==s(r(B.rt(1)),r(1)))return A-S-l(B.rt(1));
		else return A-S-l(B.rt(1))-1;
	}
	else
	{
		if(in(A,l(1),B.rt(1)))
		{
			if(r(1)-r(B.rt(1))==s(r(B.rt(1)),r(1)))return A-S-l(B.rt(1))-1;
			else return A-S-l(B.rt(1))-2;
		}
		else return A-S-l(B.rt(1))-1;
	}
}
int main()
{
	freopen("shuffle.in","r",stdin);
	freopen("shuffle.out","w",stdout);
	scanf("%d%s",&n,a+1);
	bool bk1=true;
	for(int i=2;i<=n;i++)
	{
		if(a[1]!=a[i]){bk1=false;break;}
	}
	if(bk1)
	{
		puts("0");
		return 0;
	}
	rnxt[n][0]=rnxt[n][1]=-1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='0')
		{
			if(rnxt[n][0]==-1)rnxt[n][0]=i;
		}
		else
		{
			if(rnxt[n][1]==-1)rnxt[n][1]=i;
		}
	}
	for(int i=n-1;i>=0;i--)
	{
		if(a[i+1]=='0')rnxt[i][0]=i+1,rnxt[i][1]=rnxt[i+1][1];
		else rnxt[i][1]=i+1,rnxt[i][0]=rnxt[i+1][0];
	}
	lnxt[0][0]=lnxt[0][1]=-1;
	for(int i=n;i>=1;i--)
	{
		if(a[i]=='0')
		{
			if(lnxt[0][0]==-1)lnxt[0][0]=i;
		}
		else
		{
			if(lnxt[0][1]==-1)lnxt[0][1]=i;
		}
	}
	for(int i=1;i<n;i++)
	{
		if(a[i]=='0')lnxt[i][0]=i,lnxt[i][1]=lnxt[i-1][1];
		else lnxt[i][1]=i,lnxt[i][0]=lnxt[i-1][0];
	}
	s1[0]=0;
	for(int i=1;i<=n;i++)s1[i]=s1[i-1]+a[i]-'0';
	S=s1[n];
	int bk2=1;
	for(seg i=l(1);bk2<=n;bk2++,i=i+1)
	{
		if(s(i-S,i)==S)
		{
			printf("%d\n",l(1)-i);
			return 0;
		}
	}
	seg A=l(1);
	seg B=A-S,C=A-S;
	while(in(A,A-S,B.l()))
	{
		seg pB=B-1,pC=C;
		if(a[B.l()]=='1')pC=r(C.rt(0));
		int ps1=calc1(A,pB,pC),ps2=calc2(A,pB,pC);
		if(ps2<=ps1)B=pB,C=pC;
		else break;
	}
	long long ss=n+(l(1)-A)+1ll*n*mymax(calc1(A,B,C),calc2(A,B,C));
	for(A=A-1;A.x!=0;A=A-1)
	{
		C=l(C.lt(0));
		if(in(A-S,A,B.l())&&in(A-S,A,B.r()))
		{
			B=B-1;
			if(a[B.r()]=='1')C=r(C.rt(0));
		}
		while(in(A,A-S,B.l()))
		{
			seg pB=B-1,pC=C;
			if(a[B.l()]=='1')pC=r(C.rt(0));
			int ps1=calc1(A,pB,pC),ps2=calc2(A,pB,pC);
			if(ps2<=ps1)B=pB,C=pC;
			else break;
		}
		if(in(A-S,A,1))ss=mymin(ss,l(1)-A+1ll*n*mymax(calc1(A,B,C),calc2(A,B,C)));
		else ss=mymin(ss,n+(l(1)-A)+1ll*n*mymax(calc1(A,B,C),calc2(A,B,C)));
	}
	printf("%lld\n",ss);
	return 0;
}