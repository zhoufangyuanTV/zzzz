#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
using namespace std;
vector<long long> base;
vector<int> aa,an;
map<long long,map<long long,long long> > f;
map<long long,vector<int> > h;
long long g(long long x,long long y)
{
	if(x==1)return 0;
	if(y==1)return 1;
	map<long long,map<long long,long long> >::iterator it=f.find(x);
	if(it!=f.end())
	{
		map<long long,long long>::iterator jt=it->second.find(y);
		if(jt!=it->second.end())return jt->second;
	}
	long long ss=0;
	map<long long,vector<int> >::iterator kt=h.find(x);
	vector<int> a(base.size());
	int k=base.size();
	long long d=1;
	while(k>=0)
	{
		if(k==base.size())
		{
			if(d>1)ss=(ss+g(y,x/d))%998244353;
			k--;
		}
		else
		{
			if(a[k]<kt->second[k])
			{
				a[k]++;
				if(a[k]>0)d*=base[k];
				k++;
			}
			else
			{
				while(a[k]>=0)
				{
					a[k]--;
					if(a[k]>=0)d/=base[k];
				}
				k--;
			}
		}
	}
	return f[x][y]=ss;
}
int main()
{
	freopen("wsm.in","r",stdin);
	freopen("wsm.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		long long n,y;scanf("%lld%lld",&n,&y);
		long long x=n/y;
		base.clear();
		h.clear();
		aa.clear();
		an.clear();
		int cnt=0;
		for(long long i=2;i*i<=n;i++)
		{
			if(n%i==0)
			{
				base.push_back(i);
				aa.push_back(0);
				an.push_back(0);
				while(n%i==0)
				{
					n=n/i;
					an[cnt]++;
				}
				cnt++;
			}
		}
		if(n>1)
		{
			base.push_back(n);
			aa.push_back(0);
			an.push_back(1);
		}
		for(int i=0;i<base.size();i++)aa[i]=0;
		int k=base.size();
		long long d=1;
		while(k>=0)
		{
			if(k==base.size())
			{
				h[d]=aa;
				k--;
			}
			else
			{
				if(aa[k]<an[k])
				{
					aa[k]++;
					if(aa[k]>0)d*=base[k];
					k++;
				}
				else
				{
					while(aa[k]>=0)
					{
						aa[k]--;
						if(aa[k]>=0)d/=base[k];
					}
					k--;
				}
			}
		}
		if(x==1&&y==1)puts("1");
		else printf("%lld\n",(g(x,y)+g(y,x))%998244353);
	}
	return 0;
}