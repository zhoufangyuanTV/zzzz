#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 300010

using namespace std;

int n, a[N], qz[N][2], ans, zh, f[N], zc;

int main(){
//	freopen("funny.in", "r", stdin);
	scanf("%d", &n);
	for (int i=1; i<=n; i++){
		scanf("%d", &a[i]);
		qz[i][0]=qz[i-1][0];
		qz[i][1]=qz[i-1][1];
		if (i%2) qz[i][1]+=a[i];
		else qz[i][0]+=a[i];
		zh+=a[i];
	}
	if (n%2==0) ans=max(qz[n][1], qz[n][0]);
	else{
		int l=0, r=n*1000+1, mid; 
		while (l<r-1){
			mid=(l+r)/2;
			int jl=a[1];
			for (int i=1; i<n; i++){
				if (i%2==1){
					if (jl>=mid){
						jl+=a[i+2]-a[i+1];
						jl=max(jl, a[i+2]);
					}
					else jl+=a[i+2]-a[i+1];
				}
			}
			if (jl>=mid) l=mid;
			else r=mid;
		}
		ans=max(ans, qz[n][0]+l);
	}
	printf("%d %d", ans, zh-ans);
	
	return 0;
} 