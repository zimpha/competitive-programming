#include <bits/stdc++.h>
using namespace std;

bool ok(int n) {
  double x = (sqrt(1 + 24 * n) + 1) / 6;
  return x == (int)x;
}

int main() {
  for (int i = 1; ; ++ i) {
    int a = i * (i * 3 - 1) >> 1;
    for (int j = 1; j < i; ++ j) {
      int b = j * (j * 3 - 1) >> 1;
      if (ok(a + b) && ok(a - b)) {
        cout << a - b << endl;
        return 0;
      }
    }
  }
  return 0;
}
