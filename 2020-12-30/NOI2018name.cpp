#include<cstdio>
#include<cstring>
using namespace std;
struct SAM
{
	int last;
	struct node
	{
		int son[26],len,fail;
	}*tr;int trlen;
	SAM(int len)
	{
		tr=new node[len];
		last=trlen=0;
		tr[0].fail=-1;
	}
	void clear();
	void push_back(int);
}T(2010000),S(1010000);
inline void SAM::clear()
{
	memset(tr,0,sizeof(node)*(trlen+1));
	last=trlen=0;
	tr[0].fail=-1;
}
void SAM::push_back(int c)
{
	tr[last].son[c]=++trlen;
	tr[trlen].len=tr[last].len+1;
	int k=tr[last].fail;
	last=trlen;
	while(k!=-1&&tr[k].son[c]==0)
	{
		tr[k].son[c]=last;
		k=tr[k].fail;
	}
	if(k==-1)tr[last].fail=0;
	else
	{
		int p=tr[k].son[c];
		if(tr[k].len+1==tr[p].len)tr[last].fail=p;
		else
		{
			tr[++trlen]=tr[p];
			tr[trlen].len=tr[k].len+1;
			tr[last].fail=tr[p].fail=trlen;
			while(k!=-1&&tr[k].son[c]==p)
			{
				tr[k].son[c]=trlen;
				k=tr[k].fail;
			}
		}
	}
}
int rt[1010000];
struct node
{
	int l,r,lc,rc;
}tr[19010000];int len;
void bt(int now,int x)
{
	if(tr[now].l==tr[now].r)return ;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)
	{
		if(lc==-1)
		{
			lc=tr[now].lc=++len;
			tr[lc].l=tr[now].l;tr[lc].r=mid;tr[lc].lc=tr[lc].rc=-1;
		}
		bt(lc,x);
	}
	else
	{
		if(rc==-1)
		{
			rc=tr[now].rc=++len;
			tr[rc].l=mid+1;tr[rc].r=tr[now].r;tr[rc].lc=tr[rc].rc=-1;
		}
		bt(rc,x);
	}
}
void merge(int &x,int y)
{
	if(x==-1||y==-1)x+=y+1;
	else
	{
		tr[++len]=tr[x];x=len;
		merge(tr[x].lc,tr[y].lc);
		merge(tr[x].rc,tr[y].rc);
	}
}
int find(int now,int r)
{
	if(now==-1)return -1;
	if(tr[now].l==tr[now].r)return tr[now].l;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return find(lc,r);
	else
	{
		int re=find(rc,r);
		if(re==-1)return find(lc,r);
		return re;
	}
}
int p[1010000];
int list[1010000];
char Ta[1010000];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
	len=0;memset(rt,-1,sizeof(rt));
	char c=getchar();
	while(c<'a'||c>'z')c=getchar();
	while(c>='a'&&c<='z')
	{
		S.push_back(c-'a');
		rt[S.last]=++len;
		tr[len].l=1;tr[len].r=500000;tr[len].lc=tr[len].rc=-1;
		bt(len,S.tr[S.last].len);
		c=getchar();
	}
	memset(p,0,sizeof(p));
	for(int i=1;i<=S.trlen;i++)p[S.tr[i].fail]++;
	int head=1,tail=1;
	for(int i=0;i<=S.trlen;i++)if(p[i]==0)list[tail++]=i;
	while(head<tail)
	{
		int x=list[head];
		if(x!=0)
		{
			merge(rt[S.tr[x].fail],rt[x]);
			p[S.tr[x].fail]--;
			if(p[S.tr[x].fail]==0)list[tail++]=S.tr[x].fail;
		}
		head++;
	}
	int t;scanf("%d",&t);
	while(t--)
	{
		int l,r;
		scanf("%s%d%d",Ta+1,&l,&r);
		T.clear();
		int n=strlen(Ta+1),j=0,jl=0;
		long long ss=0;
		for(int i=1;i<=n;i++)
		{
			int c=Ta[i]-'a';
			while(j!=-1&&S.tr[j].son[c]==0)j=S.tr[j].fail;
			if(j==-1)j=jl=0;
			else
			{
				if(S.tr[j].len<jl)jl=S.tr[j].len;
				j=S.tr[j].son[c];
				jl++;
			}
			while(find(rt[j],r)==-1)j=S.tr[j].fail;
			int k=j,kl=jl;jl=0;
			while(k!=-1)
			{
				int re=find(rt[k],r);
				int len=mymin(kl,S.tr[k].len);
				if(l<=re-len+1)
				{
					if(len>jl)j=k,jl=len;
					break;
				}
				else if(re-l+1>jl)j=k,jl=re-l+1;
				k=S.tr[k].fail;
			}
			T.push_back(c);
			int h=T.tr[T.tr[T.last].fail].len;
			if(h<jl)ss+=i-jl;
			else ss+=i-h;
		}
		printf("%lld\n",ss);
	}
	return 0;
}