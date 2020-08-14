#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int son[26],len,fail,last;
}tr[1010000];int trlen;
int a[110000];
int main()
{
	int n,sig;scanf("%d%d",&n,&sig);
	trlen=1;memset(tr,0,sizeof(tr));
	tr[1].len=-1;tr[1].fail=1;tr[1].last=0;
	tr[0].len=0;tr[0].fail=1;tr[0].last=0;
	long long ss=0;int j=1;a[0]=-1;
	for(int i=1;i<=n;i++)
	{
		long long x;scanf("%lld",&x);
		if(sig==1)x^=ss;a[i]=x;
		while(a[i]!=a[i-tr[j].len-1])j=tr[j].fail;
		if(tr[j].son[x]==0)
		{
			tr[j].son[x]=++trlen;
			tr[trlen].len=tr[j].len+2;
			if(j==1)tr[trlen].fail=0;
			else
			{
				int k=tr[j].fail;
				while(j>1&&a[i]!=a[i-tr[k].len-1])k=tr[k].fail;
				tr[trlen].fail=tr[k].son[x];
			}
		}
		j=tr[j].son[x];
		tr[j].last++;
		int k=j;
		while(k>1)ss+=1ll*tr[k].len*tr[k].last,k=tr[k].fail;
		printf("%lld\n",ss);
	}
	return 0;
}