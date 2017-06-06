#include <bits/stdc++.h>

typedef double flt;

const flt pi = acos(-1.0), eps = 1e-9;

flt k;

flt calc(flt x) {
    flt y = 1 - sqrt(1 - (x - 1) * (x - 1));
    return std::min(y, k * x);
}

flt simpson(flt a, flt b) {
  flt c = (a + b) * 0.5;
  return (calc(a) + 4 * calc(c) + calc(b)) * (b -a) / 6;
}

flt asr(flt a, flt b, flt eps, flt A) {
  flt c = (a + b) * 0.5;
  flt L = simpson(a, c), R = simpson(c, b);
  if (fabs(A - L - R) <= 15 * eps) return L + R + (A - L - R) / 15;
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}

flt asr(flt a, flt b, flt eps) {
  return asr(a, b, eps, simpson(a, b));
}

int main() {
    flt S = 1 - pi / 4;
    for (int n = 2; ; ++n) {
        k = 1.0 / n;
        flt now = asr(0, 1, 1e-9);
        if (now / S < 0.001) {
            std::cout << n << std::endl;
            break;
        }
    }
    return 0;
}
