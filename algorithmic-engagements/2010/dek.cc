#include <cstdio>
#include <vector>

const int N = 1e5 + 10;

std::vector<int> edges[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(m), b(m), deg(n);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
    ++deg[b[i]];
    edges[a[i]].push_back(b[i]);
  }
  std::vector<int> queue;
  queue.reserve(n);
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) queue.push_back(i);
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    for (auto &v: edges[queue[i]]) {
      if (--deg[v] == 0) queue.push_back(v);
    }
  }
  if ((int)queue.size() == n) {
    printf("1\n%d", m);
    for (int i = 1; i <= m; ++i) printf(" %d", i);
    puts("");
  } else {
    puts("2");
    std::vector<int> x, y;
    for (int i = 0; i < m; ++i) {
      if (a[i] < b[i]) x.push_back(i + 1);
      else y.push_back(i + 1);
    }
    printf("%d", (int)x.size());
    for (auto &e: x) printf(" %d", e);
    puts("");
    printf("%d", (int)y.size());
    for (auto &e: y) printf(" %d", e);
    puts("");
  }
  return 0;
}
