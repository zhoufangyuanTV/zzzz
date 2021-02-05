#include<cstdio>
#include<cstring>
using namespace std;
long long f[1010000],a[110];
struct node
{
	int son[26],len,fail;
}tr[1010000];int trlen;
char s[1010000];
inline long long mymin(long long x,long long y){return x<y?x:y;}
int main()
{
	freopen("copy.in","r",stdin);
	freopen("copy.out","w",stdout);
	int n;long long C;scanf("%d%lld",&n,&C);
	f[0]=0;
	for(int i=0;i<26;i++)scanf("%lld",&a[i]);
	tr[0].len=0;tr[0].fail=1;
	tr[1].len=-1;tr[1].fail=1;
	trlen=1;int last=1;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		int c=s[i]-'a';
		while(s[i-tr[last].len-1]!=s[i])last=tr[last].fail;
		if(tr[last].son[c]==0)
		{
			tr[last].son[c]=++trlen;
			tr[trlen].len=tr[last].len+2;
			if(last==1)tr[trlen].fail=0;
			else
			{
				int k=tr[last].fail;
				while(s[i-tr[k].len-1]!=s[i])k=tr[k].fail;
				tr[trlen].fail=tr[k].son[c];
			}
		}
		last=tr[last].son[c];
		if(tr[last].len==1)f[i]=f[i-1]+a[c];
		else f[i]=mymin(f[i-1]+a[c],f[i-tr[last].len/2]+C);
	}
	printf("%lld\n",f[n]);
	return 0;
}
