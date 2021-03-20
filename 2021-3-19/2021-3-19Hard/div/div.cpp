#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<vector>
using namespace std;
map<int,int> M,MM;
int a[410000],len;
vector<int> vv[210000];
int list[210000];
int main()
{
	freopen("div.in","r",stdin);
	freopen("div.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		int ss=0;
		M.clear();
		for(int i=1;i<=n;i++)
		{
			int c,x;scanf("%d%d",&c,&x);
			M[(x+1)%m]+=c;M[x%m]-=c;
			ss+=c;
		}
		if(ss%m==0)ss=1;
		else ss=0;
		bool bk=true;
		for(int i=0;i<=2*n;i++)vv[i].clear();
		for(map<int,int>::iterator it=M.begin();it!=M.end();it++)
		{
			vv[abs(it->second)].push_back(it->first);
			if(it->second)bk=false;
		}
		if(bk){puts("-1");continue;}
		MM=M;
		int head=1,tail=1,tt=1;
		for(int i=2*n+1;i>=2;i--)
		{
			len=0;
			for(int j=0;j<vv[i].size();j++)list[tt++]=vv[i][j];
			head=1;tail=tt;int v=MM.size()-vv[0].size();
			while(head<tail)
			{
				int x=list[head];
				int c=M[x];
				if(abs(c)<i){head++;continue;}
				a[++len]=x;
				a[++len]=(x+1)%m;
				M[x]%=i;
				if(c%i==0)v--;
				bool bbk=abs(M[(x+1)%m])<i;
				bool kb=M[(x+1)%m]!=0;
				M[(x+1)%m]+=(c-c%i)/i;
				v+=(M[(x+1)%m]!=0)-kb;
				if(bbk&&abs(M[(x+1)%m])>=i)list[tail++]=(x+1)%m;
				head++;
			}
			if(v==0)ss++;
			else if(M.size()==m)
			{
				bk=true;bool bbk=true;
				for(map<int,int>::iterator it=M.begin();it!=M.end();it++)
				{
					if(it->second!=i-1)bk=false;
					if(it->second!=1-i)bbk=false;
					if(!bk&&!bbk)break;
				}
				if(bk||bbk)ss++;
			}
			for(int i=1;i<=len;i++)M[a[i]]=MM[a[i]];
		}
		printf("%d\n",ss);
	}
	return 0;
}