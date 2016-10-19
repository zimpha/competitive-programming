#include <bits/stdc++.h>
using namespace std;

string toStr(int n) {
  static char bf[100];
  sprintf(bf, "%d", n);
  return string(bf);
}

int sol() {
  for (int x = 1; ; ++ x) {
    string s(toStr(x));
    sort(s.begin(), s.end());
    bool ok(1);
    for (int i = 2; i < 7; ++ i) {
      string t(toStr(i * x));
      sort(t.begin(), t.end());
      if (s != t) ok = 0;
    }
    if (ok) return x;
  }
  return -1;
}

int main() {
  cout << sol() << endl;
  return 0;
}
