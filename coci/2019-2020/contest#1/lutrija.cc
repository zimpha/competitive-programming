#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

bool is_prime(int64 n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (~n & 1) return false;
  for (int64 i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int main() {
  int64 a, b;
  scanf("%lld%lld", &a, &b);
  std::vector<int64> s = {2, a, b};
  if (is_prime(a - 2)) s.push_back(a - 2);
  if (is_prime(a + 2)) s.push_back(a + 2);
  if (is_prime(b - 2)) s.push_back(b - 2);
  if (is_prime(b + 2)) s.push_back(b + 2);
  std::sort(s.begin(), s.end());
  s.erase(std::unique(s.begin(), s.end()), s.end());
  std::vector<std::vector<int>> edges(s.size());
  int x = 0, y = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == a) x = i;
    if (s[i] == b) y = i;
    for (size_t j = 0; j < s.size(); ++j) {
      if (i != j && is_prime(std::abs(s[i] - s[j]))) edges[i].push_back(j);
    }
  }
  std::vector<int> parent(s.size(), -1);
  std::queue<int> queue;
  queue.push(x);
  parent[x] = -2;
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto &v: edges[u]) if (parent[v] == -1) {
      parent[v] = u;
      queue.push(v);
    }
  }
  if (parent[y] == -1) {
    puts("-1");
  } else {
    std::vector<int64> ret;
    for (; y != -2; y = parent[y]) {
      ret.push_back(s[y]);
    }
    std::reverse(ret.begin(), ret.end());
    printf("%d\n", (int)ret.size());
    for (auto &x: ret) printf("%lld ", x);
    puts("");
  }
  return 0;
}
