#include <cstdio>
#include <cassert>
#include <vector>
#include <set>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::vector<std::pair<int, int>> edges;
  std::vector<int> cl(n), cr(n);
  std::vector<int> queue;
  for (int i = 0; i < n; ++i) {
    bool same = false;
    while (!queue.empty() && a[queue.back()] <= a[i]) {
      if (a[queue.back()] == a[i]) same = true;
      edges.emplace_back(queue.back(), i);
      cl[i]++, cr[queue.back()]++;
      queue.pop_back();
    }
    if (!queue.empty() && !same) {
      edges.emplace_back(queue.back(), i);
      cl[i]++, cr[queue.back()]++;
    }
    queue.push_back(i);
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += cl[i] * cr[i];
    ret += cr[i];
  }
  std::vector<std::vector<int>> go(n);
  for (auto &e: edges) {
    if (cl[e.first] + cr[e.first] < cl[e.second] + cr[e.second]) {
      go[e.first].push_back(e.second);
    } else {
      go[e.second].push_back(e.first);
    }
  }
  std::vector<int> mark(n);
  for (int u = 0; u < n; ++u) {
    for (auto &v: go[u]) mark[v] = 1;
    for (auto &v: go[u]) {
      for (auto &w: go[v]) ret -= mark[w];
    }
    for (auto &v: go[u]) mark[v] = 0;
  }
  printf("%d\n", ret);
  return 0;
}
