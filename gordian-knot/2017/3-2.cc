#include <bits/stdc++.h>

int main() {
  int n;
  scanf("%d", &n);
  int p[100];
  for (int i = 0; i < n; ++i) {
    p[i] = i + 1;
  }
  std::map<int, int> cnt;
  do {
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += abs(i + 1 - 2 * p[i]);
    cnt[sum]++;
  } while (std::next_permutation(p, p + n));
  for (auto &&e: cnt) {
    std::cout << e.first << ' ' << e.second << std::endl;
  }
  return 0;
}
