#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
  int n;
  scanf("%d", &n);
  int c0 = n / 2, c1 = (n + 1) / 2;
  int last_pos = -1, last_val = -1;
  std::vector<int> v00, v11, vx0, vx1;
  int ret = 0;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    if (x == 0) continue;
    if (x & 1) --c1;
    else --c0;
    if (last_pos == -1) {
      if (x & 1) vx1.push_back(i);
      else vx0.push_back(i);
    } else {
      int u = last_val & 1, v = x & 1;
      if (u > v) std::swap(u, v);
      if (u == 0 && v == 0) v00.push_back(i - last_pos - 1);
      if (u == 0 && v == 1) ++ret;
      if (u == 1 && v == 1) v11.push_back(i - last_pos - 1);
    }
    last_pos = i; last_val = x;
  }
  if (last_pos == -1) {
    printf("%d\n", int(n > 1));
    return 0;
  }
  if (last_val & 1) vx1.push_back(n - 1 - last_pos);
  else vx0.push_back(n - 1 - last_pos);
  std::sort(v00.begin(), v00.end(), std::greater<int>());
  std::sort(v11.begin(), v11.end(), std::greater<int>());
  std::sort(vx0.begin(), vx0.end(), std::greater<int>());
  std::sort(vx1.begin(), vx1.end(), std::greater<int>());
  while (!v00.empty() && c0 >= v00.back()) {
    c0 -= v00.back();
    v00.pop_back();
  }
  while (!vx0.empty() && c0 >= vx0.back()) {
    c0 -= vx0.back();
    vx0.pop_back();
  }
  while (!v11.empty() && c1 >= v11.back()) {
    c1 -= v11.back();
    v11.pop_back();
  }
  while (!vx1.empty() && c1 >= vx1.back()) {
    c1 -= vx1.back();
    vx1.pop_back();
  }
  ret += (v00.size() + v11.size()) * 2 + vx0.size() + vx1.size();
  printf("%d\n", ret);
  return 0;
}