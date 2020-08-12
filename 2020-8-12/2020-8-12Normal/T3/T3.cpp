#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int son[26],len,fail,size;
}tr[110000],trb[110000];int trlen,trblen;
char a[51000];
char b[51000];
long long ss;
void dfs(int x,int y)
{
	if(x>1&&y>1)ss=ss+1ll*tr[x].size*trb[y].size;
	for(int i=0;i<26;i++)
	{
		if(tr[x].son[i]&&trb[y].son[i])dfs(tr[x].son[i],trb[y].son[i]);
	}
}
int main()
{
	scanf("%s%s",a+1,b+1);
	int n=strlen(a+1),m=strlen(b+1);
	tr[0].len=0;tr[0].fail=1;tr[0].size=0;
	tr[1].len=-1;tr[1].fail=1;tr[1].size=1;
	int last=1;trlen=1;
	for(int i=1;i<=n;i++)
	{
		while(a[i]!=a[i-tr[last].len-1])last=tr[last].fail;
		int c=a[i]-'A';
		if(tr[last].son[c]==0)
		{
			tr[last].son[c]=++trlen;
			tr[trlen].len=tr[last].len+2;
			if(last==1)tr[trlen].fail=0;
			else
			{
				int k=tr[last].fail;
				while(a[i]!=a[i-tr[k].len-1])k=tr[k].fail;
				tr[trlen].fail=tr[k].son[c];
			}
		}
		int y=tr[last].son[c];
		tr[y].size++;
		last=y;
	}
	for(int i=trlen;i>=2;i--)tr[tr[i].fail].size+=tr[i].size;
	trb[0].len=0;trb[0].fail=1;trb[0].size=0;
	trb[1].len=-1;trb[1].fail=1;trb[1].size=1;
	last=1;trblen=1;
	for(int i=1;i<=m;i++)
	{
		while(b[i]!=b[i-trb[last].len-1])last=trb[last].fail;
		int c=b[i]-'A';
		if(trb[last].son[c]==0)
		{
			trb[last].son[c]=++trblen;
			trb[trblen].len=trb[last].len+2;
			if(last==1)trb[trblen].fail=0;
			else
			{
				int k=trb[last].fail;
				while(b[i]!=b[i-trb[k].len-1])k=trb[k].fail;
				trb[trblen].fail=trb[k].son[c];
			}
		}
		int y=trb[last].son[c];
		trb[y].size++;
		last=y;
	}
	for(int i=trblen;i>=2;i--)trb[trb[i].fail].size+=trb[i].size;
	ss=0;
	dfs(0,0);dfs(1,1);
	printf("%lld\n",ss);
	return 0;
}