#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[1100];int len,last[1100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
struct trnode
{
	int son[4];
}tr[1100];int trlen;
char s[1100];
int nxt[1100];
int bt(int st,int l,int r)
{
	if(l>r)return st;
	if(s[l]=='[')
	{
		int lst=++trlen;
		ins(st,lst);
		int red=bt(lst,l+1,nxt[l]-1);
		int rst=++trlen;
		ins(red,rst);
		ins(st,rst);
		return bt(rst,nxt[l]+1,r);
	}
	else
	{
		int ed=++trlen;
		if(s[l]=='N')tr[st].son[0]=ed;
		else if(s[l]=='S')tr[st].son[1]=ed;
		else if(s[l]=='E')tr[st].son[2]=ed;
		else if(s[l]=='W')tr[st].son[3]=ed;
		else if(s[l]=='?')
		{
			tr[st].son[0]=ed;
			tr[st].son[1]=ed;
			tr[st].son[2]=ed;
			tr[st].son[3]=ed;
		}
		else
		{
			ins(st,ed);
			int red=++trlen;
			ins(ed,red);
			tr[red].son[0]=st;
			tr[red].son[1]=st;
			tr[red].son[2]=st;
			tr[red].son[3]=st;
		}
		return bt(ed,l+1,r);
	}
}
int sta[1100],top;
char gs[1010000];
bool b[210],bb[210];
int list[1100];
int main()
{
	freopen("walking.in","r",stdin);
	freopen("walking.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	top=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='[')sta[++top]=i;
		else if(s[i]==']')nxt[sta[top--]]=i;
	}
	len=0;memset(last,0,sizeof(last));
	memset(tr,0,sizeof(tr));
	trlen=1;
	int ed=bt(1,1,n);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s",gs+1);
		n=strlen(gs+1);
		memset(b+1,false,trlen);b[1]=true;
		int head=1,tail=2;list[1]=1;
		while(head<tail)
		{
			int x=list[head];
			for(int k=last[x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(b[y]==false)
				{
					b[y]=true;
					list[tail++]=y;
				}
			}
			head++;
		}
		for(int i=1;i<=n;i++)
		{
			int c;
			if(gs[i]=='N')c=0;
			else if(gs[i]=='S')c=1;
			else if(gs[i]=='E')c=2;
			else c=3;
			memset(bb+1,false,trlen);
			int head=1,tail=1;
			for(int j=1;j<=trlen;j++)
			{
				if(b[j]==true)
				{
					int y=tr[j].son[c];
					if(y!=0&&bb[y]==false)bb[y]=true,list[tail++]=y;
				}
			}
			while(head<tail)
			{
				int x=list[head];
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(bb[y]==false)
					{
						bb[y]=true;
						list[tail++]=y;
					}
				}
				head++;
			}
			for(int j=1;j<=trlen;j++)b[j]=bb[j];
			putchar(b[ed]?'1':'0');
		}
		putchar('\n');
	}
	return 0;
}