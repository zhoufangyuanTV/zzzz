#pragma GCC optimize(3)
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<cmath>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
int _2p[210000];
int n,block,blen;
long long a[310000],c[310000],bl[310000],blk[1100],mx[1100];
multiset<int> S;
void work()
{
	register int M=*S.rbegin(),ss=0,pp=n;
	while(M>0)
	{
		register int l=1,p=pp;
		while(l<p)
		{
			int mid=(l+p)/2;
			if(blk[bl[mid]-1]+c[mid]<M)l=mid+1;
			else p=mid;
		}
		pp=0;
		register int s=blk[bl[p]-1]+c[p];
		for(register int i=p;bl[p]==bl[i];i--)if(a[i]<=s-M){pp=i;break;}
		if(pp==0)
		{
			register int i;
			for(i=bl[p]-1;i>=1;i--)if(mx[i]<=s-M)break;
			register int end=(i-1)*block+1;
			if(i>0)for(register int j=i*block;j>=end;j--)if(a[j]<=s-M){pp=j;break;}
		}
		ss=(ss+1ll*_2p[pp+1]*(_2p[p-pp]+998244352))%998244353;
		M-=s-blk[bl[pp]-1]-c[pp];
	}
	printf("%d\n",ss);
}
int main()
{
	freopen("imperishable.in","r",stdin);
	freopen("imperishable.out","w",stdout);
	int Num;
	scanf("%d%d",&Num,&n);
	_2p[0]=1;
	for(int i=1;i<=n;i++)_2p[i]=_2p[i-1]*2%998244353;
	block=Num==25?800:sqrt(n);blen=(n-1)/block+1;
	for(int i=1;i<=n;i++)bl[i]=(i-1)/block+1;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		S.insert(a[i]);
	}
	memset(blk,0,sizeof(blk));
	for(int i=1;i<=n;i++)
	{
		c[i]=a[i];blk[bl[i]]+=a[i];
		if(i%block!=1)c[i]+=c[i-1];
	}
	for(int i=2;i<=blen;i++)blk[i]+=blk[i-1];
	memset(mx,63,sizeof(mx));
	for(int i=1;i<=n;i++)if(a[i]<mx[bl[i]])mx[bl[i]]=a[i];
	work();
	int t;scanf("%d",&t);
	while(t--)
	{
		int x,y;scanf("%d%d",&x,&y);
		S.erase(S.find(a[x]));S.insert(y);
		register int g=y-a[x];
		for(register int i=x;bl[x]==bl[i];i++)c[i]+=g;
		for(register int i=bl[x];i<=blen;i++)blk[i]+=g;
		a[x]=y;mx[bl[x]]=0x3f3f3f3f;
		register int end=bl[x]*block;if(end>n)end=n;
		for(register int i=(bl[x]-1)*block+1;i<=end;i++)if(a[i]<mx[bl[i]])mx[bl[i]]=a[i];
		work();
	}
	return 0;
}