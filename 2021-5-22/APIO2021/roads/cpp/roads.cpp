#include "roads.h"
#include <vector>
#include <queue>
namespace {
	using namespace std;
	vector< pair<int, int> > e[110000];
	int k;
	long long f[110000], g[110000];
	void dfs(int x, int fa)
	{
		int cnt=0;
		g[x]=0;
		priority_queue<int, vector<int>, greater<int> > Q;
		for(auto i:e[x]) {
			int y=i.first, c=i.second;
			if(y!=fa) {
				dfs(y, x);
				if(g[y]+c < f[y]) g[x] += g[y]+c;
				else {
					cnt++;
					g[x]+=f[y];
					Q.push(g[y]+c-f[y]);
				}
			}
		}
		if(cnt>k) {
			while(cnt>k) {
				g[x]+=Q.top();
				Q.pop();
				cnt--;
			}
		}
		f[x]=g[x];
		if(k<=cnt) {
			while(k<=cnt) {
				f[x]+=Q.top();
				Q.pop();
				cnt--;
			}
		}
	}
}
vector<long long> minimum_closure_costs(int N,
										std::vector<int> U,
										std::vector<int> V,
										std::vector<int> W)
{
	vector<long long> Ans;
	Ans.resize(N);
	for(int i=0; i <= N-2; i++) {
		e[ U[i] ].push_back({V[i], W[i]});
		e[ V[i] ].push_back({U[i], W[i]});
		Ans[0]+=W[i];
	}
	k=1;
	dfs(0, -1);
	Ans[1]=g[0];
	for(k=2; k<N; k++) Ans[k]=0;
	return Ans;
}
