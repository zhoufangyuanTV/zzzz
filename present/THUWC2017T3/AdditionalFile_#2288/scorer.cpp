#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn = 10010;
const int maxm = 10010;

int n,m;

int drawer_volume [maxm];

int item_volume [maxn];

int weight [maxn][maxm];

int solution [maxn];

int used [maxm];

int main(int argc,char *args[])
{
	if (argc<=2)
	{
		printf("Parameters not enought, please specify the input file and the output file.");
		return 0;
	}

	FILE *fin = fopen(args[1],"r");
	FILE *fout = fopen(args[2],"r");

	fscanf(fin,"%d%d",&n,&m);
	for (int a=1;a<=n;a++)
		fscanf(fin,"%d",&item_volume[a]);
	for (int a=1;a<=m;a++)
		fscanf(fin,"%d",&drawer_volume[a]);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
			fscanf(fin,"%d",&weight[a][b]);
	
	for (int a=1;a<=n;a++)
		fscanf(fout,"%d",&solution[a]);
	
	for (int a=1;a<=n;a++)
		if (solution[a] < 0 || solution[a] > m)
		{
			printf("The item with id %d is put into the wrong id box.\n",a);
			return 0;
		}
	
	int ans=0;
	for (int a=1;a<=n;a++)
	{
		ans += weight[a][solution[a]];
		used[solution[a]] += item_volume[a];
	}

	for (int a=1;a<=m;a++)
		if (used[a] > drawer_volume[a])
		{
			printf("You put too much item into box %d.\n",a);
			printf("%d\n",used[a]);
			return 0;
		}
	
	printf("Solution is acceptable, and the value you get is %d.\n",ans);
	
	return 0;

}
