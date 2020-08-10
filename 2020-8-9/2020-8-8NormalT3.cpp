#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct node
{
	int x,y,next;
}a[510000],fa[510000];int len,flen,last[1010000],flast[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
inline void fins(int x,int y)
{
	flen++;fa[flen].x=x;fa[flen].y=y;
	fa[flen].next=flast[x];flast[x]=flen;
}
int sta[1010000],top;bool v[1010000];
void fKosaraju(int x)
{
	if(v[x])return ;
	v[x]=true;
	for(int k=flast[x];k>0;k=fa[k].next)fKosaraju(fa[k].y);
	sta[++top]=x;
}
int b[1010000];
int Kosaraju(int x)
{
	if(b[x]!=-1)return b[x];
	b[x]=1;b[x&1?x+1:x-1]=0;
	for(int k=last[x];k>0;k=a[k].next)b[x]&=Kosaraju(a[k].y);
	return b[x];
}
void color(int x,int c)
{
	if(v[x])return ;
	v[x]=true;b[x]=c;
	if(b[x&1?x+1:x-1]==c)
	{
		printf("IMPOSSIBLE\n");
		exit(0);
	}
	b[x&1?x+1:x-1]=c^1;
	for(int k=last[x];k>0;k=a[k].next)color(a[k].y,c);
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len=0;flen=0;memset(last,0,sizeof(last));memset(flast,0,sizeof(flast));
	for(int i=1;i<=n;i++)
	{
		int a,b,sa,sb;scanf("%d%d%d%d",&a,&sa,&b,&sb);
		ins(a*2-sa,b*2-1+sb);ins(b*2-sb,a*2-1+sa);
		fins(b*2-1+sb,a*2-sa);fins(a*2-1+sa,b*2-sb);
	}
	top=0;
	memset(v,false,sizeof(v));
	for(int i=1;i<=2*m;i++)fKosaraju(i);
	memset(b,-1,sizeof(b));
	memset(v,false,sizeof(v));
	while(top>0)color(sta[top],Kosaraju(sta[top])),top--;
	bool bk=false;
	for(int i=1;i<=m;i++)
	{
		if(b[i*2-1]==b[i*2]){bk=true;break;}
	}
	if(bk)
	{
		printf("IMPOSSIBLE\n");
		return 0;
	}
	for(int i=1;i<=m;i++)printf("%d\n",b[i*2]);
	return 0;
}