#include <bits/stdc++.h>
using namespace std;

int run(int n) {
  vector<int> rad(n, 1); rad[0] = 0;
  for (int i = 2; i < n; ++i) if (rad[i] == 1) {
    for (int j = i; j < n; j += i) rad[j] *= i;
  }
  vector<int> id(n);
  for (int i = 0; i < n; ++i) id[i] = i;
  sort(id.begin(), id.end(), [&](int a, int b) {
    return rad[a] < rad[b] || (rad[a] == rad[b] && a < b);
  });
  int ret = 0;
  for (int c = 1; c < n; ++c) {
    int rc = rad[c];
    for (auto a: id) if (a < c && a) {
      if (rad[a] * rc >= c) break;
      int b = c - a;
      if (b <= a || __gcd(a, b) != 1) continue;
      if (1ll * rad[a] * rad[b] * rad[c] < c) ret += c;
    }
  }
  return ret;
}

int main() {
  cout << run(1000) << endl;
  cout << run(120000) << endl;
  return 0;
}
