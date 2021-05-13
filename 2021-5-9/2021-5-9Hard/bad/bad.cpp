#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
class MT_gen {
	const unsigned A = 2567483615u, B = 2636928640u, C = 4022730752u, F = 1812433253u;
	unsigned MT[624], tot;
	unsigned keep(unsigned index) { return index >= 624 ? index - 624 : index; }

public:
	MT_gen(unsigned seed) {
		MT[0] = seed;
		tot = 0;
		for (int i = 1; i < 624; ++i) MT[i] = F * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
	}
	void twist() {
		for (int i = 0; i < 624; ++i) {
			unsigned tmp = (MT[i] & 0x80000000) | (MT[keep(i + 1)] & 0x7fffffff);
			tmp = (tmp & 1) ? (tmp >> 1) ^ A : (tmp >> 1);
			MT[i] = MT[keep(i + 397)] ^ tmp;
		}
	}
	unsigned operator()() {
		if (tot == 0) twist();
		unsigned tmp = MT[tot];
		tmp ^= tmp >> 11;
		tmp ^= tmp << 7 & B;
		tmp ^= tmp << 15 & C;
		tmp ^= tmp >> 18;
		tot = keep(tot + 1);
		return tmp;
	}
};

char c[10000005];
int p;
long long F[1100],f[1100],g[1100];
long long jc[1100];
void chushihua(int n)
{
	memset(F,0,sizeof(F));
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	F[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++)
		{
			F[i]=(F[i]+F[i-j-1]*F[j])%p;
			f[i]=(f[i]+f[i-j-1]*F[j]+F[i-j-1]*f[j]+((i-j-1)*j+i)*F[i-j-1]%p*F[j])%p;
			g[i]=(g[i]+g[i-j-1]*F[j]+F[i-j-1]*g[j]+((i-j-1)*j+i-j-1)*F[i-j-1]%p*F[j])%p;
		}
	}
}
long long solve(int n)
{
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(c[i]==c[j])
			{
				ss=(ss+F[n/2]*jc[n/2]%p*jc[n/2]%p*((p+1)/2))%p;
			}
			else
			{
				if(c[i]==')'&&c[j]=='(')ss=(ss+f[n/2]*jc[n/2-1]%p*jc[n/2-1])%p;
				else ss=(ss+g[n/2]*jc[n/2-1]%p*jc[n/2-1])%p;
			}
		}
	}
	return ss;
}
int main()
{
	freopen("bad.in","r",stdin);
	freopen("bad.out","w",stdout);
	int n,q;
	unsigned seed;
	scanf("%d%d%d%u",&n,&q,&p,&seed);
	MT_gen rnd(seed);
	for (int i = 1; i <= n / 2; ++i) c[i] = '(';
	for (int i = n / 2 + 1; i <= n; ++i) c[i] = ')';
	for (int i = n; i >= 1; --i) swap(c[i], c[rnd() % i + 1]);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	chushihua(n);
	printf("%lld\n",solve(n));
	while(q--)
	{
		int x,y;scanf("%d%d",&x,&y);
		char t=c[x];c[x]=c[y];c[y]=t;
		printf("%lld\n",solve(n));
	}
	return 0;
}
