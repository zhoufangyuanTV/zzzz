#include "jumps.h"
#include <vector>
#include <utility>
#include <algorithm>
namespace {
	using namespace std;
	struct node {
		int l, r, lc, rc, c;
		vector<int> cc;
	} tr[410000];
	int trlen;
	int a[210000];
	inline bool cmp(int x, int y)
	{
		return a[x]<a[y];
	}
	inline int mymax(int x, int y)
	{
		return a[x]>a[y] ? x : y;
	}
	inline void update(int x)
	{
		int lc=tr[x].lc, rc=tr[x].rc;
		tr[x].c=mymax(tr[lc].c, tr[rc].c);
		tr[x].cc=tr[lc].cc;
		tr[x].cc.insert(tr[x].cc.end(),
						lower_bound(tr[rc].cc.begin(), tr[rc].cc.end(), tr[lc].cc.back(), cmp),
						tr[rc].cc.end() );
	}
	void bt(int l, int r)
	{
		int now=++trlen;
		tr[now].l=l;
		tr[now].r=r;
		tr[now].lc=tr[now].rc=-1;
		if(l<r) {
			int mid = (l+r)/2;
			tr[now].lc = trlen+1;
			bt(l, mid);
			tr[now].rc = trlen+1;
			bt(mid+1, r);
			update(now);
		} else {
			tr[now].c=l;
			tr[now].cc={l};
		}
	}
	int findmax(int now, int l, int r)
	{
		if(tr[now].l==l && tr[now].r==r) return tr[now].c;
		int lc=tr[now].lc, rc=tr[now].rc;
		int mid = (tr[now].l+tr[now].r)/2;
		if(r<=mid) return findmax(lc, l, r);
		else if(l >= mid+1) return findmax(rc, l, r);
		else return mymax(findmax(lc, l, mid), findmax(rc, mid+1, r) );
	}
	pair<int,int> query(int now, int l, int r,pair<int,int> c)
	{
		if(tr[now].l==l && tr[now].r==r) {
			auto it=upper_bound(tr[now].cc.begin(), tr[now].cc.end(), c.second, cmp);
			if(it==tr[now].cc.end() ) return c;
			else return {c.first+tr[now].cc.end()-it, tr[now].cc.back()};
		}
		int lc=tr[now].lc, rc=tr[now].rc;
		int mid = (tr[now].l+tr[now].r)/2;
		if(r<=mid) return query(lc, l, r, c);
		else if(l >= mid+1) return query(rc, l, r, c);
		else return query(rc, mid+1, r, query(lc, l, mid, c) );
	}
	int findleft(int now, int l, int r, int c)
	{
		if(!cmp(c, tr[now].c) ) return -1;
		if(tr[now].l==tr[now].r) return tr[now].c;
		int lc=tr[now].lc, rc=tr[now].rc;
		int mid = (tr[now].l+tr[now].r)/2;
		if(r<=mid) return findleft(lc, l, r, c);
		else if(l >= mid+1) return findleft(rc, l, r, c);
		else {
			int re=findleft(lc, l, mid, c);
			if(re==-1) re=findleft(rc, mid+1, r, c);
			return re;
		}
	}
	int findright(int now, int l, int r, int c)
	{
		if(!cmp(c, tr[now].c) ) return -1;
		if(tr[now].l==tr[now].r) return tr[now].c;
		int lc=tr[now].lc, rc=tr[now].rc;
		int mid = (tr[now].l+tr[now].r)/2;
		if(r<=mid) return findright(lc, l, r, c);
		else if(l >= mid+1) return findright(rc, l, r, c);
		else {
			int re=findright(rc, mid+1, r, c);
			if(re==-1) re=findright(lc, l, mid, c);
			return re;
		}
	}
	int L[210000], R[210000];
	vector<int> e[210000];
	int z, dep[210000], in[210000], out[210000];
	void dfs(int x)
	{
		in[x]=++z;
		for(int y:e[x]) {
			dep[y] = dep[x]+1;
			dfs(y);
		}
		out[x]=++z;
	}
	inline bool pand(int x, int y)
	{
		return in[x]<=in[y] && in[y]<=out[x];
	}
}
void init(int N, vector<int> H)
{
	for(int i=0; i<N; i++) a[i]=H[i];
	trlen=0;
	bt(0, N-1);
	for(int i=0; i<N; i++) L[i]=findright(1, 0, i, i);
	for(int i=0; i<N; i++) R[i]=findleft(1, i, N-1, i);
	for(int i=0; i<N; i++)
	{
		if(L[i]!=-1 || R[i]!=-1) {
			if(L[i]==-1 || R[i]==-1) e[L[i]+R[i]+1].push_back(i);
			else e[mymax(L[i], R[i])].push_back(i);
		}
	}
	z=0;
	dfs(findmax(1, 0, N-1) );
}
int minimum_jumps(int A, int B, int C, int D)
{
	if(B+1 == C) {
		if(cmp(B, findmax(1, C, D) ) ) return 1;
		else return -1;
	} else {
		int M=findmax(1, B+1, C-1), RM=findmax(1, C, D);
		if(cmp(M, RM) ) {
			int P=findright(1, A, B, RM);
			if(P==-1) {
				int LM=findmax(1, A, B);
				if(cmp(M, LM) ) return 1;
				else {
					if(A>0) {
						int LP=findright(1, 0, A-1, M);
						if(LP==-1) return dep[LM]-dep[M]+1;
						else {
							if(cmp(LP, RM) ) {
								int re=0x3f3f3f3f;
								if(pand(LP, LM) && dep[LM]-dep[LP]+1 < re) re = dep[LM]-dep[LP]+1;
								if(pand(M, LM) && dep[LM]-dep[M]+1 < re) re = dep[LM]-dep[M]+1;
								return re;
							} else {
								if(LP+1 == A) return query(1, B+1, C-1, {0, LM}).first+1;
								else {
									int LLM=findmax(1, LP+1, A-1);
									if(cmp(LLM, LM) ) return query(1, B+1, C-1, {0, LM}).first+1;
									else {
										int RP=findleft(1, B+1, C-1, LLM);
										int re=0x3f3f3f3f;
										if(pand(LLM, LM) && dep[LM]-dep[LLM]+1 < re) re = dep[LM]-dep[LLM]+1;
										if(pand(RP, LM) && dep[LM]-dep[RP] < re) re = dep[LM]-dep[RP];
										return re+query(1, RP, C-1, {0, RP}).first+1;
									}
								}
							}
						}
					} else return dep[LM]-dep[M]+1;
				}
			} else {
				if(P==B) return -1;
				else return query(1, B+1, C-1, {0, findmax(1, P+1, B)}).first+1;
			}
		} else return -1;
	}
}
