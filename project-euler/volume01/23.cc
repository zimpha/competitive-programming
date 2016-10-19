#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> dv(n + 1, 0);
  for (int i = 1; i <= n; ++ i) {
    for (int j = i + i; j <= n; j += i) {
      dv[j] += i;
    }
  }
  vector<int> ab;
  for (size_t i = 1; i <= n; ++ i) {
    if (dv[i] > i) ab.push_back(i);
  }
  cout << ab.size() << endl;
  fill(dv.begin(), dv.end(), 1);
  for (size_t i = 0; i < ab.size(); ++ i) {
    for (size_t j = 0; j < ab.size(); ++ j) {
      if (ab[i] + ab[j] <= n) dv[ab[i] + ab[j]] = 0;
    }
  }
  int ret(0);
  for (int i = 1; i <= n; ++ i) ret += i * dv[i];
  return ret;
}

int main() {
  cout << sol(28123) << endl;
  return 0;
}
