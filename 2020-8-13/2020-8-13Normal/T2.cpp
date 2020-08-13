#include<cstdio>
#include<cstring>
using namespace std;
inline int ch(char c){return c=='A'?0:c=='C'?1:c=='T'?2:3;}
struct node
{
	int son[4],fail,last[16];
}tr[410000];int len;
void bt(int x,char a[])
{
	int n=strlen(a),actg=0;
	for(int i=0;i<n;i++)
	{
		int c=ch(a[i]);
		actg^=1<<c;
		if(tr[x].son[c]==0)
		{
			tr[x].son[c]=++len;
			tr[len].last[actg]=1;
		}
		x=tr[x].son[c];
	}
}
int list[410000];
void getfail()
{
	int head=1,tail=1;
	for(int i=0;i<4;i++)
	{
		int y=tr[0].son[i];
		if(y!=0)list[tail++]=y;
	}
	while(head<tail)
	{
		int x=list[head];
		for(int i=0;i<4;i++)
		{
			int y=tr[x].son[i];
			if(y==0)tr[x].son[i]=tr[tr[x].fail].son[i];
			else
			{
				tr[y].fail=tr[tr[x].fail].son[i];
				for(int j=0;j<16;j++)tr[y].last[j]+=tr[tr[y].fail].last[j];
				list[tail++]=y;
			}
		}
		head++;
	}
}
char a[110000],gtca[11];
int l[4],r[4];
int main()
{
	int t;scanf("%d%s",&t,a+1);
	int n=strlen(a+1);
	len=0;memset(tr,0,sizeof(tr));
	for(int i=1;i<=n;i++)bt(0,a+i);
	getfail();
	while(t--)
	{
		scanf("%s%s",a+1,gtca+1);
		n=strlen(a+1);
		int m=strlen(gtca+1);
		l[0]=l[1]=l[2]=l[3]=0;
		r[0]=r[1]=r[2]=r[3]=1;
		for(int i=1;i<=m;i++)
		{
			if(gtca[i]>='A'&&gtca[i]<='Z')l[ch(gtca[i])]=1;
			else r[ch(gtca[i]-'a'+'A')]=0;
		}
		int j=0;long long ss=0;
		for(int i=1;i<=n;i++)
		{
			int c=ch(a[i]);
			j=tr[j].son[c];
			for(int w=l[0];w<=r[0];w++)
			{
				for(int x=l[1];x<=r[1];x++)
				{
					for(int y=l[2];y<=r[2];y++)
					{
						for(int z=l[3];z<=r[3];z++)
						{
							ss=ss+tr[j].last[w|x<<1|y<<2|z<<3];
						}
					}
				}
			}
		}
		printf("%lld\n",ss);
	}
	return 0;
}