#include"doll.h"
#include<cstring>
using namespace std;
struct node
{
	int lc,rc;
}tr[610000];int trlen;
int a[262144];
int p[262144];
int x;
int bt(int l,int r)
{
	if(r<x)return -1;
	if(l==r)return a[l];
	int now=++trlen;
	int mid=(l+r)/2;
	tr[now].lc=bt(l,mid);
	tr[now].rc=bt(mid+1,r);
	return -now;
}
void create_circuit(int m,vector<int> A)
{
	int n=A.size();
	int len=1,t=-1;
	while(len<=n)len<<=1,t++;
	p[0]=0;
	for(int i=1;i<len;i++)p[i]=p[i>>1]>>1|(i&1)<<t;
	int l=len-n-1;
	x=l;
	int j=0;
	memset(a,-1,sizeof(a));
	for(int i=0;i<len;i++)
	{
		if(l<=p[i])
		{
			if(j==n)a[p[i]]=0;
			else a[p[i]]=A[j++];
		}
	}
	trlen=0;bt(0,len-1);
	vector<int> C,X,Y;
	C.resize(m+1);
	for(int i=0;i<=m;i++)C[i]=-1;
	X.resize(trlen);Y.resize(trlen);
	for(int i=0;i<trlen;i++)X[i]=tr[i+1].lc,Y[i]=tr[i+1].rc;
	answer(C,X,Y);
}
