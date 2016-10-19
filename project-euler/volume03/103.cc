#include <bits/stdc++.h>
using namespace std;

const int s[] = {20, 31, 38, 39, 40, 42, 45};
int t[7], x[128], y[7], ret;

void dfs(int d) {
  if (d == 7) {
    static int a[7];
    for (int i = 0; i < 7; ++i) {
      a[i] = t[i] + s[i];
    }
    for (int msk = 0; msk < 128; ++msk) {
      x[msk] = 0;
      for (int i = 0; i < 7; ++i) {
        if (msk >> i & 1) x[msk] += a[i];
      }
    }
    for (int msk = 1; msk < 128; ++msk) {
      for (int sub = (msk - 1) & msk; sub; sub = (sub - 1) & msk) {
        if (x[sub] >= x[msk]) return;
      }
    }
    sort(x, x + 128);
    for (int i = 1; i < 128; ++i) {
      if (x[i] == x[i - 1]) return;
    }
    if (x[127] < ret) {
      ret = x[127];
      for (int i = 0; i < 7; ++i) y[i] = a[i];
    }
    return;
  }
  for (int i = -3; i <= 3; ++i) {
    t[d] = i; dfs(d + 1);
  }
}

int main() {
  ret = 1e9;
  dfs(0);
  cout << ret << endl;
  for (int i = 0; i < 7; ++i) cout << y[i]; cout << endl;
  return 0;
}
