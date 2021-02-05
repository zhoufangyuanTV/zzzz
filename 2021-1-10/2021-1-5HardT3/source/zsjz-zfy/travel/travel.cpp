#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
void solve(int,int,int);
void report(int,int);
int check(int,int,std::vector<int>);
int find(int,int);
int tot[1100];
vector<int> V,Aleph,Alpha,Beta;
int p[1100];
inline bool cmp(int x,int y){return tot[x]<tot[y];}
bool leaf[1100];
void tr(int x,int y,int l,int r)
{
	int result=check(x,y,vector<int>(Aleph.begin()+l,Aleph.begin()+r+1));
	if(result==1)for(int i=l;i<=r;i++)Beta.push_back(Aleph[i]);
	else if(result==2)for(int i=l;i<=r;i++)Alpha.push_back(Aleph[i]);
	else
	{
		int mid=(l+r)/2;
		tr(x,y,l,mid);tr(x,y,mid+1,r);
	}
}
void work(int x,vector<int> N)
{
	int cnt=0;
	for(int y:N)if(!leaf[y])cnt++;
	if(cnt==0)for(int y:N)report(x,y);
	else
	{
		cnt=rand()%cnt;
		for(int y:N)
		{
			if(!leaf[y])
			{
				if(cnt==0){cnt=y;break;}
				cnt--;
			}
		}
		int l=0;
		Aleph=N;
		Alpha.clear();
		Beta.clear();
		tr(x,cnt,0,N.size()-1);
		vector<int> A=Alpha,B=Beta;
		int i;
		for(i=0;i<B.size();i++)if(cnt==B[i])break;
		B.erase(B.begin()+i);
		A.push_back(cnt);
		leaf[cnt]=true;
		work(x,A);
		work(cnt,B);
	}
}
void solve(int n,int limA,int limB)
{
	if(limB==0)
	{
		for(int i=2;i<=n;i++)
		{
			vector<int> vv;
			for(int j=1;j<=n;j++)if(i!=j)vv.push_back(j);
			leaf[i]=2==check(1,i,vv);
		}
		for(int i=2;i<=n;i++)V.push_back(i);
		work(1,V);
	}
	else
	{
		tot[1]=n;
		for(int i=2;i<=n;i++)tot[i]=find(1,i),p[i]=i;
		sort(p+2,p+n+1,cmp);
		for(int i=2;i<=n;i++)
		{
			int siz=tot[p[i]]-1,l=0;
			while(siz>0)
			{
				int r=V.size()-1;
				while(l<r)
				{
					int mid=(l+r)/2;
					if(check(1,p[i],vector<int>(V.begin()+l,V.begin()+mid+1))==2)l=mid+1;
					else r=mid;
				}
				report(V[r],p[i]);
				siz-=tot[V[r]];
				V.erase(V.begin()+r);
			}
			V.push_back(p[i]);
		}
		for(int i:V)report(1,i);
	}
}