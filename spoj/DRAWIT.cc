#include <cstdio>
#include <vector>
#include <functional>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> deg(n), dsu(n);
    std::function<int(int)> root = [&](int x) {
      if (x != dsu[x]) dsu[x] = root(dsu[x]);
      return dsu[x];
    };
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      --u, --v;
      deg[u] += c;
      deg[v] += c;
      u = root(u);
      v = root(v);
      dsu[u] = v;
    }
    bool valid = 1;
    for (int i = 1; i < n; ++i) {
      valid &= root(i) == root(0);
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) cnt += deg[i] & 1;
    valid &= cnt <= 2;
    if (!valid) puts("NO");
    else {
      if (cnt == 0) puts("YES 1");
      else {
        printf("YES ");
        for (int i = 0; i < n; ++i) {
          if (deg[i] & 1) {
            printf("%d\n", i + 1);
            break;
          }
        }
      }
    }
  }
  return 0;
}
