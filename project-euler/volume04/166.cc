#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
/*
abcd
efgh
ijkl
mnop
*/
int ok(int a, int b, int c, int d, int e, int g, int i, int k) {
  int s = a + b + c + d, ret = 0;
  int m = s - a - e - i; if (m < 0 || m > 9) return 0;
  int o = s - c - g - k; if (o < 0 || o > 9) return 0;
  int j = s - d - g - m; if (j < 0 || j > 9) return 0;
  int l = s - i - j - k; if (l < 0 || l > 9) return 0;
  for (int f = 0; f < 10; ++f) {
    int h = s - e - f - g; if (h < 0 || h > 9) continue;
    int n = s - b - f - j; if (n < 0 || n > 9) continue;
    int p = s - m - n - o; if (p < 0 || p > 9) continue;
    ret += (s == d + h + l + p) && (s == a + f + k + p);
  }
  return ret;
}

int run(int a, int b, int c, int d) {
  int ret = 0;
  for (int e = 0; e < 10; ++e) {
    for (int i = 0; i < 10; ++i) {
      for (int g = 0; g < 10; ++g) {
        for (int k = 0; k < 10; ++k) {
          ret += ok(a, b, c, d, e, g, i, k);
        }
      }
    }
  }
  return ret;
}

int main() {
  LL ret = 0;
  for (int a = 0; a < 10; ++a) {
    for (int b = 0; b < 10; ++b) {
      for (int c = 0; c < 10; ++c) {
        for (int d = 0; d < 10; ++d) {
          ret += run(a, b, c, d);
        }
      }
    }
  }
  cout << ret << endl;
  return 0;
}
