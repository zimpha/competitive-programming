#include <bits/stdc++.h>
using namespace std;

int f[10];
int len(int n) {
  set<int> S; S.insert(n);
  for (; ;) {
    int m = 0;
    for (; n; n /= 10) m += f[n % 10];
    if (S.count(n = m)) return S.size();
    S.insert(n);
  }
  return -1;
}

int sol(int n) {
  f[0] = 1;
  for (int i = 1; i < 10; ++ i) f[i] = i * f[i - 1];
  int ret(0);
  for (int i = 1; i <= n; ++ i) {
    ret += len(i) == 60;
  }
  return ret;
}

int main() {
  cout << sol(1000000) << endl;
  return 0;
}
