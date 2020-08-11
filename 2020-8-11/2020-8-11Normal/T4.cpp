#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110000],b[110000],l[110000],r[110000];
struct node
{
	int x,y;
}Q[110000],QQ[110000];int len,qlen;
int sta[110000],top;bool v[110000];
int c[110000],clen;
void dfs(int x)
{
	sta[++top]=x;v[x]=true;
	for(int i=l[x];i<=r[x];i++)
	{
		if(i<l[i]||r[i]<i)
		{
			if(v[i])
			{
				int y;clen=0;
				do
				{
					y=sta[top--];
					v[y]=false;
					c[++clen]=y;
				}while(y!=i);
				for(int i=1;i<=clen/2;i++)swap(c[i],c[clen-i+1]);
				len++;Q[len].x=c[clen-1];Q[len].y=c[clen];
				for(int i=1;i<=clen/2-1;i++)len++,Q[len].x=c[i],Q[len].y=c[clen-i-1];
				for(int i=1;i<=(clen-1)/2;i++)qlen++,QQ[qlen].x=c[i],QQ[qlen].y=c[clen-i];
				for(int i=1;i<=clen;i++)l[c[i]]=r[c[i]]=c[i];
				return ;
			}
			else dfs(i);
			if(v[x]==false)return ;
		}
	}
	v[x]=false;return ;
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		l[i]=lower_bound(b+1,b+n+1,a[i])-b;
		r[i]=upper_bound(b+1,b+n+1,a[i])-b-1;
	}
	bool bk=true;
	for(int i=1;i<=n;i++)if(i<l[i]||r[i]<i)bk=false;
	if(bk){printf("0\n");return 0;}
	bk=true;len=0;
	for(int i=1;i<=n;i++)
	{
		if(i<l[i]||r[i]<i)
		{
			bool bbk=false;
			for(int j=l[i];j<=r[i];j++)
			{
				if(l[j]<=i&&i<=r[j])
				{
					len++;
					Q[len].x=i;Q[len].y=j;
					swap(l[i],l[j]);
					swap(r[i],r[j]);
					bbk=true;
					break;
				}
			}
			if(bbk==false){bk=false;break;}
		}
	}
	if(bk)
	{
		printf("1\n");
		printf("%d",len);
		for(int i=1;i<=len;i++)printf(" %d %d",Q[i].x,Q[i].y);
		printf("\n");
		return 0;
	}
	qlen=0;top=0;
	for(int i=1;i<=n;i++)
	{
		if(i<l[i]||r[i]<i)dfs(i);
	}
	printf("2\n");
	printf("%d",len);
	for(int i=1;i<=len;i++)printf(" %d %d",Q[i].x,Q[i].y);
	printf("\n");
	printf("%d",qlen);
	for(int i=1;i<=qlen;i++)printf(" %d %d",QQ[i].x,QQ[i].y);
	printf("\n");
	return 0;
}