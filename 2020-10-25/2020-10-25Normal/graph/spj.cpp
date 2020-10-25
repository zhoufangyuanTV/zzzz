#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[510000];int len,last[1100];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
bool b[1100];
int list[1100];
int main()
{
	freopen("graph.in","r",stdin);
	FILE *fp=fopen("graph.out","r");
	int n,m,s,t;scanf("%d%d%d%d",&n,&m,&s,&t);
	int ss;fscanf(fp,"%d",&ss);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		int c;fscanf(fp,"%d",&c);
		ins(x,y,c);ins(y,x,c);
	}
	for(int i=1;i<=ss;i++)
	{
		memset(b,false,sizeof(b));b[s]=true;
		int head=1,tail=2;list[1]=s;
		while(head<tail)
		{
			int x=list[head];
			for(int k=last[x];k>0;k=a[k].next)
			{
				int y=a[k].y;
				if(i!=a[k].c&&b[y]==false)
				{
					if(y==t)
					{
						fclose(fp);
						return 1;
					}
					b[y]=true;
					list[tail++]=y;
				}
			}
			head++;
		}
	}
	fclose(fp);
	return 0;
}