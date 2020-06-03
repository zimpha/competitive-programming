#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> left(n), right(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &left[i], &right[i]);
      --left[i], --right[i];
    }
    std::vector<int> pre, post;
    std::function<void(int)> rec = [&](int u) {
      if (u == -1) return;
      pre.push_back(u);
      rec(left[u]);
      rec(right[u]);
      post.push_back(u);
    };

    rec(0);

    std::vector<int> dsu(n), col(n);
    for (int i = 0; i < n; ++i) dsu[i] = i;
    
    std::function<int(int)> root = [&](int x) {
      if (x != dsu[x]) dsu[x] = root(dsu[x]);
      return dsu[x];
    };

    for (int i = 0; i < n; ++i) {
      int a = root(pre[i]);
      int b = root(post[i]);
      dsu[a] = b;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (root(i) == i) col[i] = (cnt++) % k;
    }
    if (cnt < k) printf("Case #%d: Impossible\n", cas);
    else {
      printf("Case #%d:", cas);
      for (int i = 0; i < n; ++i) printf(" %d", col[root(i)] + 1);
      puts("");
    }
  }
  return 0;
}
