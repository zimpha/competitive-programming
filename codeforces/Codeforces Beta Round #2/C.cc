#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

double x[5], y[5], r[5], t[5];

inline double sqr(double x)
{
	return x*x;
}

double check(double tx, double ty)
{
	double ret=0;
	for (int i=0; i<3; i++) t[i]=sqrt(sqr(tx-x[i])+sqr(ty-y[i]))/r[i];
	for (int i=0; i<3; i++) ret+=sqr(t[i]-t[(i+1)%3]);
	return ret;
}

int main()
{
	for (int i=0; i<3; i++) scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
	double nx=(x[0]+x[1]+x[2])/3.0, ny=(y[0]+y[1]+y[2])/3.0;
	bool flag=0;
	for (double d=1; d>1e-6; flag=0)
	{
		double tmp=check(nx, ny);
		if (tmp>check(nx+d, ny)) nx+=d, flag=true;
		else if (tmp>check(nx-d, ny)) nx-=d, flag=true;
		else if (tmp>check(nx, ny+d)) ny+=d, flag=true;
		else if (tmp>check(nx, ny-d)) ny-=d, flag=true;
		if (!flag) d*=0.7;
	}
	if (check(nx, ny)<1e-5) printf("%.5f %.5f\n", nx, ny);
	return 0;
}
