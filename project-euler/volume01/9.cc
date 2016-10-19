#include <bits/stdc++.h>
using namespace std;

int sol() {
  for (int a = 1; a < 1000; ++ a) {
    for (int b = 1; b < 1000; ++ b) {
      int c = 1000 - a - b;
      if (c >= 0 && a * a + b * b == c * c) {
        return a * b * c;
      }
    }
  }
}

int main() {
  cout << sol() << endl;
  return 0;
}
