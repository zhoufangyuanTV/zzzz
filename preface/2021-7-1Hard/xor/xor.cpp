#include<cstdio>
#include<cstring>
using namespace std;
bool a[16384];
int Ans[16384];
inline int mymin(int x,int y){return x<y?x:y;}
int C;
int f[16384],s[16384];
inline int lowbit(int x){return x&-x;}
inline bool pand(int l,int k){return s[l]<s[l+k];}
inline int X(int l,int k,int x)
{
	while(k>0)
	{
		if(pand(l+(x&k),k))l+=x&k;
		else l+=(x&k)^k;
		k>>=1;
	}
	return l;
}
inline int query(int l,int k)
{
	if(k==0)return a[l]&&a[l+1&(1<<C)-1];
	for(int i=0;i<1<<k;i++)
	{
		s[i+1]=s[i]+a[l+i&(1<<C)-1];
		if(a[l+i&(1<<C)-1]&&a[l+(1<<k)+i&(1<<C)-1])return 1<<k;
	}
	if(s[1<<k]==0)return 0;
	f[0]=X(0,1<<k-1,0);
	int ss=0x3f3f3f3f;
	if(a[l+(1<<k)&(1<<C)-1])ss=f[0];
	for(int i=1;i<1<<k;i++)
	{
		f[i]=X(f[i-1]&~((lowbit(i)<<1)-1),lowbit(i),i);
		if(a[l+(1<<k)+i&(1<<C)-1])ss=mymin(ss,i^f[i]);
	}
	if(ss==0x3f3f3f3f)return 0;
	else return ss|1<<k;
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n;scanf("%d%d",&n,&C);
	memset(a,false,sizeof(a));
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		a[x]=true;
	}
	for(int i=0;i<=C-2;i++)
	{
		for(int j=0;j<1<<C;j++)
		{
			int s=query(j,i);
			for(int k=0;k<1<<C;k+=1<<i+1)Ans[(1<<C)-j+k&(1<<C)-1]+=s;
		}
	}
	for(int i=0;i<1<<C-1;i++)Ans[(1<<C-1)-i&(1<<C-1)-1]+=query(i,C-1);
	int m;scanf("%d",&m);
	int s=0;
	for(int i=1;i<=m;i++)
	{
		int x;scanf("%d",&x);
		s=s+x&(1<<C-1)-1;
		printf("%d\n",Ans[s]);
	}
	return 0;
}