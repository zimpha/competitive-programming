#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n) {
  vector<int> a(n + 1, 0), b(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    for (int p = 2; p <= i; p *= 2) a[i] += i / p;
    for (int p = 5; p <= i; p *= 5) b[i] += i / p;
  }
  int s = a[n], t = b[n];
  LL ret = 0;
  for (int x = 0; x <= n; ++x) {
    for (int y = 0; y <= n - x; ++y) {
      int z = n - x - y;
      if (s - a[x] - a[y] - a[z] >= 12 && t - b[x] - b[y] - b[z] >= 12) ++ret;
    }
  }
  return ret;
}

int main() {
  cout << run(200000) << endl;
  return 0;
}
