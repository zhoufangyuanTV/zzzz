#include<set>
#include<string>
#include<fstream>
using namespace std;
string a,b;
set<string> s;
int main(int argc,char* argv[])
{
	ifstream fin(argv[1]),fout(argv[2]),fstd(argv[3]);
	ofstream fscore(argv[5]);
	int n;fin>>n;
	int ss,ans;fout>>ss;fstd>>ans;
	if(ss!=ans)
	{
		fscore<<0;
		fin.close();fout.close();fstd.close();fscore.close();
		return 0;
	}
	if(ans==-1)
	{
		fscore<<argv[4];
		fin.close();fout.close();fstd.close();fscore.close();
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		fin>>a;
		fout>>b;
		if(s.insert(b).second==false)
		{
			fscore<<0;
			fin.close();fout.close();fstd.close();fscore.close();
			return 0;
		}
		string::iterator at=a.begin();
		for(string::iterator it=b.begin();it!=b.end();it++)
		{
			while(at!=a.end()&&*at!=*it)at++;
			if(at==a.end())
			{
				fscore<<0;
				fin.close();fout.close();fstd.close();fscore.close();
				return 0;
			}
			at++;
		}
	}
	fscore<<argv[4];
	fin.close();fout.close();fstd.close();fscore.close();
	return 0;
}