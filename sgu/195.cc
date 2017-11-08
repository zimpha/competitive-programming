#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 500000 + 10;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> p(n);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &p[i]);
    --p[i];
  }
  std::vector<bool> vis(n);
  std::vector<int> grant;
  for (int i = n - 1; i > 0; --i) {
    if (!vis[p[i]] && !vis[i]) {
      grant.push_back(i + 1);
      vis[p[i]] = true;
    } else {
      vis[i] = true;
    }
  }
  printf("%d000\n", (int)grant.size());
  std::reverse(grant.begin(), grant.end());
  for (size_t i = 0; i < grant.size(); ++i) {
    if (i) putchar(' ');
    printf("%d", grant[i]);
  }
  puts("");
}
