#include<cstdio>
#include<cstring>
using namespace std;
bool f[141][57][29][15];
int main()
{
	freopen("a.txt","w",stdout);
	memset(f,false,sizeof(f));
	for(int d=0;d<=14;d++)
	{
		for(int c=0;c<=28-d;c++)
		{
			for(int b=0;b<=56-c-d*2;b++)
			{
				for(int a=0;a<=140-b*2-c*3-d*4;a++)
				{
					if(a>=1&&!f[a-1][b][c][d])f[a][b][c][d]=true;
					else if(b>=2&&!f[a][b-2][c][d])f[a][b][c][d]=true;
					else if(c>=3&&!f[a][b][c-3][d])f[a][b][c][d]=true;
					else if(d>=4&&!f[a][b][c][d-4])f[a][b][c][d]=true;
					else if(b>=1&&!f[a+2][b-1][c][d])f[a][b][c][d]=true;
					else if(c>=1&&!f[a+1][b+1][c-1][d])f[a][b][c][d]=true;
					else if(d>=1&&(!f[a+1][b][c+1][d-1]||!f[a][b+2][c][d-1]))f[a][b][c][d]=true;
				}
			}
		}
	}
	for(int d=0;d<=2;d++)
	for(int c=0;c<=1;c++)
	for(int b=0;b<=4;b++)
	for(int a=0;a<=4;a++)
	if(f[a][b][c][d])printf("%d %d %d %d=%d\n",a,b,c,d,a+b*2+c*3+d*4);
	return 0;
}