#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sol() {
  LL s(1), t(1);
  for (int a = 1; a <= 9; ++ a) {
    for (int b = 1; b <= 9; ++ b) {
      for (int c = 1; c <= 9; ++ c) {
        int x = a * 10 + b;
        int y = b * 10 + c;
        if (x >= y) continue;
        if (x * c == y * a) {
          s *= a; t *= c;
        }
      }
    }
  }
  return t / __gcd(s, t);
}

int main() {
  cout << sol() << endl;
  return 0;
}
