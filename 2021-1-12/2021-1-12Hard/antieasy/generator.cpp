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
int main()
{
    unsigned long long kk,se;
	scanf("%llu",&kk);m=kk;
    __int128_t s;
    do
    {
        se=seed=gen();generate();
        s=(W(')')-W('(')+m)%m;
    }while(p==q||(s+s*b%m*b%m*b%m*b%m)%m!=s*b%m);
    printf("%llu\n",se);
    int i=p,j=q,k=b,l=(s+s*b%m*b%m*b%m)%m,ll=(s*b%m*b%m*b%m*b%m*b%m+s*b%m*b%m*b%m*b%m*b%m*b%m)%m,suk=s;
    printf("%d %d %d %d %d %d\n",i,j,k,l,ll,suk);
    return 0;
}