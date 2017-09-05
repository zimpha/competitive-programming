#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef long double real;
const real eps=1e-2;
const real pi=acos(-1);

real dis(real x1, real y1, real x2, real y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

real fgcd(real a, real b)
{
	if (fabs(a)<eps) return b;
	if (fabs(b)<eps) return a;
	return fgcd(b, fmod(a, b));
}

int main()
{
	cout.precision(10);
	real x[3], y[3];
	for (int i=0; i<3; i++) cin >> x[i] >> y[i];
	real a, b, c, r, s, p;
	real A, B, C, n;
	a=dis(x[0], y[0], x[1], y[1]);
	b=dis(x[1], y[1], x[2], y[2]);
	c=dis(x[2], y[2], x[0], y[0]);
	if (c<a) swap(a, c);
	if (c<b) swap(b, c);
	//cout << a << " " << b << " " << c << endl;
	p=0.5*(a+b+c);
	s=sqrt(p*(p-a)*(p-b)*(p-c));
	r=0.25*a*b*c/s;
	//cout << r << endl;
	A=acos(1-0.5*a*a/(r*r))*180/pi;
	B=acos(1-0.5*b*b/(r*r))*180/pi;
	C=360-A-B;
	//C=acos(1-0.5*c*c/(r*r))*180/pi;
	//cout << A << " " << B << " " << " " << C << endl;
	n=360/fgcd(A, fgcd(B, C));
	cout << fixed << 0.5*n*r*r*sin(2*pi/n) << endl;
	return 0;
}
