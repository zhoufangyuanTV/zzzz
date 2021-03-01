#include<cstdio>
#include<cstring>
#include<deque>
#include<vector>
using namespace std;
deque<int> D;
vector<int> Q,S;
int a[1100][1100],b[1100][1100],f[1100],lf[1100],rf[1100];
int p[1100],plen;
bool x[1100];
bool work()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			b[i][a[i][j]]=j;
		}
	}
	p[0]=plen=0;
	for(int i=1;i<=n;i++)f[i]=0;
	for(int i=1;i<=m;i++)
	{
		bool bk=true;
		for(int j=2;j<=n;j++)
		{
			if(f[j]<b[j][a[1][i]])f[j]=b[j][a[1][i]];
			if(i<f[j])bk=false;
		}
		if(bk)p[++plen]=i;
	}
	int ss=1;
	D.clear();
	memset(x,false,sizeof(x));
	for(int i=1;i<=plen;i++)
	{
		if(p[i]>1)ss=ss*2%1000000007;
		if(p[i]-p[i-1]==1)
		{
			if(i>1&&a[1][p[i]]<D.front())D.push_front(a[1][p[i]]);
			else D.push_back(a[1][p[i]]);
		}
		else
		{
			int A=a[1][p[i]],B;
			for(int j=2;j<=n;j++)if(A!=a[j][p[i]])B=a[j][p[i]];
			if(A>B)A^=B^=A^=B;
			Q.clear();S.clear();
			Q.push_back(A);S.push_back(B);
			for(int j=1;j<=n;j++)f[j]=p[i],lf[j]=rf[j]=0;
			bool bk;
			do
			{
				bk=true;
				for(int j=1;j<=n;j++)
				{
					while(lf[j]<Q.size())
					{
						if(f[j]<b[j][Q[lf[j]]])return false;
						while(a[j][f[j]]!=Q[lf[j]])
						{
							if(rf[j]<S.size())
							{
								if(a[j][f[j]]!=S[rf[j]])return false;
							}
							else S.push_back(a[j][f[j]]);
							if(Q.size()+S.size()==p[i]-p[i-1]){bk=false;break;}
							f[j]--;rf[j]++;
						}
						if(bk==false)break;
						f[j]--;lf[j]++;
					}
					while(rf[j]<S.size())
					{
						if(f[j]<b[j][S[rf[j]]])return false;
						while(a[j][f[j]]!=S[rf[j]])
						{
							Q.push_back(a[j][f[j]--]);
							if(Q.size()+S.size()==p[i]-p[i-1]){bk=false;break;}
							lf[j]++;
						}
						if(bk==false)break;
						f[j]--;rf[j]++;
					}
					if(bk==false)break;
				}
			}while(bk);
			for(vector<int>::reverse_iterator it=Q.rbegin();it!=Q.rend();it++)
			{
				D.push_front(*it);
				if(x[*it])return false;
				x[*it]=true;
			}
			for(vector<int>::reverse_iterator it=S.rbegin();it!=S.rend();it++)
			{
				D.push_back(*it);
				if(x[*it])return false;
				x[*it]=true;
			}
			if(i==1)
			{
				for(int j=1;j<=n;j++)
				{
					bool kk=true,kkk=true;int y=m+1;
					for(deque<int>::iterator it=D.begin();it!=D.end();it++)
					{
						if(kk&&y<b[j][*it])kk=false;
						else if(!kk&b[j][*it]<y){kkk=false;break;}
						y=b[j][*it];
					}
					if(kkk==false)return false;
				}
			}
			else
			{
				for(int j=1;j<=n;j++)
				{
					int y=m+1;
					for(vector<int>::iterator it=Q.begin();it!=Q.end();it++){if(y<b[j][*it])return false;y=b[j][*it];}
					y=m+1;
					for(vector<int>::iterator it=S.begin();it!=S.end();it++){if(y<b[j][*it])return false;y=b[j][*it];}
				}
			}
		}
	}
	printf("%d\n",ss);
	while(!D.empty())
	{
		printf("%d",D.front());
		D.pop_front();
		if(D.empty())putchar('\n');
		else putchar(' ');
	}
	return true;
}
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)if(!work())puts("0");
	return 0;
}