long long f[100000007];
int Ans1,Ans2,Ans3;
int A[10010000];
void init(int n,int *a)
{
	f[1]=1;
	for(register int i=2;i<=100000006;i++)f[i]=(100000007-f[100000007%i]*(100000007/i)%100000007)%100000007;
	Ans1=1;
	Ans2=0;
	Ans3=0;
	for(int i=1;i<=n;i++)
	{
		A[i]=a[i];
		Ans2=(Ans2+f[A[i]])%100000007;
		Ans3=(Ans3+f[A[i]]*f[A[i]])%100000007;
	}
}
void modify(int x,int y)
{
	Ans2=(Ans2-f[A[x]]+f[y]+100000007)%100000007;
	Ans3=(Ans3-f[A[x]]*f[A[x]]%100000007+f[y]*f[y]+100000007)%100000007;
	A[x]=y;
}
int query(int op)
{
	if(op==1)return Ans1;
	else if(op==2)return Ans2;
	else return (Ans3-Ans2+100000007)%100000007;
}