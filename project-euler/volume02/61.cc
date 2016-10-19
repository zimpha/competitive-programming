#include <bits/stdc++.h>
using namespace std;

int get(int type, int pre) {
  for (int n = 1, s; ; ++ n) {
    if (type == 0) s = n * (n + 1) >> 1;
    else if (type == 1) s = n * n;
    else if (type == 2) s = n * (n * 3 - 1) >> 1;
    else if (type == 3) s = n * (2 * n - 1);
    else if (type == 4) s = n * (n * 5 - 3) >> 1;
    else if (type == 5) s = n * (3 * n - 2);
    if (s > 9999) break;
    if (s >= 1000 && s / 100 == pre) return s;
  }
  return -1;
}

int main() {
  int p[] = {0, 1, 2, 3, 4, 5};
  do {
    for (int x = 10; x <= 99; ++ x) {
      int s = get(p[0], x);
      if (s == -1) continue;
      int sum(s);
      int d[6] = {s};
      for (int i = 1; i < 6; ++ i) {
        s = get(p[i], s % 100);
        if (s == -1) break;
        sum += s; d[i] = s;
        if (i == 5 && s % 100 == x) {
          for (int j = 0; j < 6; ++ j) cout << p[j] << " ";
          cout << endl;
          for (int j = 0; j < 6; ++ j) cout << d[j] << " ";
          cout << sum << endl;
        }
      }
    }
  } while (next_permutation(p, p + 6));
  return 0;
}
