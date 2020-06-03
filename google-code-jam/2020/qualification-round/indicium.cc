#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int N = 100;

int graph[N][N], ret[N][N];
int mate[N], mark[N], go[N];
int n;

bool aug(int u) {
  for (int v = 0; v < n; ++v) if (!mark[v] && graph[u][v]) {
    mark[v] = true;
    if (mate[v] == -1 || aug(mate[v])) {
      go[u] = v;
      mate[v] = u;
      return true;
    }
  }
  return false;
}

bool check(int m) {
  for (int i = 0; i < n; ++i) m -= ret[i][i];
  if (m != 0) return false;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < j; ++k) {
        if (ret[i][j] == ret[i][k]) return false;
        if (ret[j][i] == ret[k][i]) return false;
      }
    }
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int m;
    scanf("%d%d", &n, &m);
    if (m == n + 1 || m == n * n - 1 || (n == 3 && m == 5) || (n == 3 && m == 7)) {
      printf("Case #%d: IMPOSSIBLE\n", cas);
      continue;
    }
    printf("Case #%d: POSSIBLE\n", cas);
    if (n == 2) {
      if (m == 2) puts("1 2\n2 1");
      else puts("2 1\n1 2");
      continue;
    }
    std::vector<int> a(n);
    int mm = m;
    for (int i = 0; i < n; ++i) {
      int l = 1, r = n;
      r = std::min(r, m - (n - 1 - i));
      l = std::max(l, m - n * (n - 1 - i));
      assert(l <= r);
      a[i] = r;
      m -= a[i];
    }
    std::sort(a.begin(), a.end());
    if (a[0] != a[n - 1]) {
      if (a[0] == a[n - 2]) {
      ++a[n - 2]; --a[n - 1];
      } else if (a[1] == a[n - 1]) {
        if (a[1] < n) ++a[1], --a[2];
        else ++a[0], --a[1];
      }
    }
    for (int r = 0; r < n; ++r) {
      memset(graph, 0, sizeof(graph));
      for (int c = 0; c < n; ++c) if (c != r) {
        std::vector<bool> used(n, 0);
        for (int i = 0; i < r; ++i) {
          printf("%d ", ret[i][c] - 1);
          fflush(stdout);
          used.at(ret[i][c] - 1) = true;
        }
        puts("");
        used[a[r] - 1] = true;
        used[a[c] - 1] = true;
        for (int i = 0; i < n; ++i) {
          if (!used[i]) graph[c][i] = true;
        }
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%d", graph[i][j]);
        puts("");
      }
      puts("");
      memset(mate, -1, sizeof(mate));
      memset(go, -1, sizeof(go));
      for (int i = 0; i < n; ++i) {
        memset(mark, 0, sizeof(mark));
        aug(i);
      }
      for (int i = 0; i < n; ++i) {
        if (go[i] == -1) {
          assert(r == i);
          ret[r][r] = a[r];
        } else ret[r][i] = go[i] + 1;
      }
      for (int i = 0; i < n; ++i) printf("%d ", ret[r][i]);
      puts("xxxx");
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        printf("%d ", ret[i][j]);
      }
      puts("");
    }
    assert(check(mm));
  }
  return 0;
}
