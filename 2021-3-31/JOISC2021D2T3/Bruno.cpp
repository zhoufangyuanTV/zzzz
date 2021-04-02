#include "Bruno.h"
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
namespace {
	int n, a[1010000];
	int cl, cr;
	int ord;
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
	} f[307];
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
	vector<int> re;
	int len;
	int usedA, usedB;
	BigInt lutte(vector<int> g)
	{
		if(g.size()==0)return BigInt();
		BigInt ss;
		int root=0;
		for(int i=1; i<g.size(); i++) {
			if(g[i]<g[root]) root=i;
		}
		for(int i=0; i<root; i++) ss = ss + f[i]*f[g.size()-i-1];
		return ss +
		       lutte(vector<int>(g.begin(), g.begin()+root) )*f[g.size()-root-1] +
		       lutte(vector<int>(g.begin()+root+1, g.end() ) );
	}
	int gl, gr, G, real;
	int lastQ;
	void send(int pos)
	{
		int p;
		if(pos<gl) p = pos-cl;
		else if(pos==G) p = gl-cl;
		else p = gl-cl+pos-gr;
		for(int i = L2[real-1]-1; i>=0; i--) SendB((p>>i)&1);
		usedB+=L2[real-1];
	}
	int fa[1010000];
	int sta[1010000], top;
	void checkl()
	{
		int i;
		for(i = gl-1; i>=cl; i--) {
			if(a[i]<a[G]) break;
		}
		int x = i+1, ff = gl-i-1;
		if(ff > real*0.47) {
			SendB(false);
			usedB++;
			send(x);
			gl=x;
			real = gl-cl+cr-gr+1;
		}
	}
	void checkr()
	{
		int i;
		for(i = gr+1; i<=cr; i++) {
			if(a[i]<a[G]) break;
		}
		int x = i-1, ff = i-gr-1;
		if(ff > real*0.47) {
			SendB(false);
			usedB++;
			send(x);
			gr=x;
			real = gl-cl+cr-gr+1;
		}
	}
	int du[1010000], siz[1010000];
	queue<int> Q;
	int lastY, LastCnt;
}
void InitB(int N, vector<int> P)
{
	n=N;
	for(int i=0; i<N; i++) a[i]=P[i];
	cl=0;
	cr=n-1;
	ord=0;
	L2[0]=0;
	for(int i=1; i<=20; i++) {
		for(int j = 1<<(i-1); j < 1<<i; j++) L2[j]=i;
	}
	f[0].a[0]=1;
	f[0].len=1;
	for(int i=1; i<=306; i++) {
		for(int j=0; j<i; j++) {
			f[i] = f[i] + f[j]*f[i-j-1];
		}
	}
	usedA=usedB=0;
	lastY=-1;
	LastCnt=0;
}
void ReceiveB(bool y)
{
	usedA++;
	switch(ord) {
	case 0:
		re.push_back(y);
		if(re.size()==3 && re[0]==0 && re[1]==0) {
			len=re[2];
			if(len==0) {
				gl = gr = G = (cl+cr)/2;
				real=n;
				if(real<=306 && f[real].size() <= 300) ord=4;
				else ord=2;
			} else ord=1;
			re.clear();
		} else if(re.size()==4) {
			len = (((re[0]<<1 | re[1])-1)<<2 | re[2]<<1 | re[3])+2;
			ord=1;
			re.clear();
		}
		break;
	case 1:
		re.push_back(y);
		if(re.size()==len) {
			for(int i=0; i<len; i++) {
				int mid = (cl+cr)/2;
				if(re[i]==0) cr = mid-1;
				else cl = mid+1;
			}
			re.clear();
			gl = gr = G = (cl+cr)/2;
			real = cr-cl+1;
			if(len==13) ord=4;
			else {
				if(real<=306 && f[real].size() <= 300) ord=4;
				else ord=2;
			}
		}
		break;
	case 2:
		if(y) {
			if(lastQ<G) gl=lastQ;
			else gr=lastQ;
			G=lastQ;
		} else {
			if(lastQ<G) cl = lastQ+1;
			else cr = lastQ-1;
		}
		real = gl-cl+cr-gr+1;
		if(usedA==18 || (real<=306 && usedB+f[real].size() <= 300) ) ord=4;
	}
	if(ord>1) {
		if(real>306 || usedB+f[real].size() > 300) checkl();
		if(real>306 || usedB+f[real].size() > 300) checkr();
		if(real<=306 && usedB+f[real].size() <= 300) ord=4;
	}
	int i, x, last, g;
	double ff, s1;
	switch(ord) {
	case 2:
		top=0;
		sta[0]=0;
		for(i=cl; i<gl; i++) {
			int last=-1;
			while(top>0 && a[i]<a[sta[top]]) last=sta[top--];
			fa[i]=sta[top];
			sta[++top]=i;
			if(last!=-1) fa[last]=i;
		}
		last=-1;
		while(top>0 && a[G]<a[sta[top]]) last=sta[top--];
		fa[G]=sta[top];
		sta[++top]=G;
		if(last!=-1) fa[last]=G;
		for(i=gr+1; i<=cr; i++) {
			last=-1;
			while(top>0 && a[i]<a[sta[top]]) last=sta[top--];
			fa[i]=sta[top];
			sta[++top]=i;
			if(last!=-1) fa[last]=i;
		}
		for(i=cl; i<gl; i++) du[i]=siz[i]=0;
		du[G]=siz[G]=0;
		for(i=gr+1; i<=cr; i++) du[i]=siz[i]=0;
		for(i=cl; i<gl; i++) du[ fa[i] ]++;
		du[ fa[G] ]++;
		for(i=gr+1; i<=cr; i++) du[ fa[i] ]++;
		for(i=cl; i<gl; i++) {
			if(du[i]==0) Q.push(i);
		}
		if(du[G]==0) Q.push(G);
		for(i=gr+1; i<=cr; i++) {
			if(du[i]==0) Q.push(i);
		}
		while(!Q.empty() ) {
			int x=Q.front();
			Q.pop();
			siz[x]++;
			du[ fa[x] ]--;
			siz[ fa[x] ]+=siz[x];
			if(du[ fa[x] ]==0) Q.push(fa[x]);
		}
		g=x=G;
		ff=-1e9;
		if(usedA<15 && LastCnt<=3 && lastY==y) {
			if(y) s1=0.5;
			else s1=1.5;
		} else {
			s1=0.8;
			LastCnt++;
		}
		while(fa[g]!=0) {
			g=fa[g];
			if(g<G) {
				if(ff<min(double(g-cl), (siz[g]-siz[G])*s1) ) {
					ff=min(double(g-cl), (siz[g]-siz[G])*s1);
					x=g;
				}
			} else {
				if(ff<min(double(cr-g), (siz[g]-siz[G])*s1) ) {
					ff=min(double(cr-g), (siz[g]-siz[G])*s1);
					x=g;
				}
			}
		}
		SendB(true);
		usedB++;
		send(x);
		lastQ=x;
		break;
	case 4:
		if(real>306 || usedB+f[real].size() > 300) SendB(true);
		vector<int> v;
		for(i=cl; i<gl; i++) v.push_back(a[i]);
		v.push_back(a[G]);
		for(i = gr+1; i<=cr; i++) v.push_back(a[i]);
		BigInt S=lutte(v);
		int LastUsed=f[real].size();
		for(i=0; i<LastUsed; i++) {
			int j = i/20, k = i%20;
			SendB((S.a[j]>>k)&1);
		}
	}
	lastY=y;
}