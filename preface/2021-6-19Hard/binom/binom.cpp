#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
struct circle
{
	const int p;
	long long *jc,*fjc;
	long long ksm(long long,long long);
	circle(int prime):p(prime){
		jc=new long long[p];
		fjc=new long long[p];
		jc[0]=1;
		for(int i=1;i<p;i++)jc[i]=jc[i-1]*i%p;
		fjc[p-1]=ksm(jc[p-1],p-2);
		for(int i=p-2;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	}
	~circle(){
		delete []jc;
		delete []fjc;
	}
	long long lucas(long long,long long);
}A(3333373),C(10000019);
long long circle::ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
long long circle::lucas(long long n,long long m)
{
	if(n<m)return 0;
	if(n<p)return jc[n]*fjc[n-m]%p*fjc[m]%p;
	return lucas(n/p,m/p)*lucas(n%p,m%p)%p;
}
inline long double jifen(long long x)
{
	return (x+0.5)*log(x+(long double)0.5)-x+0.41894;
}
int main()
{
	freopen("binom.in","r",stdin);
	freopen("binom.out","w",stdout);
	int t=100;
	while(t--)
	{
		long long w,x,y,z;scanf("%lld%lld%lld%lld",&w,&x,&y,&z);
		if(w-x<x)x=w-x;
		if(y-z<z)z=y-z;
		if(w<=20&&y<=20)
		{
			long long s=1,ss=1;
			for(int i=1;i<=x;i++)s=s*(w-i+1)/i;
			for(int i=1;i<=z;i++)ss=ss*(y-i+1)/i;
			if(s>ss)puts("1");
			else if(s<ss)puts("0");
			else puts("2");
		}
		else
		{
			long double s=0,ss=0;
			if(x<=10000)
			{
				for(long long i=1;i<=x;i++)s+=log(w-i+1)-log(i);
			}
			else s=jifen(w)-jifen(x)-jifen(w-x);
			if(z<=10000)
			{
				for(long long i=1;i<=z;i++)ss+=log(y-i+1)-log(i);
			}
			else ss=jifen(y)-jifen(z)-jifen(y-z);
			if(-1e-3<s-ss&&s-ss<1e-3)
			{
				long long As=A.lucas(w,x),Cs=C.lucas(w,x);
				long long Ass=A.lucas(y,z),Css=C.lucas(y,z);
				if(As==Ass&&Cs==Css&&(As!=0||Cs!=0))
				{
					puts("2");
				}
				else if(s>ss)puts("1");
				else puts("0");
			}
			else if(s<ss)puts("0");
			else puts("1");
		}
	}
	return 0;
}
