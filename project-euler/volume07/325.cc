#include <bits/stdc++.h>

int main() {
  int prev = -1;
  for (int i = 1; i <= 100; ++i) {
    const double phi = (1 + sqrt(5)) / 2;
    int now = int(floor(i * phi));
    if (prev != -1) std::cout << now - prev;
    prev = now;
  }
}
