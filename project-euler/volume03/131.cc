#include <bits/stdc++.h>
using namespace std;

int run(int n) {
  vector<bool> vs(n, 1); vs[0] = vs[1] = 0;
  for (int i = 2; i < n; ++i) if (vs[i]) {
    for (int j = i + i; j < n; j += i) vs[j] = 0;
  }
  int ret = 0;
  for (int x = 1; x * x * 3 + x * 3 + 1 < n; ++x) {
    if (vs[x * x * 3 + x * 3 + 1]) ++ret;
  }
  return ret;
}

int main() {
  cout << run(100) << endl;
  cout << run(1000000) << endl;
  return 0;
}
