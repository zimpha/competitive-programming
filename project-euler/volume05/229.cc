#include <bits/stdc++.h>
using namespace std;
const int N = 2e9 + 1;
bitset<N> S, T;

int run(int n) {
  S.reset();
  for (int a = 1; a * a <= n; ++a) {
    for (int b = 1; b * b <= (n - a * a) / 7; ++b) {
      S[a * a + 7 * b * b] = 1;
    }
  }
  T.reset();
  for (int a = 1; a * a <= n; ++a) {
    for (int b = 1; b * b <= (n - a * a) / 3; ++b) {
      T[a * a + 3 * b * b] = 1;
    }
  }
  S &= T;
  T.reset();
  for (int a = 1; a * a <= n; ++a) {
    for (int b = 1; b * b <= (n - a * a) / 2; ++b) {
      T[a * a + 2 * b * b] = 1;
    }
  }
  S &= T;
  T.reset();
  for (int a = 1; a * a <= n; ++a) {
    for (int b = 1; b * b <= n - a * a; ++b) {
      T[a * a + b * b] = 1;
    }
  }
  S &= T;
  return S.count();
}

int main() {
  cout << run(10000000) << endl;
  cout << run(2000000000) << endl;
  return 0;
}
