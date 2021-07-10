#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
long long ss;
int n;
long long x[110],y[110];
void dfs(vector<long long> A)
{
	if(A.size()==1)
	{
		if(A[0]<ss)
		{
			ss=A[0];
			printf("%lld\n",ss);
			for(int i=1;i<n;i++)printf("%d %d\n",x[i],y[i]);
		}
	}
	else
	{
		int k=n-A.size()+1;
		for(int i=0;i<A.size();i++)
		{
			vector<long long> B=A;
			B.erase(B.begin()+i);
			x[k]=A[i];y[k]=0;
			dfs(B);
		}
		for(int i=0;i<A.size();i++)
		{
			for(int j=i+1;j<A.size();j++)
			{
				long long z=(A[i]|A[j])/2;
				vector<long long> B=A;
				B[i]=z;
				B.erase(B.begin()+j);
				x[k]=A[i];y[k]=A[j];
				dfs(B);
			}
		}
	}
}
int main()
{
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int w;scanf("%d%d",&n,&w);
		ss=1ll<<w;
		vector<long long> A;
		A.resize(n);
		for(int i=0;i<n;i++)scanf("%lld",&A[i]);
		dfs(A);
	}
	return 0;
}
