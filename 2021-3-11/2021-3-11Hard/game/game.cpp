#include<bits/stdc++.h>
using namespace std;
long double C(long long n,long long m)
{
	long double ss=1;
	for(long long i=1;i<=m;i++)ss=ss*(n-i+1)/i;
	return ss;
}
long double getans(long long k,long long n)
{
	if(k>0)return getans(k-1,n+1)/k*(n+1)-C(n+k,k)/k;
	else
	{
		if(n>10000000)return log(n)+0.57721566490153286060;
		long double ss=0;
		for(long long i=1;i<=n;i++)ss+=1.0/i;
		return ss;
	}
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	cout.unsetf(ios::fixed);
	cout.setf(ios::scientific);
	cout.precision(9);
	long long n,k;
	cin>>k>>n;
	cout<<getans(k,n)<<endl;
	return 0;
}