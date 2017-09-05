#include <bits/stdc++.h>

void run() {
  std::vector<int> left, right;
  int n, a;
  std::cin >> n >> a;
  if (n == 1) {
    std::cout << 0 << std::endl;
    return;
  }
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    if (x <= a) left.push_back(x);
    else right.push_back(x);
  }
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end(), std::greater<int>());
  if (!left.size()) {
    std::cout << right[1] - a << std::endl;
  } else if (!right.size()) {
    std::cout << a - left[1] << std::endl;
  } else {
    int ret = (right[0] - left[0]) * 2;
    if (left.size() > 1) {
      ret = std::min(ret, right[0] - left[1] + std::min(a - left[1], right[0] - a));
    }
    if (right.size() > 1) {
      ret = std::min(ret, right[1] - left[0] + std::min(a - left[0], right[1] - a));
    }
    if (left.size() == 1) {
      ret = std::min(right[0] - a, ret);
    }
    if (right.size() == 1) {
      ret = std::min(ret, a - left[0]);
    }
    std::cout << ret << std::endl;
  }
}

int main() {
  run();
  return 0;
}
