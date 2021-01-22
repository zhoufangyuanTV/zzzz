#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t[110000],c[110000],in[110000];
int list[110000];
int a[110000],len;
bool b[110000];
int s[110000],slen;
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	int n;scanf("%d",&n);
	memset(in,0,sizeof(in));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t[i]);
		in[t[i]]++;
	}
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	long long ss=0;slen=0;
	int head=1,tail=1;
	for(int i=1;i<=n;i++)if(in[i]==0)list[tail++]=i;
	while(head<tail)
	{
		int x=list[head];
		ss=ss+c[x];
		in[t[x]]--;
		if(in[t[x]]==0)list[tail++]=t[x];
		head++;
	}
	memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		if(b[i]==false&&in[i]>0)
		{
			len=0;int j=i;
			do
			{
				b[j]=true;
				a[++len]=c[j];
				ss=ss+c[j];
				j=t[j];
			}while(j!=i);
			sort(a+1,a+len+1);
			if(len%2==0)
			{
				ss=ss-a[len/2+1];
				s[++slen]=a[len/2+1]-a[len/2];
			}
			else ss=ss-a[len/2+1];
		}
	}
	if(slen>0)
	{
		sort(s+1,s+slen+1);
		for(int i=slen-1;i>=1;i-=2)ss=ss+s[i];
	}
	printf("%lld\n",ss);
	return 0;
}