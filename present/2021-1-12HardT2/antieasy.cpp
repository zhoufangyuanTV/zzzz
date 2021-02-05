#include<ctime>
#include<cstdio>
#include<cstring>
#include<random>
using namespace std;
mt19937_64 gen(time(0));
unsigned long long seed;
inline unsigned long long last_int()
{
	seed^=seed>>27;seed^=seed>>54;
	seed^=seed<<25;seed^=seed<<50;
	seed^=seed>>12;seed^=seed>>24;seed^=seed>>48;
	return seed;
}
unsigned long long m;
int n,q;
char a[1010000];
struct Query{int l,p,pp;}Q[1010000];
char Ans[1010000][5];
int Wa,Wrong[1010000];
namespace myhash
{
	const long long p1=1000000007,p2=1000000009;
	long long base1[1010000],base2[1010000];
	long long h1[1010000],h2[1010000];
	void work()
	{
		base1[0]=base2[0]=1;
		for(int i=1;i<=n;i++)base1[i]=base1[i-1]*131%p1,base2[i]=base2[i-1]*137%p2;
		h1[0]=h2[0]=0;
		for(int i=1;i<=n;i++)h1[i]=(h1[i-1]*131+a[i])%p1,h2[i]=(h2[i-1]*137+a[i])%p2;
		Wa=0;
		for(int i=1;i<=(q+1)/2;i++)
		{
			int l=Q[i].l,p=Q[i].p,pp=Q[i].pp;
			long long s1=(h1[p+l-1]-h1[p-1]*base1[l]%p1+p1)%p1,s2=(h2[p+l-1]-h2[p-1]*base2[l]%p2+p2)%p2;
			long long ss1=(h1[pp+l-1]-h1[pp-1]*base1[l]%p1+p1)%p1,ss2=(h2[pp+l-1]-h2[pp-1]*base2[l]%p2+p2)%p2;
			if(s1!=ss1||s2!=ss2)
			{
				if(Ans[i][1]=='Y')Wrong[++Wa]=i;
			}
		}
	}
}
struct functon
{
	__int128_t a[1010000];
	int len;
};
int main(int argc,char *argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	scanf("%llu%d%d%s",&m,&n,&q,a+1);
	for(int i=1;i<=(q+1)/2;i++)scanf("%d%d%d%s",&Q[i].l,&Q[i].p,&Q[i].pp,Ans[i]+1);
	for(int i=(q+1)/2+1;i<=q;i++)scanf("%d%d%d",&Q[i].l,&Q[i].p,&Q[i].pp);
	myhash::work();
	return 0;
}