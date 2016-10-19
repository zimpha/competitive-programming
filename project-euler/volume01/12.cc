#include <bits/stdc++.h>
using namespace std;

int sol(int target) {
  const int n = 100000;
  static int dv[n];
  fill(dv, dv + n, 0);
  for (int i = 1; i < n; ++ i) {
    for (int j = i; j < n; j += i) {
      dv[j] ++;
    }
  }
  for (int i = 1; i < n; ++ i) {
    int cnt;
    if (i & 1) cnt = dv[(i + 1) >> 1] * dv[i];
    else cnt = dv[i / 2] * dv[i + 1];
    if (cnt > target) return i * (i + 1) / 2;
  }
  return -1;
}

int main() {
  cout << sol(5) << endl;
  cout << sol(500) << endl;
  return 0;
}
