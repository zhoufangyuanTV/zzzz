#include"combo.h"
using namespace std;
string guess_sequence(int n)
{
	string S,p="AB";
	if(press(p)==0)
	{
		p="X";
		if(press(p)==0)S="Y";
		else S="X";
	}
	else
	{
		p="A";
		if(press(p)==0)S="B";
		else S="A";
	}
	if(n==1)return S;
	char x,y,z;
	if(S[0]=='A')x='B',y='X',z='Y';
	else if(S[0]=='B')x='A',y='X',z='Y';
	else if(S[0]=='X')x='A',y='B',z='Y';
	else x='A',y='B',z='X';
	for(int i=2;i<n;i++)
	{
		int re=press(S+x+x+S+x+y+S+x+z+S+y);
		if(re==i+1)S+=x;
		else if(re==i)S+=y;
		else S+=z;
	}
	int re=press(S+x);
	if(re==n)return S+x;
	re=press(S+y);
	if(re==n)return S+y;
	return S+z;
}
