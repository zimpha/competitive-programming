#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int K;
  scanf("%d", &K);
  std::vector<std::pair<int, int>> edges;
  for (int i = 2; i < 42; i += 2) {
    edges.emplace_back(i, i + 2);
    edges.emplace_back(i, i + 1);
    edges.emplace_back(i + 2, i + 1);
  }
  for (int i = 0; i < 21; ++i) {
    if (K >> i & 1) edges.emplace_back(1, i * 2 + 2);
  }
  printf("42 %d\n", (int)edges.size());
  for (auto &e: edges) printf("%d %d\n", e.first, e.second);
  return 0;
}
