#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<vector>
#include<utility>
using namespace std;
char str[310][310];
int slen[310];
vector<int> e[310][310];
int p[310];
struct q{int x;long long h1,h2;};
vector<q> Q[310],QQ;
int cnt[310];
map<pair<long long,long long>,int> M;
set<pair<long long,long long> > S;
struct node
{
	int x,y,c,next,other;
}a[510000];int len,last[110000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[len-1].other=len;
	a[len].other=len-1;
}
int st,ed,z;
int dep[110000];
int list[110000];
bool bd()
{
	memset(dep,-1,(z+1)*4);dep[st]=1;
	int head=1,tail=2;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(a[k].c>0&&dep[y]==-1)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed]!=-1;
}
bool b[110000];
int cur[110000];
inline int mymin(int x,int y){return x<y?x:y;}
int dfs(int x,int f)
{
	if(x==ed)return f;
	if(b[x]==false)return 0;
	int used=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(a[k].c>0&&dep[y]==dep[x]+1&&used<f)
		{
			int tt=dfs(y,mymin(a[k].c,f-used));
			used+=tt;
			a[k].c-=tt;
			a[a[k].other].c+=tt;
			if(used==f)break;
		}
	}
	if(used==0)b[x]=false;
	return used;
}
char Ans[310][310];
char aa[310];
int maxdep,obj;
bool dfs(int i,int j,int k,long long h1,long long h2)
{
	if(obj==0)
	{
		if(S.find(make_pair(h1,h2))==S.end())
		{
			S.insert(make_pair(h1,h2));
			for(int l=1;l<=k;l++)Ans[i][l]=aa[l];
			Ans[i][k+1]='\0';
			return true;
		}
	}
	else
	{
		if(M[make_pair(h1,h2)]==obj)
		{
			S.insert(make_pair(h1,h2));
			for(int l=1;l<=k;l++)Ans[i][l]=aa[l];
			Ans[i][k+1]='\0';
			return true;
		}
	}
	if(k==maxdep)return false;
	for(int l=0;l<e[i][j].size();l++)
	{
		int jj=e[i][j][l];
		long long hh1=(h1*29+str[i][jj]-'a'+1)%100000000000000003ll;
		long long hh2=(h2*31+str[i][jj]-'a'+1)%99999999999999997ll;
		aa[k+1]=str[i][jj];
		bool bk=dfs(i,jj,k+1,hh1,hh2);
		if(bk==true)return true;
	}
	return false;
}
int main()
{
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str[i]+1);
		slen[i]=strlen(str[i]+1);
		memset(p,-1,sizeof(p));
		for(int j=slen[i];j>=1;j--)
		{
			for(int k=1;k<=26;k++)
			{
				if(p[k]!=-1)e[i][j].push_back(p[k]);
			}
			p[str[i][j]-'a'+1]=j;
		}
		for(int j=1;j<=26;j++)
		{
			if(p[j]!=-1)e[i][0].push_back(p[j]);
		}
		Q[i].push_back((q){0,0,0});
		cnt[i]=0;
	}
	st=1;ed=2;z=n+2;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)ins(st,i+2,1);
	int ss=0;
	for(maxdep=1;maxdep<=300;maxdep++)
	{
		for(int j=1;j<=n;j++)
		{
			if(cnt[j]>=n)continue;
			QQ.clear();
			for(int k=0;k<Q[j].size();k++)
			{
				int x=Q[j][k].x;
				long long h1=Q[j][k].h1,h2=Q[j][k].h2;
				for(int l=0;l<e[j][x].size();l++)
				{
					cnt[j]++;
					if(cnt[j]>=n)break;
					int y=e[j][x][l];
					long long hh1=(h1*29+str[j][y]-'a'+1)%100000000000000003ll;
					long long hh2=(h2*31+str[j][y]-'a'+1)%99999999999999997ll;
					QQ.push_back((q){y,hh1,hh2});
				}
				if(cnt[j]>=n)break;
			}
			if(cnt[j]>=n)ins(j+2,ed,1);
			else
			{
				Q[j].resize(QQ.size());
				for(int k=0;k<QQ.size();k++)
				{
					Q[j][k]=QQ[k];
					map<pair<long long,long long>,int>::iterator it=M.find(make_pair(QQ[k].h1,QQ[k].h2));
					if(it==M.end())
					{
						z++;
						M[make_pair(QQ[k].h1,QQ[k].h2)]=z;
						ins(z,ed,1);
						ins(j+2,z,1);
					}
					else ins(j+2,it->second,1);
				}
			}
		}
		while(bd())
		{
			memset(b,true,z+1);
			for(int j=1;j<=z;j++)cur[j]=last[j];
			ss+=dfs(st,0x3f3f3f3f);
		}
		if(ss==n)
		{
			printf("%d\n",maxdep);
			S.insert(make_pair(0,0));
			for(int j=1;j<=n;j++)
			{
				if(cnt[j]<n)
				{
					for(int k=last[j+2];k>0;k=a[k].next)
					{
						int y=a[k].y;
						if(y>n+2&&a[k].c==0){obj=y;break;}
					}
					dfs(j,0,0,0,0);
				}
			}
			obj=0;
			for(int j=1;j<=n;j++)if(cnt[j]>=n)dfs(j,0,0,0,0);
			for(int j=1;j<=n;j++)puts(Ans[j]+1);
			return 0;
		}
	}
	puts("-1");
	return 0;
}