#include <cstdio>
#include <cassert>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n), b(m);
  std::vector<int> in(m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    --a[i];
    in[a[i]]++;
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &b[i]);
    --b[i];
  }
  std::vector<int> queue;
  for (int i = 0; i < m; ++i) {
    if (in[i] == 0) {
      queue.push_back(i);
    }
  }
  std::vector<int> bornholm(n, 1);
  std::vector<int> gotland(m);
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i], v = b[u];
    gotland[u] = 1;
    if (bornholm[v]) {
      bornholm[v] = 0;
      if (--in[a[v]] == 0) queue.push_back(a[v]);
    }
  }
  for (int i = 0; i < n; ++i) printf("%d", bornholm[i]);
  puts("");
  for (int i = 0; i < m; ++i) printf("%d", gotland[i]);
  puts("");
  return 0;
}
