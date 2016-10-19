#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sol() {
  int p[9];
  for (int i = 0; i < 9; ++ i) p[i] = i + 1;
  set<int> S;
  do {
    int a(0);
    for (int i = 0; i < 9; ++ i) {
      a = a * 10 + p[i];
      int b = 0;
      for (int j = i + 1; j < 9; ++ j) {
        b = b * 10 + p[j];
        int c = 0;
        for (int k = j + 1; k < 9; ++ k) {
          c = c * 10 + p[k];
        }
        if (a * b == c) S.insert(c);
      }
    }
  } while (next_permutation(p, p + 9));
  LL ret(0);
  for (auto &x: S) ret += x;
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}
