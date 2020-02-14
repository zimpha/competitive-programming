#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

std::vector<int> solve(int n) {
  std::vector<int> result(n);
  std::vector<int> s(1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    scanf("%d", &s[i]);
  }
  std::sort(s.begin(), s.end());
  if (s[0] != 0) return {};
  for (int i = 0; i < n; ++i) {
    result[i] = s[1];
    std::vector<bool> done(s.size(), 0);
    std::vector<int> t;
    for (int x = s.size() - 1, y = s.size() - 1; ; ) {
      while (x >= 0 && done[x]) --x;
      if (x < 0) break;
      done[x] = 1;
      int target = s[x] - result[i];
      while (y >= 0 && (done[y] || s[y] > target)) --y;
      if (y < 0 || s[y] != target) return {};
      done[y] = 1;
      t.push_back(s[y]);
    }
    s.swap(t);
    std::reverse(s.begin(), s.end());
  }
  return result;
}

int main() {
  int n;
  scanf("%d", &n);
  auto ret = solve(n);
  if (ret.empty()) puts("impossible");
  else {
    for (auto &x: ret) printf("%d\n", x);
  }
  return 0;
}
