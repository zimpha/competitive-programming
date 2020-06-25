#include <cstdio>
#include <vector>

const int N = 1e6 + 10;

std::vector<std::vector<int>> seq[N];
int a[N];

bool check(int l, int r) {
  for (auto &e: seq[r - l]) {
    bool found = false;
    for (int i = l; i < r && !found; ++i) {
      if (a[i] != e[i - l]) found = true;
    }
    if (!found) return true;
  }
  return false;
}

int solve(int l, int r, int draw) {
  if (l == r) return !draw;
  if (check(l, r)) return false;
  if (l + 1 == r) return draw;
  if (check(l + 1, r) || check(l, r - 1)) return true;
  if (l + 2 == r) return !draw;
  if (check(l + 2, r)) return !solve(l, r - 1, draw);
  if (check(l, r - 2)) return !solve(l + 1, r, draw);
  if (check(l + 1, r - 1)) return false;
  if (l + 3 == r) return draw;
  if (check(l + 2, r - 1) || check(l + 1, r - 2)) return true;
  return solve(l + 1, r - 1, draw);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) seq[i].clear();
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
      int l; scanf("%d", &l);
      std::vector<int> w(l);
      for (int j = 0; j < l; ++j) scanf("%d", &w[j]);
      if (l < n) seq[l].push_back(w);
    }
    int win0 = solve(0, n, 0);
    int win1 = solve(0, n, 1);
    if (win0 && win1) puts("FIRST");
    else if (win0 || win1) puts("DRAW");
    else puts("SECOND");
  }
  return 0;
}
