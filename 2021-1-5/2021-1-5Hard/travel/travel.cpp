#include<cstdio>
#include<vector>
#include<algorithm>
#include"travel.h"
using namespace std;
int tot[1100];
struct node{int siz,p;}a[1100];
inline bool cmp(node x,node y){return x.siz<y.siz;}
int weiyi[1100];
void solve(int n,int limA,int limB)
{
	tot[1]=n;
	for(int i=2;i<=n;i++)tot[i]=find(1,i);
	for(int i=1;i<=n;i++)a[i]=(node){tot[i]-1,i};
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<n;i++)
	{
		int j;
		for(j=i+1;j<n;j++)if(tot[a[i].p]<=a[j].siz)break;
		for(;j<n;j++)if(1==check(1,a[j].p,vector<int>{a[i].p}))break;
		report(a[i].p,a[j].p);
		a[j].siz-=tot[a[i].p];
		node f=a[j];
		int k;
		for(k=j-1;k>i;k--)
		{
			if(f.siz<a[k].siz)a[k+1]=a[k];
			else break;
		}
		a[k+1]=f;
	}
}