#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int son[26],fail,manacher;
}tr[810000];int len;
char a[51000];
void bt(int k)
{
	int n=strlen(a+1),x=0;
	for(int i=k;i<=n;i++)
	{
		int c=a[i]-'A';
		if(tr[x].son[c]==0)
		{
			tr[x].son[c]=++len;
			x=tr[x].son[c];
			bool bk=true;
			for(int j=k;j<=k+(i-k+1)/2-1;j++)if(a[j]!=a[i-j+k]){bk=false;break;}
			tr[x].manacher=bk;
		}
		else
		{
			x=tr[x].son[c];
			if(tr[x].manacher)tr[x].manacher++;
		}
	}
}
int list[810000];
void getfail()
{
	int head=1,tail=1;
	for(int i=0;i<26;i++)
	{
		int y=tr[0].son[i];
		if(y!=0)
		{
			tr[y].fail=0;
			list[tail++]=y;
		}
	}
	while(head<tail)
	{
		int x=list[head];
		for(int i=0;i<26;i++)
		{
			int y=tr[x].son[i];
			if(y==0)tr[x].son[i]=tr[tr[x].fail].son[i];
			else
			{
				tr[y].fail=tr[tr[x].fail].son[i];
				tr[y].manacher+=tr[tr[y].fail].manacher;
				list[tail++]=y;
			}
		}
		head++;
	}
}
char b[51000];
int main()
{
	scanf("%s%s",a+1,b+1);
	int n=strlen(a+1),m=strlen(b+1);
	len=0;memset(tr,0,sizeof(tr));
	for(int i=1;i<=n;i++)bt(i);
	getfail();
	long long ss=0;int j=0;
	for(int i=1;i<=m;i++)
	{
		int c=b[i]-'A';
		j=tr[j].son[c];
		ss=ss+tr[j].manacher;
	}
	printf("%lld\n",ss);
	return 0;
}