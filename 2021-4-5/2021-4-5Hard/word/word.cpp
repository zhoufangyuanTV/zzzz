#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
struct node
{
	int son[26],len,fail;
	long long v;
}tr[1010000];int trlen;
char str[510000];
string a[510000];
int p[510000],y[510000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
int main()
{
	freopen("word.in","r",stdin);
	freopen("word.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s%d",str+1,&y[i]);
		a[i]=str+1;
		p[i]=n-i+1;
	}
	tr[0].fail=-1;
	for(int t=1;t<=n;t++)
	{
		int x=0;
		bool bk=true;
		for(int i=0;i<a[p[t]].length();i++)
		{
			int c=a[p[t]][i]-'a';
			if(tr[x].son[c]==0){bk=false;break;}
			x=tr[x].son[c];
		}
		long long s;
		if(bk)s=y[p[t]]+tr[x].v;
		else s=y[p[t]];
		int last=0;
		for(int i=0;i<a[p[t]].length();i++)
		{
			int c=a[p[t]][i]-'a';
			if(tr[last].son[c]==0)
			{
				tr[last].son[c]=++trlen;
				tr[trlen].len=i+1;
				int pp=tr[last].fail;
				last=trlen;
				while(pp!=-1&&tr[pp].son[c]==0)
				{
					tr[pp].son[c]=trlen;
					pp=tr[pp].fail;
				}
				if(pp!=-1)
				{
					int q=tr[pp].son[c];
					if(tr[pp].len+1!=tr[q].len)
					{
						tr[++trlen]=tr[q];
						tr[trlen].len=tr[pp].len+1;
						while(pp!=-1&&tr[pp].son[c]==q)
						{
							tr[pp].son[c]=trlen;
							pp=tr[pp].fail;
						}
						tr[q].fail=tr[last].fail=trlen;
					}
					else tr[last].fail=q;
				}
			}
			else
			{
				int q=tr[last].son[c];
				if(tr[last].len+1!=tr[q].len)
				{
					tr[++trlen]=tr[q];
					tr[trlen].len=tr[last].len+1;
					int pp=last;
					while(pp!=-1&&tr[pp].son[c]==q)
					{
						tr[pp].son[c]=trlen;
						pp=tr[pp].fail;
					}
					tr[q].fail=trlen;
				}
				last=tr[last].son[c];
			}
			x=last;
			while(x!=-1&&tr[x].v<s)
			{
				tr[x].v=s;
				x=tr[x].fail;
			}
		}
	}
	printf("%lld\n",tr[0].v);
	return 0;
}
