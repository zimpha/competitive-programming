#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef double flt;
const int MAXN = 100000 + 10, SIZE = 1<<18;
const flt PI = acos(-1.0);
int mc[MAXN];
char s[MAXN];

struct Complex {
    flt x,y;
    Complex(flt _x=0,flt _y=0):x(_x),y(_y) {}
    Complex operator +(const Complex &t) const {return Complex(x+t.x,y+t.y);}
    Complex& operator +=(const Complex &t) {x+=t.x,y+=t.y;return *this;}
    Complex operator -(const Complex &t) const {return Complex(x-t.x,y-t.y);}
    Complex& operator -=(const Complex &t) {x-=t.x,y-=t.y;return *this;}
    Complex operator *(const Complex &t) const {return Complex(x*t.x-y*t.y,x*t.y+y*t.x);}
    Complex operator /(const flt &t) const {return Complex(x/t,y/t);}
    Complex& operator /=(const flt &t) {x/=t,y/=t;return *this;}
    flt real() {return x;}
    flt imag() {return y;}
};

Complex A[SIZE], B[SIZE];

void FFT(Complex a[], int n, int rev = 1) {
    for (int i = 1, j = 0, k; i < n; ++ i) {
        for (k = n >> 1; k > (j ^= k); k >>= 1);
        if (i < j) swap(a[i], a[j]);
    }
    for (int s = 1, ss = 2; s < n; s <<= 1, ss <<= 1) {
        Complex wn(cos(2*PI*rev/ss), sin(2*PI*rev/ss)), w, t;
        for (int i = 0, j; i < n; i += ss) {
            for (j = i, w = 1; j < i + s; ++ j, w = w * wn) {
                t = w * a[j + s]; a[j + s] = a[j] - t; a[j] += t;
            }
        }
    }
    if (rev == -1) for (int i = 0; i < n; ++ i) a[i] /= n;
}

int main() {
	scanf("%s", s);
	int N = strlen(s), n = 1;
	while (n < N * 2) n <<= 1;

	for (int i = 0; i < n; ++ i) A[i] = B[i] = 0;
	for (int i = 0; i < N; ++ i) A[i] = B[N - i - 1] = s[i] == 'a';
	FFT(A, n); FFT(B, n);
    for (int i = 0; i < n; ++ i) A[i] = A[i] * B[i];
    FFT(A, n, -1);
	for (int i = 1; i < N; ++ i) mc[i] += (int)(A[N - 1 + i].real() + 0.5);

	for (int i = 0; i < n; ++ i) A[i] = B[i] = 0;
	for (int i = 0; i < N; ++ i) A[i] = B[N - i - 1] = s[i] == 'b';
	FFT(A, n); FFT(B, n);
    for (int i = 0; i < n; ++ i) A[i] = A[i] * B[i];
    FFT(A, n, -1);
	for (int i = 1; i < N; ++ i) mc[i] += (int)(A[N - 1 + i].real() + 0.5);

	for (int i = 0; i < n; ++ i) A[i] = B[i] = 0;
	for (int i = 0; i < N; ++ i) A[i] = B[N - i - 1] = s[i] == 'c';
	FFT(A, n); FFT(B, n);
    for (int i = 0; i < n; ++ i) A[i] = A[i] * B[i];
    FFT(A, n, -1);
	for (int i = 1; i < N; ++ i) mc[i] += (int)(A[N - 1 + i].real() + 0.5);

	int ret = 0;
	for (int i = 1; i < N; ++ i) ret = max(ret, mc[i]);
	printf("%d\n", ret);
	for (int i = 1; i < N; ++ i)
		if (mc[i] == ret) printf("%d ", i);
	puts("");
	return 0;
}

