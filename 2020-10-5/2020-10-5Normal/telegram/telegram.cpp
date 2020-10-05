#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long a[130000];
int rk[130000],b[130000],bb[130000];
int Ans[510][510];
int main()
{
	freopen("telegram.in","r",stdin);
	freopen("telegram.out","w",stdout);
	int n,m;scanf("%d",&n);m=n*(n-1)/2;
	for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
	sort(a+1,a+m+1);a[0]=0;rk[0]=0;
	memset(b,0,sizeof(b));
	for(int i=1;i<=m;i++)
	{
		if(a[i]==a[i-1])rk[i]=rk[i-1];
		else rk[i]=rk[i-1]+1;
		b[rk[i]]++;
	}
	int ss=0;
	for(int i=3;i<=n;i++)
	{
		for(int j=1;j<=m;j++)bb[j]=b[j];
		long long S=a[1]+a[2]+a[i];
		if(S%2==0)
		{
			S=S/2;
			Ans[ss][1]=S-a[i];
			if(Ans[ss][1]<=0)continue;
			Ans[ss][2]=S-a[2];
			Ans[ss][3]=S-a[1];
			bb[rk[1]]--;
			bb[rk[2]]--;
			bb[rk[i]]--;
			bool bk=true;
			for(int j=3;j<i;j++)
			{
				bb[rk[j]]--;
				Ans[ss][j+1]=a[j]-Ans[ss][1];
				for(int k=2;k<=j;k++)
				{
					int p=lower_bound(a+1,a+m+1,Ans[ss][j+1]+Ans[ss][k])-a;
					if(a[p]!=Ans[ss][j+1]+Ans[ss][k]){bk=false;break;}
					if(bb[rk[p]]==0){bk=false;break;}
					bb[rk[p]]--;
				}
				if(bk==false)break;
			}
			if(bk==false)continue;
			int len=i;
			for(int j=i+1;j<=m;j++)
			{
				if(bb[rk[j]]>0)
				{
					bb[rk[j]]--;
					Ans[ss][++len]=a[j]-Ans[ss][1];
					for(int k=2;k<len;k++)
					{
						int p=lower_bound(a+1,a+m+1,Ans[ss][len]+Ans[ss][k])-a;
						if(a[p]!=Ans[ss][len]+Ans[ss][k]){bk=false;break;}
						if(bb[rk[p]]==0){bk=false;break;}
						bb[rk[p]]--;
					}
					if(bk==false)break;
				}
			}
			if(bk==false)continue;
			if(ss==0){ss++;continue;}
			bk=false;
			for(int i=1;i<=n;i++)
			{
				if(Ans[ss][i]!=Ans[ss-1][i]){bk=true;break;}
			}
			ss+=bk;
		}
	}
	printf("%d\n",ss);
	for(int i=0;i<ss;i++)
	{
		for(int j=1;j<n;j++)printf("%d ",Ans[i][j]);
		printf("%d\n",Ans[i][n]);
	}
	return 0;
}