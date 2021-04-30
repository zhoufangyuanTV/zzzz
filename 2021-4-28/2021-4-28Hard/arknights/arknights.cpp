#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
using namespace std;
#define p 998244353
#define g 3
inline long long ksm(long long x,long long k)
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
struct node
{
	vector<long long> a;
	void ntt(int);
}AA,W;int len;
int R[262144];
long long w[262144];
void node::ntt(int type)
{
	for(int i=0;i<len;i++)if(i<R[i])a[i]^=a[R[i]]^=a[i]^=a[R[i]];
	w[0]=1;
	for(int i=1;i<len;i<<=1)
	{
		long long wi=ksm(g,type*(p-1)/i/2+p-1);
		for(int j=i-2;j>=2;j-=2)w[j]=w[j>>1];
		for(int j=1;j<i;j+=2)w[j]=w[j-1]*wi%p;
		for(int j=0;j<len;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				long long ak=a[j+k],awk=w[k]*a[i+j+k]%p;
				a[j+k]=(ak+awk)%p;a[i+j+k]=(ak-awk+p)%p;
			}
		}
	}
}
long long P[110000],ww[110000];
int Ans[110000];
pair<node,node> solve(int l,int r,node A)
{
	if(l==r)
	{
		if(A.a.size()>0)Ans[l]=A.a[0]*(1-P[l]+p)%p;
		if(A.a.size()>1)Ans[l]=(Ans[l]+A.a[1]*P[l])%p;
		Ans[l]=(Ans[l]+ww[0]*(1-P[l]+p)+ww[1]*P[l])%p;
		node B,C;
		B.a=C.a=vector<long long>{(1-P[l]+p)%p,P[l]};
		return make_pair(B,C);
	}
	int mid=(l+r)/2;
	pair<node,node> BC=solve(l,mid,A);
	len=1;int t=-1;
	while(len<=(r-l+1)*2)len<<=1,t++;
	R[0]=0;
	for(int i=1;i<len;i++)R[i]=R[i>>1]>>1|(i&1)<<t;
	A.a.resize(len);
	AA.a.clear();
	AA.a.resize(len);
	for(int i=0;i<=mid-l+1;i++)AA.a[r-l+1-i]=BC.first.a[i];
	A.ntt(1);AA.ntt(1);
	for(int i=0;i<len;i++)A.a[i]=A.a[i]*AA.a[i]%p;
    //
	W.a.clear();
	W.a.resize(len);
	for(int i=0;i<=r-l+1;i++)W.a[i]=ww[i];
	AA.a.clear();
	AA.a.resize(len);
	for(int i=0;i<=mid-l+1;i++)AA.a[r-l+1-i]=BC.second.a[i];
	W.ntt(1);AA.ntt(1);
	for(int i=0;i<len;i++)A.a[i]=(A.a[i]+W.a[i]*AA.a[i])%p;
	//
	A.ntt(-1);
	long long flen=ksm(len,p-2);
	for(int i=0;i<=r-mid;i++)A.a[i]=A.a[r-l+1+i]*flen%p;
	A.a.resize(r-mid+1);
	pair<node,node> CD=solve(mid+1,r,A);
	//
	len=1;t=-1;
	while(len<=r-l+1)len<<=1,t++;
	R[0]=0;
	for(int i=1;i<len;i++)R[i]=R[i>>1]>>1|(i&1)<<t;
	BC.first.a.resize(len);BC.second.a.resize(len);CD.first.a.resize(len);
	BC.first.ntt(1);BC.second.ntt(1);CD.first.ntt(1);
	for(int i=0;i<len;i++)BC.first.a[i]=BC.first.a[i]*CD.first.a[i]%p,BC.second.a[i]=BC.second.a[i]*CD.first.a[i]%p;
	BC.first.ntt(-1);BC.second.ntt(-1);
	flen=ksm(len,p-2);
	BC.first.a.resize(r-l+2);BC.second.a.resize(r-l+2);
	for(int i=0;i<=r-l+1;i++)BC.first.a[i]=BC.first.a[i]*flen%p,BC.second.a[i]=(BC.second.a[i]*flen+(i<=r-mid?CD.second.a[i]:0))%p;
	return BC;
}
int main()
{
	freopen("arknights.in","r",stdin);
	freopen("arknights.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&P[i]);
	for(int i=0;i<=n;i++)scanf("%lld",&ww[i]);
	node A;
	solve(1,n,A);
	for(int i=1;i<n;i++)printf("%d ",Ans[i]);
	printf("%d\n",Ans[n]);
	return 0;
}
