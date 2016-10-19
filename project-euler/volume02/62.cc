#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

string toString(LL n) {
  static char buf[100];
  sprintf(buf, "%lld", n);
  return string(buf);
}

LL sol() {
  int n = 100000;
  vector<pair<string, int> > u(n);
  for (int i = 0; i < n; ++ i) {
    string s = toString((LL)i * i * i);
    sort(s.begin(), s.end());
    u[i] = make_pair(s, i);
  }
  sort(u.begin(), u.end());
  int mx(n);
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && u[i].first == u[j].first; ++ j);
    if (j - i == 5) mx = min(mx, u[i].second);
  }
  return (LL)mx * mx * mx;
}

int main() {
  cout << sol() << endl;
  return 0;
}
