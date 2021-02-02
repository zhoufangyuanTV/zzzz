#include <cstdio>
#include <cstring>
using namespace std;
int n, a[110000], b[110000];
int log_2[110000];
int f[110000][17];
inline int mymin(int x, int y)
{
	return x<y ? x : y;
}
void st()
{
	log_2[0]=-1;
	for(int i=1; i<=n; i++) log_2[i] = log_2[i/2]+1;
	for(int i=1; i<=n; i++) f[i][0]=a[i];
	for(int j=1; j<=log_2[n]; j++) {
		for(int i=1; i <= n-(1<<j)+1; i++) f[i][j]=mymin(f[i][j-1], f[i+(1 << j-1)][j-1]);
	}
}
inline int findmin(int l, int r)
{
	int lr=log_2[r-l+1];
	return mymin(f[l][lr], f[r-(1<<lr)+1][lr]);
}
int p[110], plen;
inline int heap(int rt, int x, int R)
{
	int i=1, ss=0x3f3f3f3f;
	for(int l=x, r=x; rt+l <= R; l = l*2, r = r*2 + 1) {
		if(rt+r > R) r = R-rt;
		while(i<=plen && p[i] < rt+l) i++;
		int j = rt+l;
		while(i<=plen && p[i] <= rt+r) {
			if(j<p[i]) ss=mymin(ss, findmin(j, p[i]-1) );
			j = p[i]+1;
			i++;
		}
		if(j <= rt+r) ss=mymin(ss, findmin(j, rt+r) );
	}
	return ss;
}
int A[110000], B[110000], ExA[110000], ExB[110000], C;
int main()
{
	freopen("heap.in", "r", stdin);
	freopen("heap.out", "w", stdout);
	int m;
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++) {
		scanf("%d", &a[i]);
		b[ a[i] ]=i;
	}
	st();
	memset(A, -1, sizeof(A) );
	memset(B, -1, sizeof(B) );
	C=0;
	for(int i=1; i<=m; i++) {
		int opt, rt, R, x;
		scanf("%d%d%d%d", &opt, &rt, &R, &x);
		rt--;
		plen=0;
		if(opt==1) {
			int dep=log_2[x];
			for(int i=0; i<=dep; i++) {
				int now = x >> dep-i;
				int g=heap(rt, now, R);
				for(int j=0; j<i; j++) {
					int pre = now >> i-j;
					if(B[ a[rt+pre] ]!=-1) {
						int re = B[ a[rt+pre] ]-rt;
						if(i<=log_2[re] && re >> log_2[re]-i == now) g=mymin(g, A[rt+re]);
					}
				}
				if(i==dep) {
					printf("%d\n", g);
					break;
				}
				int k;
				for(k=1; k<=plen; k++) {
					if(b[g]<p[k]) break;
				}
				plen++;
				for(int j=plen; j>k; j--) p[j]=p[j-1];
				p[k]=b[g];
				int h = B[g]==-1 ? b[g] : B[g];
				if(A[h]==-1) {
					A[h]=g;
					B[g]=h;
					C++;
					ExA[C]=h;
					ExB[C]=g;
				}
				while(h!=rt+now) {
					int fa = rt+(h-rt >> 1);
					if(A[fa]==-1) {
						A[fa]=a[fa];
						B[ a[fa] ]=fa;
						C++;
						ExA[C]=fa;
						ExB[C]=a[fa];
					}
					int fg=A[fa];
					A[h]^=A[fa]^=A[h]^=A[fa];
					B[g]^=B[fg]^=B[g]^=B[fg];
					h=fa;
				}
			}
		} else {
			A[ b[x] ]=x;
			B[x]=b[x];
			C++;
			ExA[C]=b[x];
			ExB[C]=x;
			for(int i=0; i<=log_2[B[x]-rt]; i++) {
				int now = B[x]-rt >> log_2[B[x]-rt]-i;
				int g=heap(rt, now, R);
				for(int j=0; j<i; j++) {
					int pre = now >> i-j;
					if(B[ a[rt+pre] ]!=-1) {
						int re = B[ a[rt+pre] ]-rt;
						if(i<=log_2[re] && re >> log_2[re]-i == now) g=mymin(g, A[rt+re]);
					}
				}
				if(g==x) {
					printf("%d\n", now);
					break;
				}
				int k;
				for(k=1; k<=plen; k++) {
					if(b[g]<p[k]) break;
				}
				plen++;
				for(int j=plen; j>k; j--) p[j]=p[j-1];
				p[k]=b[g];
				int h = B[g]==-1 ? b[g] : B[g];
				if(A[h]==-1) {
					A[h]=g;
					B[g]=h;
					C++;
					ExA[C]=h;
					ExB[C]=g;
				}
				while(h!=rt+now) {
					int fa = rt+(h-rt >> 1);
					if(A[fa]==-1) {
						A[fa]=a[fa];
						B[ a[fa] ]=fa;
						C++;
						ExA[C]=fa;
						ExB[C]=a[fa];
					}
					int fg=A[fa];
					A[h]^=A[fa]^=A[h]^=A[fa];
					B[g]^=B[fg]^=B[g]^=B[fg];
					h=fa;
				}
			}
		}
		for(int i=1; i<=C; i++) {
			A[ ExA[i] ]=-1;
			B[ ExB[i] ]=-1;
		}
		C=0;
	}
	return 0;
}