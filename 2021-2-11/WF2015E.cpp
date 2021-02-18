#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
string ST,S[4100],T[4100],A[4100],B[4100],C[4100];
int len[4100],p[4100];
inline bool cmp(int x,int y){return len[x]<len[y];}
inline bool check(string x,string y)
{
	string::iterator it=x.begin(),jt=y.begin();
	while(it!=x.end()&&jt!=y.end())
	{
		if(*it==*jt)it++;
		jt++;
	}
	return it==x.end();
}
int main()
{
	int n;cin>>n>>ST;
	for(int i=1;i<=n;i++)
	{
		cin>>S[i];
		if(!check(S[i],ST))
		{
			cout<<"impossible\n";
			return 0;
		}
		len[i]=S[i].length();
		p[i]=i;
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)T[i]=S[p[i]];
	int a=0,b=0,c=0;
	for(int i=1;i<=n;i++)
	{
		bool Alpha=check(A[a],T[i]),Beta=check(B[b],T[i]),Gamma=check(C[c],T[i]);
		if(!Alpha&&!Beta)
		{
			cout<<"impossible\n";
			return 0;
		}
		if(!Alpha)
		{
			for(int j=1;j<=c;j++)A[a+j]=C[j];
			a+=c;c=0;B[++b]=T[i];
		}
		else if(!Beta)
		{
			for(int j=1;j<=c;j++)B[b+j]=C[j];
			b+=c;c=0;A[++a]=T[i];
		}
		else if(!Gamma)
		{
			for(int j=1;j<=c;j++)B[b+j]=C[j];
			b+=c;c=0;A[++a]=T[i];
		}
		else C[++c]=T[i];
	}
	for(int i=1;i<=c;i++)A[a+i]=C[i];a+=c;
	cout<<a<<' '<<b<<endl;
	for(int i=1;i<=a;i++)cout<<A[i]<<endl;
	for(int i=1;i<=b;i++)cout<<B[i]<<endl;
	return 0;
}