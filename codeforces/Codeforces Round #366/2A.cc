#include <bits/stdc++.h>

void run() {
  int n;
  std::cin >> n;
  for (int i = 1; i < n; ++i) {
    if (i & 1) printf("I hate that ");
    else printf("I love that ");
  }
  if (n & 1) printf("I hate it\n");
  else printf("I love it\n");
}

int main() {
  run();
  return 0;
}
