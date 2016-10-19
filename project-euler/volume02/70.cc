#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

string to(int n) {
  static char buf[100];
  sprintf(buf, "%d", n);
  return string(buf);
}

int sol(int n) {
  vector<int> phi(n);
  for (int i = 0; i < n; i ++) phi[i] = i;
  for (int i = 2; i < n; ++ i) if (phi[i] == i) {
    for (int j = i; j < n; j += i) {
      phi[j] = phi[j] / i * (i - 1);
    }
  }
  int ret = -1;
  for (int i = 2; i <= n; ++ i) {
    string s = to(i), t = to(phi[i]);
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    if (s == t) {
      if (ret == -1 || i * 1.0 / phi[i] < ret * 1.0 / phi[ret]) {
        ret = i;
      }
    }
  }
  return ret;
}

int main() {
  cout << sol(10) << endl;
  cout << sol(10000000) << endl;
  return 0;
}
