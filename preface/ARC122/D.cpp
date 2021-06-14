#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int son[2];
}tr[12010000];int len;
int a[410000];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
int solve(int l,int r,int k)
{
	if(l>r)return 0;
	if(k<0)return 0;
	int mid;
	for(mid=l;mid<=r;mid++)if(a[mid]>>k&1)break;
	if(mid-l&1)
	{
		len=0;
		tr[0].son[0]=tr[0].son[1]=0;
		for(int i=l;i<mid;i++)
		{
			int x=0;
			for(int j=k-1;j>=0;j--)
			{
				int c=a[i]>>j&1;
				if(tr[x].son[c]==0)
				{
					tr[x].son[c]=++len;
					tr[len].son[0]=tr[len].son[1]=0;
				}
				x=tr[x].son[c];
			}
		}
		int ss=0x3fffffff;
		for(int i=mid;i<=r;i++)
		{
			int x=0,s=1<<k;
			for(int j=k-1;j>=0;j--)
			{
				int c=a[i]>>j&1;
				if(tr[x].son[c]==0)
				{
					x=tr[x].son[c^1];
					s^=1<<j;
				}
				else x=tr[x].son[c];
			}
			ss=mymin(ss,s);
		}
		return ss;
	}
	else return mymax(solve(l,mid-1,k-1),solve(mid,r,k-1));
}
int main()
{
	int n;scanf("%d",&n);n*=2;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	printf("%d\n",solve(1,n,29));
	return 0;
}