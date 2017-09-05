#include <bits/stdc++.h>

int a[50][50];

void run() {
  int n;
  std::cin >> n;
  int s = n / 2, x = 1, val = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < x; ++j) {
      a[i][s + j] = val;
      val += 2;
    }
    if (i < n / 2) --s, x += 2;
    else ++s, x -= 2;
  }
  val = 2;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i][j] == 0) {
        a[i][j] = val;
        val += 2;
      }
      std::cout << a[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

int main() {
  run();
  return 0;
}
