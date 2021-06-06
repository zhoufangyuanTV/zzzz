#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct point
{
	long long x,y;
}a[110000];
inline bool Ucmp(point x,point y){return x.x==y.x?x.y>y.y:x.x<y.x;}
inline bool Dcmp(point x,point y){return x.x==y.x?x.y<y.y:x.x<y.x;}
inline point operator+(point x,point y){return (point){x.x+y.x,x.y+y.y};}
inline point operator-(point x,point y){return (point){x.x-y.x,x.y-y.y};}
inline long long operator*(point x,point y){return x.x*y.y-y.x*x.y;}
vector<point> Utubao(vector<point> p)
{
	vector<point> re;
	for(int i=0;i<p.size();i++)
	{
		while(re.size()>1&&(re[re.size()-1]-re[re.size()-2])*(p[i]-re[re.size()-2])>=0)re.pop_back();
		re.push_back(p[i]);
	}
	return re;
}
vector<point> Uminkefusiji(vector<point> x,vector<point> y)
{
	vector<point> re;
	int i=0,j=0;
	while(i<x.size()&&j<y.size())
	{
		re.push_back(x[i]+y[j]);
		if(i==x.size()-1&&j==y.size()-1)break;
		else if(i==x.size()-1)j++;
		else if(j==y.size()-1)i++;
		else
		{
			if((x[i+1]-x[i])*(y[j+1]-y[j])>0)j++;
			else i++;
		}
	}
	return re;
}
vector<point> Usolve(int l,int r)
{
	if(l==r)
	{
		vector<point> re;
		re.push_back(a[l]);
		return re;
	}
	int mid=(l+r)/2;
	vector<point> L=Usolve(l,mid),R=Usolve(mid+1,r);
	vector<point> ML,MR;
	point s=(point){0,0};
	for(int i=mid;i>=l;i--)
	{
		s=s+a[i];
		ML.push_back(s);
	}
	s=(point){0,0};
	for(int i=mid+1;i<=r;i++)
	{
		s=s+a[i];
		MR.push_back(s);
	}
	sort(ML.begin(),ML.end(),Ucmp);
	sort(MR.begin(),MR.end(),Ucmp);
	ML=Utubao(ML);
	MR=Utubao(MR);
	ML=Uminkefusiji(ML,MR);
	MR.resize(L.size()+R.size());
	merge(L.begin(),L.end(),R.begin(),R.end(),MR.begin(),Ucmp);
	vector<point> M(ML.size()+MR.size());
	merge(ML.begin(),ML.end(),MR.begin(),MR.end(),M.begin(),Ucmp);
	return Utubao(M);
}
vector<point> Dtubao(vector<point> p)
{
	vector<point> re;
	for(int i=0;i<p.size();i++)
	{
		while(re.size()>1&&(re[re.size()-1]-re[re.size()-2])*(p[i]-re[re.size()-2])<=0)re.pop_back();
		re.push_back(p[i]);
	}
	return re;
}
vector<point> Dminkefusiji(vector<point> x,vector<point> y)
{
	vector<point> re;
	int i=0,j=0;
	while(i<x.size()&&j<y.size())
	{
		re.push_back(x[i]+y[j]);
		if(i==x.size()-1&&j==y.size()-1)break;
		else if(i==x.size()-1)j++;
		else if(j==y.size()-1)i++;
		else
		{
			if((x[i+1]-x[i])*(y[j+1]-y[j])>0)i++;
			else j++;
		}
	}
	return re;
}
vector<point> Dsolve(int l,int r)
{
	if(l==r)
	{
		vector<point> re;
		re.push_back(a[l]);
		return re;
	}
	int mid=(l+r)/2;
	vector<point> L=Dsolve(l,mid),R=Dsolve(mid+1,r);
	vector<point> ML,MR;
	point s=(point){0,0};
	for(int i=mid;i>=l;i--)
	{
		s=s+a[i];
		ML.push_back(s);
	}
	s=(point){0,0};
	for(int i=mid+1;i<=r;i++)
	{
		s=s+a[i];
		MR.push_back(s);
	}
	sort(ML.begin(),ML.end(),Dcmp);
	sort(MR.begin(),MR.end(),Dcmp);
	ML=Dtubao(ML);
	MR=Dtubao(MR);
	ML=Dminkefusiji(ML,MR);
	MR.resize(L.size()+R.size());
	merge(L.begin(),L.end(),R.begin(),R.end(),MR.begin(),Dcmp);
	vector<point> M(ML.size()+MR.size());
	merge(ML.begin(),ML.end(),MR.begin(),MR.end(),M.begin(),Dcmp);
	return Dtubao(M);
}
struct Query{point p;int id;};
vector<Query> UQ,Q,DQ;
inline bool cmp1(Query x,Query y){return x.p.x*y.p.y<y.p.x*x.p.y;}
inline bool cmp2(Query x,Query y){return x.p.y*y.p.x<y.p.y*x.p.x;}
long long Ans[1010000];
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].x,&a[i].y);
	vector<point> U=Usolve(1,n),D=Dsolve(1,n);
	for(int i=1;i<=m;i++)
	{
		Query q;scanf("%lld%lld",&q.p.x,&q.p.y);
		q.id=i;
		if(q.p.x>0)UQ.push_back(q);
		else if(q.p.x<0)DQ.push_back(q);
		else Q.push_back(q);
	}
	point Us=(point){0,0},Uss=(point){0,0},Ds=(point){0,0},Dss=(point){0,0};
	for(int i=1;i<=n;i++)
	{
		if(Us.x>0)Us=(point){0,0};
		Us=Us+a[i];
		if(Us.x<Uss.x)Uss=Us;
		if(Ds.x<0)Ds=(point){0,0};
		Ds=Ds+a[i];
		if(Ds.x>Dss.x)Dss=Ds;
	}
	for(int i=0;i<Q.size();i++)
	{
		if(Q[i].p.y>0)Ans[Q[i].id]=Q[i].p*Uss;
		else Ans[Q[i].id]=Q[i].p*Dss;
	}
	sort(UQ.begin(),UQ.end(),cmp1);
	int j=0;
	for(int i=0;i<UQ.size();i++)
	{
		while(j<U.size()-1&&UQ[i].p*U[j]<UQ[i].p*U[j+1])j++;
		Ans[UQ[i].id]=UQ[i].p*U[j];
	}
	sort(DQ.begin(),DQ.end(),cmp2);
	j=0;
	for(int i=0;i<DQ.size();i++)
	{
		while(j<D.size()-1&&DQ[i].p*D[j]<DQ[i].p*D[j+1])j++;
		Ans[DQ[i].id]=DQ[i].p*D[j];
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}