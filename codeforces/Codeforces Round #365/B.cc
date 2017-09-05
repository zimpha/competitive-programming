#include <bits/stdc++.h>

void run() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> c(n);
  std::vector<int> d(k);
  long long sum = 0, ret = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
    sum += c[i];
  }
  for (int i = 0; i < k; ++i) {
    std::cin >> d[i];
    --d[i]; 
    ret += c[d[i]] * (sum - c[d[i]]);
    sum -= c[d[i]];
    c[d[i]] = 0;
  }
  for (int i = 0; i < n; ++i) {
    ret += c[i] * c[(i + 1) % n];
  }
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}
