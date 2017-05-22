#include <bits/stdc++.h>

int pos[8], cnt;
std::set<std::vector<int>> S;

void dfs(int d, int n) {
  if (d == 8) {
    if (pos[0] + 40 - pos[7] < 3) return;
    std::vector<int> a(pos, pos + 8);
    std::vector<int> b(pos, pos + 8);
    for (int i = 0; i < 8; ++i) b[i] = 39 - b[i];
    std::reverse(b.begin(), b.end());
    if (!S.count(a) && !S.count(b)) {
      std::cout << ++cnt << std::endl;
      S.insert(a);
      S.insert(b);
    }
    return;
  }
  if (n == 40) return;
  dfs(d, n + 1);
  if (!d || (d && n - pos[d - 1] >= 3)) {
    pos[d] = n;
    dfs(d + 1, n + 1);
  }
}

int main() {
  cnt = 0;
  dfs(0, 0);
  std::cout << cnt << std::endl;
  return 0;
}
