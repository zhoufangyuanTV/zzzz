#include "train.h"
#include <queue>
using namespace std;
vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v)
{
	int n=a.size(), m=u.size();
	vector< vector<int> > e(n);
	for(int i=0; i<m; i++) e[ v[i] ].push_back(u[i]);
	vector<int> d(n);
	for(int i=0; i<m; i++) d[ u[i] ]++;
	queue<int> Q;
	vector<int> re(n);
	int t=n;
	while(t--) {
		fill(re.begin(), re.end(), 0);
		vector<int> p(d);
		for(int i=0; i<n; i++) {
			if(r[i]) {
				Q.push(i);
				p[i]=0;
			} else if(a[i]) p[i]=1;
		}
		while(!Q.empty() ) {
			int x=Q.front();
			Q.pop();
			re[x]=1;
			for(int y:e[x]) {
				p[y]--;
				if(p[y]==0) Q.push(y);
			}
		}
		p=d;
		for(int i=0; i<n; i++) {
			if(!re[i]) {
				Q.push(i);
				p[i]=0;
			} else if(!a[i]) p[i]=1;
		}
		while(!Q.empty() ) {
			int x=Q.front();
			Q.pop();
			r[x]=re[x]=0;
			for(int y:e[x]) {
				p[y]--;
				if(p[y]==0) Q.push(y);
			}
		}
	}
	return re;
}