#include <cstdio>
#include <vector>

const int N = 1e5 + 10;

std::vector<int> edges[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (0 <= i + a[i] && i + a[i] < n) {
      edges[i + a[i]].push_back(i);
    }
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
    if (0 <= i + b[i] && i + b[i] < n) {
      edges[i + b[i]].push_back(i);
    }
  }
  std::vector<bool> mark(n);
  mark[n - 1] = true;
  std::vector<int> queue = {n - 1};
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &&v: edges[u]) {
      if (!mark[v]) {
        mark[v] = true;
        queue.push_back(v);
      }
    }
  }
  if (!mark[0]) puts("No solution!");
  else {
    std::vector<char> res;
    int start = 0;
    for (int i = 0; i < n * 3; ++i) {
      if (start == n - 1) break;
      if (0 <= start + a[start] && start + a[start] < n && mark[start + a[start]]) {
        res.push_back('a');
        start = start + a[start];
      } else {
        res.push_back('b');
        start = start + b[start];
      }
    }
    if (res.size() > n) puts("Infinity!");
    else {
      for (auto &&c: res) putchar(c);
      puts("");
    }
  }
  return 0;
}