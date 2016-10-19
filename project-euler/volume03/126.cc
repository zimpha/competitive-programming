#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int cnt[MAXN];

int C(int a, int b, int c, int n = 1) {
  return 2 * (a * b + b * c + c * a) + 4 * (a + b + c + n - 2) * (n - 1);
}

int run(int m) {
  for (int n = 1; n < MAXN; ++n) {
    if (cnt[n] == m) return n;
  }
  return -1;
}

int main() {
  for (int a = 1; C(a, a, a) < MAXN; ++a) {
    for (int b = a; C(a, a, b) < MAXN; ++b) {
      for (int c = b; C(a, b, c) < MAXN; ++c) {
        for (int n = 1; C(a, b, c, n) < MAXN; ++n) {
          cnt[C(a, b, c, n)]++;
        }
      }
    }
  }
  cout << run(10) << endl;
  cout << run(1000) << endl;
}
