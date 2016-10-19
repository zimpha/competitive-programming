#include <bits/stdc++.h>
using namespace std;

typedef long double flt;

flt rect(int a, int b){
  if(a==0 || b==0) return 0;
  flt a2=a*a,a3=a*a*a;
  flt b2=b*b,b3=b*b*b;
  flt sqab=sqrt(a2+b2);
  return (a3/b2+b3/a2+sqab*(3-a2/b2-b2/a2)+2.5*(b2/a*log((a+sqab)/b)+a2/b*log((b+sqab)/a)))/15*a2*b2;
}

flt rect_a(int h, int w1, int w2) {
  return ldexp(rect(w1+w2, h) - (rect(w1, h) + rect(w2, h)), -1);
}

flt rect_d(int a, int b, int w, int h) {
  return ldexp(rect_a(b+h, a, w) - (rect_a(b, a, w) + rect_a(h, a, w)), -1);
}

double run(int n) {
  flt ret = 0;
  for (int x = 1; x <= n - 2; ++x) {
    for (int y = 1; y <= n - 2; ++y) {
      for (int s = 1; s + x < n; ++s) {
        for (int t = 1; t + y < n; ++t) {
          flt tmp = rect(n, n);
          tmp -= rect_d(s, t, x, y) * 2;
          tmp -= rect_a(y, s, x) * 2;
          tmp -= rect_d(s, n - t - y, x, y) * 2;
          tmp -= rect_a(x, t, y) * 2;
          tmp -= rect_a(x, n - t - y, y) * 2;
          tmp -= rect_d(n - s - x, t, x, y) * 2;
          tmp -= rect_a(y, n - s - x, x) * 2;
          tmp -= rect_d(n - s - x, n - t - y, x, y) * 2;
          tmp -= rect(x, y);
          tmp /= (n * n - x * y) * (n * n - x * y);
          ret += tmp;
        }
      }
    }
  }
  return ret;
}

int main() {
  printf("%.4f\n", run(3));
  printf("%.4f\n", run(4));
  printf("%.4f\n", run(40));
  return 0;
}
