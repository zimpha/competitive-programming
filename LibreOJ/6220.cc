#include <iostream>
#include <vector>

using int64 = long long;

int main() {
  int n;
  std::cin >> n;
  std::vector<int> mark(n, -1);
  std::vector<int64> a(n);
  int64 sum = 0;
  mark[0] = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    sum = (sum + a[i]) % n;
    if (mark[sum] != -1) {
      for (int j = mark[sum]; j <= i; ++j) {
        std::cout << j + 1 << " " << a[j] << "\n";
      }
      return 0;
    }
    mark[sum] = i + 1;
  }
  return 0;
}
