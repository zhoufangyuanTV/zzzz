#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[1010000];
int sa[1010000],rk1[2010000],rk2[2010000],cnt[1010000],f[1010000],h[1010000];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1),m=127;
	int *x=rk1,*y=rk2;
	memset(cnt,0,m*4+4);
	for(int i=1;i<=n;i++)cnt[s[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--)sa[cnt[s[i]]--]=i;
	m=1;x[sa[1]]=1;
	for(int i=2;i<=n;i++)
	{
		if(s[sa[i]]==s[sa[i-1]])x[sa[i]]=m;
		else x[sa[i]]=++m;
	}
	for(int t=1;t<n&&m<n;t*=2)
	{
		int p=0;
		for(int i=n-t+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>t)y[++p]=sa[i]-t;
		memset(cnt,0,m*4+4);
		for(int i=1;i<=n;i++)cnt[f[i]=x[y[i]]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)sa[cnt[f[i]]--]=y[i];
		swap(x,y);
		m=1;x[sa[1]]=1;
		for(int i=2;i<=n;i++)
		{
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+t]==y[sa[i-1]+t])x[sa[i]]=m;
			else x[sa[i]]=++m;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int p=h[x[i-1]]-1;
		if(p<0)p=0;
		while(s[sa[x[i]-1]+p]==s[i+p])p++;
		h[x[i]]=p;
	}
	for(int i=1;i<n;i++)printf("%d ",sa[i]);
	printf("%d\n",sa[n]);
	return 0;
}