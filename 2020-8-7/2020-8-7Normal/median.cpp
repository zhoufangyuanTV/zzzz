#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[12],b[12];
inline int med(int x,int y,int z){return x<y?(z<x?x:y<z?y:z):(x<z?x:z<y?y:z);}
int calc(int n,bool bk)
{
	if(bk)
	{
		for(int i=1;i<n;i++)printf("%d ",b[i]);
		printf("%d\n",b[n]);
	}
	if(n==1)return b[1];
	for(int i=2;i<n;i++)b[i-1]=med(b[i-1],b[i],b[i+1]);
	return calc(n-2,bk);
}
int cnt[12];
int main()
{
	freopen("median.in","r",stdin);
	freopen("median.out","w",stdout);
	int n,k;scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)a[i]=i;
	memset(cnt,0,sizeof(cnt));
	while(1)
	{
		for(int i=1;i<=n;i++)b[i]=a[i];
		cnt[calc(n,false)]++;
		int i;
		for(i=n-1;i>=1;i--)if(a[i]<a[i+1])break;
		if(i==0)break;
		int j;
		for(j=n;j>i;j--)if(a[i]<a[j])break;
		a[i]^=a[j]^=a[i]^=a[j];
		for(int k=i+1;k<=i+(n-i)/2;k++)a[k]^=a[n-k+i+1]^=a[k]^=a[n-k+i+1];
	}
	printf("%d\n",cnt[k]);
	return 0;
}