#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long double ldb;
class Complex {
public:
	ldb r, i;
	Complex() {}
	Complex(ldb r = 0, ldb i = 0) : r(r), i(i) {}
	Complex operator + (const Complex &rhs) {return Complex(r + rhs.r, i + rhs.i);}
	Complex operator - (const Complex &rhs) {return Complex(r - rhs.r, i - rhs.i);}
	Complex operator * (const Complex &rhs) {return Complex(r * rhs.r - i * rhs.i, r * rhs.i + i * rhs.r);}
};

class FFT {
private:
	int arrange(vector<Complex> &A) {
		int n = A.size();
		for (int i = 0, j = 0, k; i < n; ++ i, j |= k) {
			if (j > i) swap(A[i], A[j]);
			for (k = n; j & (k >>= 1); j &= (~k));
		}
		return n;
	}
public:
	void trans(vector<Complex> &A, int o) {//o = -1 inverse
		int n = arrange(A);
		const ldb PI = acos(-1);
		for (int step = 1; step < n; step <<= 1) {
			for (int k = 0; k < step; ++ k) {
				Complex w(cos(PI * k / step), o * sin(PI * k / step));
				for (int i = k, j; j = i + step, i < n; i += (step << 1)) {
					Complex t = w * A[j];
					A[j] = A[i] - t;
					A[i] = A[i] + t;
				}
			}
		}
		if (o < 0) {
			for (int i = 0; i < n; ++ i) A[i].r /= n;
		}
	}
} FFT;

const int MAXN = 300000 + 10, M = 100000, L = 5;
long long ret[MAXN];
char s1[MAXN], s2[MAXN];
int base[10];

void get(vector<Complex> &A, char *s) {
	int a = 0, p = 0, l = 0;
	for (int i = strlen(s) - 1; i >= 0; -- i) {
		a += (s[i] - '0') * base[p ++];
		if (p == L) A[l ++] = Complex(a, 0), a = p = 0;
	}
	if (a) A[l ++] = Complex(a, 0);
}

int main() {
	for (int i = 0; i < 10; ++ i) base[i] = i ? base[i - 1] * 10 : 1;
	int T; scanf("%d", &T);
	while (T --) {
		scanf("%s%s", s1, s2);
		int l1 = strlen(s1) / L + 1, l2 = strlen(s2) / L + 1, l = 1;
		for (l = 1; l <= (l1 + l2); l <<= 1);
		vector<Complex> A(l, 0), B(l, 0);
		get(A, s1); get(B, s2);
		FFT.trans(A, 1); FFT.trans(B, 1);
		for (int i = 0; i < l; ++ i) A[i] = A[i] * B[i];
		FFT.trans(A, -1);
		for (int i = 0; i < l; ++ i) ret[i] = A[i].r + 0.1;
		for (int i = 0; i < l; ++ i) ret[i + 1] += ret[i] / M, ret[i] %= M;
		while (l > 1 && ret[l - 1] == 0) l --;
		printf("%lld", ret[l - 1]);
		for (int i = l - 2; i >= 0; -- i) printf("%05lld", ret[i]);
		puts("");
	}
	return 0;
}
