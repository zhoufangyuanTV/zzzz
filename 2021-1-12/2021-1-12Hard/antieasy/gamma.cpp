#include<ctime>
#include<random>
using namespace std;
__int128_t m,b,p,q;
mt19937_64 gen(time(NULL));
unsigned long long seed;
inline unsigned long long next_int()
{
	seed=seed^seed>>12;
	seed=seed^seed<<25;
	seed=seed^seed>>27;
	return seed;
}
inline unsigned long long rand_int(unsigned long long l,unsigned long long r)
{
	return next_int()%(r-l+1)+l;
}
void generate()
{
	for(int i=1;i<=10;i++)next_int();
	b=rand_int(1,m-1);
	p=rand_int(1,m-1);
	q=rand_int(1,m-1);
}
inline unsigned long long W(char c){return c=='('?p:q;}
__int128_t ksm(__int128_t x,unsigned long long k)
{
	__int128_t s=1;
	while(k>0)
	{
		if(k&1)s=s*x%m;
		x=x*x%m;
		k>>=1;
	}
	return s;
}
__int128_t f[1010000],fb[1010000];
char a[1010000],ouf[110];
int main(int argc,char* argv[])
{
	sscanf(argv[1],"%llu",&seed);
	puts(argv[1]);
	scanf("%llu",&m);
	int n,q;scanf("%d%d%s",&n,&q,a+1);
	generate();
	fb[0]=1;fb[1]=ksm(b,m-2);
	for(int i=2;i<=n;i++)fb[i]=fb[i-1]*fb[1]%m;
	__int128_t bb=1;f[0]=0;
	for(int i=1;i<=n;i++,bb=bb*b%m)f[i]=(f[i-1]+W(a[i])*bb)%m;
	for(int i=1;i<=q;i++)
	{
		int l,p,pp;scanf("%d%d%d",&l,&p,&pp);
		if(i<=(q+1)/2)scanf("%s",ouf+1);
		__int128_t s=(f[p+l-1]-f[p-1]+m)%m*fb[p-1]%m;
		__int128_t ss=(f[pp+l-1]-f[pp-1]+m)%m*fb[pp-1]%m;
		if(i>(q+1)/2){puts(s==ss?"Yes":"No");continue;}
		if(s==ss)
		{
			if(ouf[1]=='N')puts("Wrong:::::::::::::::::::::::");
			else puts("Yes");
		}
		else
		{
			if(ouf[1]=='Y')puts("Wrong::::::::::::::::::");
			else puts("No");
		}
	}
	return 0;
}