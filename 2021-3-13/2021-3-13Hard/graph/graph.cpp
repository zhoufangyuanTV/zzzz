#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n,p;
long long np;
long long ksm(long long x,long long k)
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
long long f(vector<int> N)
{
	if(N.size()==1)return 0;
	long long S=1;
	for(int i=0;i<N.size();i++)S=(S-N[i]*N[i]%p*np%p*np%p+p)%p;
	long long ss=1;
	for(int i=0;i<N.size();i++)
	{
		for(int j=i+1;j<N.size();j++)
		{
			vector<int> Q;Q.resize(N.size()-1);
			for(int k=0;k<i;k++)Q[k]=N[k];
			Q[i]=N[i]+N[j];
			for(int k=i+1;k<j;k++)Q[k]=N[k];
			for(int k=j;k<Q.size();k++)Q[k]=N[k+1];
			ss=(ss+f(Q)*N[i]%p*N[j]%p*2*np%p*np)%p;
		}
	}
	return ss*ksm(S,p-2)%p;
}
vector<int> a;
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d",&n,&p);np=ksm(n,p-2);
	for(int i=1;i<=n;i++)a.push_back(1);
	printf("%lld\n",f(a));
	return 0;
}
