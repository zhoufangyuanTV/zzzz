#include "Anna.h"
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
namespace {
	int n, l, r;
	int cl, cr;
	int L2[1048576];
	struct BigInt {
		long long a[31];
		int len;
		BigInt()
		{
			memset(a, 0, sizeof(a) );
			len=0;
		}
		inline int size()
		{
			return (len-1)*20 + L2[ a[len-1] ];
		}
	} f[307], F[307][306];
	BigInt operator+(BigInt x, BigInt y)
	{
		BigInt z;
		z.len=max(x.len, y.len);
		for(int i=0; i<z.len; i++) {
			z.a[i] += x.a[i]+y.a[i];
			z.a[i+1] = z.a[i]>>20;
			z.a[i] = z.a[i]&1048575;
		}
		if(z.a[z.len]>0) z.len++;
		return z;
	}
	BigInt operator-(BigInt x, BigInt y)
	{
		BigInt z;
		z.len=x.len;
		for(int i=0; i<z.len; i++) {
			z.a[i] += x.a[i]-y.a[i];
			if(z.a[i]<0) {
				z.a[i+1]=-1;
				z.a[i]+=1048576;
			}
		}
		while(z.len>0 && z.a[z.len-1]==0) z.len--;
		return z;
	}
	BigInt operator*(BigInt x, BigInt y)
	{
		BigInt z;
		z.len = x.len+y.len-1;
		for(int i=0; i<z.len; i++) {
			for(int j=0; j<=i; j++) {
				z.a[i] += x.a[j]*y.a[i-j];
			}
			z.a[i+1] = z.a[i]>>20;
			z.a[i] = z.a[i]&1048575;
		}
		if(z.a[z.len]>0) z.len++;
		return z;
	}
	bool operator<(BigInt x, BigInt y)
	{
		if(x.len!=y.len) return x.len<y.len;
		for(int i = x.len-1; i>=0; i--) {
			if(x.a[i]!=y.a[i]) return x.a[i]<y.a[i];
		}
		return false;
	}
	bool operator<=(BigInt x, BigInt y)
	{
		if(x.len!=y.len) return x.len<y.len;
		for(int i = x.len-1; i>=0; i--) {
			if(x.a[i]!=y.a[i]) return x.a[i]<y.a[i];
		}
		return true;
	}
	BigInt operator*(BigInt x, int y)
	{
		BigInt z;
		z.len=x.len;
		for(int i=0; i<z.len; i++) {
			z.a[i] += x.a[i]*y;
			z.a[i+1] = z.a[i]>>20;
			z.a[i] = z.a[i]&1048575;
		}
		if(z.a[z.len]>0) z.len++;
		return z;
	}
	void magic(BigInt &x, BigInt y, BigInt &q)
	{
		BigInt z;
		z.len = x.len-y.len+1;
		for(int i=z.len-1; i>=0; i--) {
			x.a[i+y.len-1] += x.a[i+y.len]<<20;
			x.a[i+y.len]=0;
			long long l = x.a[i+y.len-1]/(y.a[y.len-1]+1);
			if(l>0) {
				BigInt yy = y*l;
				yy.a[y.len-1] += yy.a[y.len]<<20;
				for(int j=0; j<y.len; j++) {
					x.a[i+j]-=yy.a[j];
					if(x.a[i+j]<0) {
						x.a[i+j+1]--;
						x.a[i+j]+=1048576;
					}
				}
			}
			z.a[i]=l;
			bool bk=true;
			for(int j=y.len-1; j>=0; j--) {
				if(x.a[i+j]<y.a[j]) {
					bk=false;
					break;
				} else {
					if(y.a[j]<x.a[i+j]) break;
				}
			}
			while(bk) {
				z.a[i]++;
				for(int j=0; j<y.len; j++) {
					x.a[i+j]-=y.a[j];
					if(x.a[i+j]<0) {
						x.a[i+j+1]--;
						x.a[i+j]+=1048576;
					}
				}
				bk=true;
				for(int j=y.len-1; j>=0; j--) {
					if(x.a[i+j]<y.a[j]) {
						bk=false;
						break;
					} else {
						if(y.a[j]<x.a[i+j]) break;
					}
				}
			}
		}
		while(x.len>0 && x.a[x.len-1]==0) x.len--;
		while(z.len>0 && z.a[z.len-1]==0) z.len--;
		q=z;
	}
	bool b[20];
	int usedA, usedB;
	int g[306];
	void finale(int B,int L, int R, BigInt x)
	{
		if(R<=L) return ;
		int N = R-L, ul=0, ur=N-1;
		while(ul<ur) {
			int mid = (ul+ur)/2;
			if(x<F[N][mid]) ur=mid;
			else ul=mid+1;
		}
		if(ur>0) x = x-F[N][ur-1];
		g[L+ur]=B;
		BigInt lx;
		magic(x, f[N-ur-1], lx);
		finale(B+1, L, L+ur, lx);
		finale(B+1, L+ur+1, R, x);
	}
	int gl, gr, G, real;
	int ord;
	vector<int> re;
}
void InitA(int N, int L, int R)
{
	n=N;
	l=L;
	r=R;
	cl=0;
	cr=n-1;
	L2[0]=0;
	for(int i=1; i<=20; i++) {
		for(int j = 1<<(i-1); j < 1<<i; j++) L2[j]=i;
	}
	f[0].a[0]=1;
	f[0].len=1;
	for(int i=1; i<=306; i++) {
		F[i][0] = f[0]*f[i-1];
		for(int j=1; j<i; j++) {
			F[i][j] = F[i][j-1] + f[j]*f[i-j-1];
		}
		f[i]=F[i][i-1];
	}
	int len=0;
	int mid = (cl+cr)/2;
	while(len<13 && (r<mid || mid<l) ) {
		if(r<mid) {
			b[len]=false;
			cr = mid-1;
		} else {
			b[len]=true;
			cl = mid+1;
		}
		len++;
		mid = (cl+cr)/2;
	}
	gl = gr = G = (cl+cr)/2;
	real = cr-cl+1;
	if(len<2) {
		SendA(false);
		SendA(false);
		SendA(len);
		usedA = len+3;
	} else {
		int x = ((len-2)>>2)+1, y = (len-2)&3;
		SendA(x>>1);
		SendA(x&1);
		SendA(y>>1);
		SendA(y&1);
		usedA = len+4;
	}
	for(int i=0; i<len; i++) SendA(b[i]);
	usedB=0;
	if(len==13) ord=3;
	else ord=0;
}
void ReceiveA(bool x)
{
	if(ord==0) {
		if(real<=306 && usedB+f[real].size() <= 300) {
			ord=3;
			re.push_back(x);
		} else {
			if(x) {
				if(usedA<18) ord=1;
				else ord=3;
			} else ord=2;
		}
	} else re.push_back(x);
	usedB++;
	if((ord==1 || ord==2) && re.size()==L2[real-1]) {
		int p=0;
		for(int i=0; i<re.size(); i++) p = p*2 + re[i];
		int pos;
		if(p < gl-cl) pos = cl+p;
		else if(p == gl-cl) pos=G;
		else pos = gr+p-gl+cl;
		if(ord==1) {
			if(l<=pos && pos<=r) {
				SendA(true);
				usedA++;
				if(pos==G) cl=cr=gl=gr=G;
				else if(pos<G) gl=pos;
				else gr=pos;
				G=pos;
			} else {
				SendA(false);
				usedA++;
				if(pos<G) cl=pos+1;
				else cr=pos-1;
			}
		} else {
			if(pos<G) gl=pos;
			else gr=pos;
		}
		real = gl-cl+cr-gr+1;
		ord=0;
		re.clear();
	} else if(ord==3 && re.size()==f[real].size() ) {
		BigInt x;
		x.len = (re.size()+19)/20;
		for(int i=0; i<re.size(); i++) {
			int j = i/20, k = i%20;
			x.a[j] |= re[i]<<k;
		}
		while(x.len>0 && x.a[x.len-1]==0) x.len--;
		finale(1,0,real,x);
	}
}
int Answer()
{
	int x, f=0x3f3f3f3f;
	for(int i=cl; i<gl; i++) {
		if(l<=i && i<=r && g[i-cl]<f) {
			f=g[i-cl];
			x=i;
		}
	}
	if(l<=G && G<=r && g[gl-cl]<f) {
		f=g[gl-cl];
		x=G;
	}
	for(int i = gr+1; i<=cr; i++) {
		if(l<=i && i<=r && g[i-gr+gl-cl]<f) {
			f=g[i-gr+gl-cl];
			x=i;
		}
	}
	return x;
}