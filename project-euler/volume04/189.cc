#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n) {
  vector<int> pw(n + 1, 1);
  for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 3;
  vector<LL> f(3, 1);
  for (int i = 1; i < n; ++i) {
    vector<LL> g(pw[i + 1], 0);
    for (int v = 0; v < pw[i + 1]; ++v) {
      for (size_t u = 0; u < f.size(); ++u) if (f[u]) {
        int mul = 1;
        for (int o = 0; o < i; ++o) {
          int a = u / pw[o] % 3, b = v / pw[o] % 3, c = v / pw[o + 1] % 3;
          if (a > b) swap(a, b);
          if (a > c) swap(a, c);
          if (b > c) swap(b, c);
          if (a == c) mul *= 2;
          else if (a == b && b != c) mul *= 1;
          else if (a != b && b == c) mul *= 1;
          else mul = 0;
        }
        g[v] += f[u] * mul;
      }
    }
    f.swap(g);
  }
  return accumulate(f.begin(), f.end(), 0ll);
}

int main() {
  cout << run(1) << endl;
  cout << run(2) << endl;
  cout << run(3) << endl;
  cout << run(4) << endl;
  cout << run(5) << endl;
  cout << run(8) << endl;
  return 0;
}
