#include <bits/stdc++.h>
using namespace std;

int get(int a, int b, int c) {
  return min(c * c + (a + b) * (a + b), min(a * a + (b + c) * (b + c), b * b + (a + c) * (a + c)));
}

int sol(int tar) {
  for (int M = 1; ; ++ M) {
    for (int a = 1; a <= M; ++ a) {
      for (int b = a; b <= M; ++ b) {
        int x = get(a, b, M);
        int y = sqrt(x);
        if (y * y == x) -- tar;
      }
    }
    if (tar < 0) return M;
  }
  return -1;
}

int main() {
  cout << sol(2000) << endl;
  cout << sol(1000000) << endl;
  return 0;
}
