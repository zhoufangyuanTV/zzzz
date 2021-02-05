#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int y,next;
}e[1110000];int len,last[1110000];
inline void ins(int x,int y){len++;e[len].y=y;e[len].next=last[x];last[x]=len;}
int z,in[1110000],out[1110000];
void dfs(int x)
{
	in[x]=++z;
	for(int k=last[x];k>0;k=e[k].next)dfs(e[k].y);
	out[x]=z;
}
char a[1110000];
int p[1110000];
int cnt[210];
int f[1110000],ff[1110000];
int c[31];
inline int lowbit(int x){return x&-x;}
inline void change(int x){while(x<=27)c[x]++,x+=lowbit(x);}
inline int sum(int x){int s=0;while(x>0)s+=c[x],x-=lowbit(x);return s;}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s",a+1);
		int n=strlen(a+1);
		len=0;memset(last,0,sizeof(last));
		p[0]=-1;
		for(int i=1;i<=n;i++)
		{
			int k=p[i-1];
			while(k!=-1&&a[k+1]!=a[i])k=p[k];
			p[i]=k+1;
			ins(k+1,i);
		}
		z=0;dfs(0);
		memset(cnt,-1,sizeof(cnt));int s=0;
		for(int i=1;i<=n;i++)
		{
			cnt[a[i]]=-cnt[a[i]];
			s+=cnt[a[i]];
			f[i]=s;
		}
		memset(cnt,-1,sizeof(cnt));s=0;
		for(int i=n;i>=1;i--)
		{
			cnt[a[i]]=-cnt[a[i]];
			s+=cnt[a[i]];
			ff[i]=s;
		}
		memset(c,0,sizeof(c));
		long long ss=0;
		for(int i=2;i<n;i++)
		{
			change(f[i-1]+1);
			int l=1,r=(n-1)/i;
			while(l<r)
			{
				int mid=(l+r+1)/2;
				if(in[i*(mid-1)]<=in[i*mid]&&out[i*mid]<=out[i*(mid-1)])l=mid;
				else r=mid-1;
			}
			ss=ss+1ll*sum(ff[i*l+1]+1)*((l+1)/2);
			ss=ss+1ll*sum(ff[i*(l-1)+1]+1)*(l/2);
		}
		printf("%lld\n",ss);
	}
	return 0;
}