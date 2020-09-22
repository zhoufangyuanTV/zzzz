#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long F[51000];
int s[51000];
struct js{long long j;int v;}Q[51000];
inline bool cmp(js x,js y){return x.j<y.j;}
int main()
{
	long long K;int P;scanf("%lld%d",&K,&P);
	int N;scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&s[i]);
	int M;scanf("%d",&M);
	for(int i=1;i<=M;i++)scanf("%lld%d",&Q[i].j,&Q[i].v);
	sort(Q+1,Q+M+1,cmp);
	F[0]=0;F[1]=1%P;int j=1;
	for(long long i=2;i<=K;i++)
	{
		long long x=s[(i-2)%N],y=s[(i-1)%N];
		if(j<=M&&Q[j].j==i-2)x=Q[j].v,j++;
		if(j<=M&&Q[j].j==i-1)y=Q[j].v;
		F[i]=(x*F[i-2]+y*F[i-1])%P;
	}
	for(int i=0;i<K;i++)printf("%lld ",F[i]);
	printf("%lld\n",F[K]);
	return 0;
}