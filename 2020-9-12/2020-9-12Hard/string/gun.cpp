#include<ctime>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	ofstream out("string.in",ios::out);
	srand(time(0));
	int t=20;out<<t<<endl;
	while(t--)
	{
		int n=15+rand()%2;
		out<<n<<endl;
		int c=rand()%4+1;
		string s;
		for(int i=1;i<=n/2;i++)s+='a'+rand()%c;
		string S(s.rbegin(),s.rend());
		if(n%2==1)s+='a'+rand()%c;
		out<<s+S<<endl;
	}
	return 0;
}