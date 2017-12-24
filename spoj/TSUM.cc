#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef double flt;
typedef complex<flt> Complex;
const flt PI = acos(-1.0);
const int BIAS=20000, MAXN=1<<17;

void FFT(Complex a[], int n, int rev = 1) {
    for (int i=1,j=0,k;i<n;++i) {
        for (k=n>>1;k>(j^=k);k>>=1);
        if (i<j) swap(a[i], a[j]);
    }
    for (int s=1,ss=2;s<n;s<<=1,ss<<=1) {
        Complex wn(cos(2*PI*rev/ss),sin(2*PI*rev/ss)),w;
        for (int i=0,j;i<n;i+=ss) {
            for (j=i,w=1;j<i+s;++j,w*=wn) {
                Complex t=w*a[j+s];
                a[j+s]=a[j]-t; a[j]+=t;
            }
        }
    }
    if (rev==-1) for (int i=0;i<n;++i) a[i]/=n;
}

Complex f1[MAXN], f2[MAXN], f3[MAXN];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < MAXN; ++ i) f1[i] = f2[i] = f3[i] = 0;
    for (int i = 0; i < n; ++ i) {
        int x; scanf("%d", &x); x += BIAS;
        f1[x] = f2[x * 2] = f3[x * 3] = 1;
    }
    FFT(f1, MAXN); FFT(f2, MAXN);
    for (int i = 0; i < MAXN; ++ i) {
        f2[i] *= f1[i];
        f1[i] = f1[i] * f1[i] * f1[i];
    }
    FFT(f1, MAXN, -1); FFT(f2, MAXN, -1);
    for (int i = 0; i < MAXN; ++ i) {
        LL w1 = (LL)(f1[i].real() + 0.5);
        LL w2 = (LL)(f2[i].real() + 0.5);
        LL w3 = (LL)(f3[i].real() + 0.5);
        LL cnt = (w1 - w2 * 3 + w3 * 3) / 6;
        if (cnt) printf("%d : %lld\n", i - BIAS * 3, cnt);
    }
    return 0;
}
