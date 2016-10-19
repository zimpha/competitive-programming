#include <bits/stdc++.h>
using namespace std;

vector<bool> vs;

void sieve(int n) {
  vs.assign(n, 1); vs[0] = vs[1] = 0;
  for (int i = 2; i < n; ++ i) if (vs[i]) {
    for (int j = i + i; j < n; j += i) vs[j] = 0;
  }
}

int sol(int n) {
  int ret(0);
  sieve(n);
  for (int i = 2; i < n; ++ i) if (vs[i]) {
    int len(0), flag(1), pw(1);
    for (int x = i; x; x /= 10) {
      len ++; pw *= 10;
    }
    pw /= 10;
    for (int _ = 0, x = i; _ < len && flag; ++ _) {
      int d = x % 10;
      x = x / 10 + d * pw;
      flag &= vs[x];
    }
    ret += flag;
  }
  return ret;
}

int main() {
  cout << sol(100) << endl;
  cout << sol(1000000) << endl;
  return 0;
}
