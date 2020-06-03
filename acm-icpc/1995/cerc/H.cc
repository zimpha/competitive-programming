#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 100;
int a[MAXN], n, lim, tot;
bool vis[MAXN];

bool cmp(const int &a, const int &b) {
  return a > b;
}

bool dfs(int cur, int len, int num) {
  if (num == n) return true;
  for (int i = cur; i < n; ++ i) {
    if (vis[i]) continue;
    if (len > a[i]) {
      vis[i] = 1;
      if (dfs(i + 1, len - a[i], num + 1)) return true;
      vis[i] = 0;
      while (i + 1 < n && a[i] == a[i + 1]) ++ i;
    } else if (len == a[i]) {
      vis[i] = 1;
      if (dfs(0, lim, num + 1)) return true;
      vis[i] = 0;
      return false;
    }
    if (len == lim) break;
  }
  return false;
}

int main() {
  while (scanf("%d", &n) == 1 && n) {
    tot = 0;
    for (int i = 0; i < n; ++ i) {
      scanf("%d", &a[i]); tot += a[i];
    }
    sort(a, a + n, cmp);
    for (lim = a[0]; lim <= tot; ++ lim) {
      if (tot % lim == 0) {
        memset(vis, 0, sizeof(vis));
        if (dfs(0, lim, 0)) {
          printf("%d\n", lim);
          break;
        }
      }
    }
  }
  return 0;
}
