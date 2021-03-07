#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c,cc,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y,int c,int cc)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;a[len].cc=cc;
	a[len].next=last[x];last[x]=len;
}
int s[110000],t[110000];
void dfs(int x,int fa)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			s[y]=s[x]^a[k].c;
			t[y]=t[x]^a[k].cc;
			dfs(y,x);
		}
	}
}
int main()
{
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c,cc;scanf("%d%d%d%d",&x,&y,&c,&cc);
		ins(x,y,c,cc);ins(y,x,c,cc);
	}
	s[1]=t[1]=0;dfs(1,0);
	for(int i=2;i<=n;i++)s[1]^=s[i],t[1]^=t[i];
	for(int i=2;i<=n;i++)s[i]^=s[1],t[i]^=t[1];
	sort(s+1,s+n+1);sort(t+1,t+n+1);
	bool bk=true;
	for(int i=1;i<=n;i++)if(s[i]!=t[i]){bk=false;break;}
	puts(bk?"YES":"NO");
	return 0;
}