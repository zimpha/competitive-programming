#include <bits/stdc++.h>
using namespace std;

bool isP(double n) {
  double x = (sqrt(1 + 24 * n) + 1) / 6;
  return x == (int)x;
}

int main() {
  for (int i = 144; ; ++ i) {
    int n = i * (2 * i - 1);
    if (isP(n)) {
      cout << i << " " << n << endl;
      return 0;
    }
  }
  return 0;
}
