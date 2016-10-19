#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sol() {
  string s = "1023456789";
  const int p[] = {2, 3, 5, 7, 11, 13, 17};
  LL ret(0);
  do {
    bool ok(1);
    for (int i = 1; i < 8 && ok; ++ i) {
      int x = 0;
      for (int j = 0; j < 3; ++ j) {
        x = x * 10 + s[i + j] - '0';
      }
      if (x  % p[i - 1]) ok = 0;
    }
    if (ok) {
      LL x(0);
      for (int i = 0; i < 10; ++ i) {
        x = x * 10 + s[i] - '0';
      }
      ret += x;
    }
  } while (next_permutation(s.begin(), s.end()));
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}
