#include<cstdio>
#include<cstring>
using namespace std;
inline long long gsc(long long x,long long y,long long p){return x*y-(long long)((long double)x*y/p)*p;}
int n;
char a[1010000];
struct Hash
{
	const long long p;
	long long base[1010000];
	long long H[1010000];
	Hash(long long pp):p(pp){};
	void yuchuli(long long bb)
	{
		base[0]=1;
		for(int i=1;i<=n;i++)base[i]=base[i-1]*bb%p;
		H[0]=0;
		for(int i=1;i<=n;i++)H[i]=(H[i-1]*bb+a[i])%p;
	}
	inline long long h(int l,int pos){return (H[pos+l-1]-gsc(H[pos-1],base[l],p)+p)%p;}
}A(1919810114531ll),B(1818551883289ll);
char c[110];
int main()
{
	unsigned long long linshi;scanf("%llu",&linshi);printf("%llu\n",linshi);
	int m;scanf("%d%d%s",&n,&m,a+1);
	printf("%d %d\n%s\n",n,m,a+1);
	A.yuchuli(131);B.yuchuli(93);
	for(int i=1;i<=(m+1)/2;i++)
	{
		int l,p,pp;scanf("%d%d%d%s",&l,&p,&pp,c+1);
		printf("%d %d %d ",l,p,pp,c+1);
		long long hh=A.h(l,p),hhh=A.h(l,pp);
		long long hB=B.h(l,p),hhB=B.h(l,pp);
		bool bk=A.h(l,p)==A.h(l,pp)&&B.h(l,p)==B.h(l,pp);
		if(bk)
		{
			if(c[1]=='N')fprintf(stderr,"%d ?????????????\n",i);
		}
		else
		{
			if(c[1]=='Y')fprintf(stderr,"%d\n",i);
		}
		puts(bk?"Yes":"No");
	}
	for(int i=(m+1)/2+1;i<=m;i++)
	{
		int l,p,pp;scanf("%d%d%d%s",&l,&p,&pp,c+1);
		printf("%d %d %d ",l,p,pp);
		puts(A.h(l,p)==A.h(l,pp)&&B.h(l,p)==B.h(l,pp)?"Yes":"No");
	}
	return 0;
}