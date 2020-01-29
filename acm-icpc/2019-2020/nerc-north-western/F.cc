#include <cstdio>
#include <vector>
#include <bitset>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  std::bitset<101> sa, sb;
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]), sa[a[i]] = 1;
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]), sb[b[i]] = 1;
  if ((sb | sa) != sa || (sb.count() == n && a != b)) {
    puts("-1");
    return 0;
  }
  if (a == b) {
    puts("0");
    return 0;
  }
  int hole = 1;
  while (sa[hole]) ++hole;
  std::vector<std::pair<int, int>> ops;
  std::vector<int> sp(101, -1), so(101);
  auto mark = sa ^ (sa & sb);

  // change a[i] -> v;
  auto change = [&](int i, int u, int v) {
    if (u == v) return;
    ops.emplace_back(0, u);
    ops.emplace_back(1, v);
    a[i] = v;
  };

  // replace all u to v in [l, r]
  auto eliminate = [&](int l, int r, int u, int v) {
    while (true) {
      int found = -1;
      for (int i = r; i >= l; --i) {
        if (a[i] == u) found = i;
      }
      if (found != -1) change(found, u, v);
      else break;
    }
  };

  // a[i] is not use in any place
  for (int i = 0; i < n; ++i) {
    if (mark[a[i]]) change(i, a[i], b[i]);
  }

  for (int i = n - 2; i >= 0; --i) {
    if (a[i] == b[i]) continue;
    int diff = -1;
    for (int j = 0; j < n; ++j) {
      if (a[i] != a[j]) diff = a[j];
    }
    eliminate(0, i - 1, a[i], diff);
    int found = -1;
    for (int j = n - 1; j > i; --j) {
      if (a[i] == a[j]) found = j;
    }
    // we have same value after i, just change it
    if (found != -1) {
      change(i, a[i], b[i]);
      if (sp[a[i]] != -1) {
        int x = a[i], y = so[x], z = a[n - 1];
        diff = -1;
        for (int j = 0; j < n; ++j) {
          if (a[j] != x && a[j] != y && a[j] != z) diff = a[j];
        }
        eliminate(0, i - 1, z, diff);
        change(i, x, z);
        change(n - 1, hole, x);
        change(sp[x], x, z);
        change(i, z, x);
        change(n - 1, hole, z);
        eliminate(i + 1, sp[x], z, y);
        eliminate(i + 1, sp[x] - 1, y, z);
        sp[x] = -1;
      }
    } else {
      std::vector<int> last(101, -1);
      int u = -1, v = -1;
      for (int j = 0; j < n && u == -1; ++j) {
        if (last[a[j]] != -1) u = last[a[j]], v = j;
        if (j < i) last[a[j]] = j;
      }
      if (u != -1) {
        // case 1: yyxz -> zyxz -> zyxx -> zytx
        // case 2: yxyz -> zxyz -> zxyx -> ztyx
        // case 3: yxy -> yxx -> ytx
        change(u, a[u], a[n - 1]);
        change(n - 1, hole, a[i]);
        change(i, a[i], b[i]);
        continue;
      }
      for (int j = i + 1; j < n && u == -1; ++j) {
        if (last[a[j]] != -1) u = last[a[j]], v = j;
        last[a[j]] = j;
      }
      if (v == n - 1) {
        // case 4: xyy -> xyx -> tyx
        change(n - 1, hole, a[i]);
        change(i, a[i], b[i]);
      } else {
        // case 5: xyyz -> xxyz -> txyz
        if (i == 0) {
          if (a[n - 1] != b[0]) {
            change(n - 1, hole, b[n - 1]);
            change(0, a[0], b[0]);
          } else {
            change(u, a[u], a[0]);
            change(0, a[0], a[n - 1]);
            change(n - 1, hole, a[u]);
            change(u, a[u], a[v]);
          }
        } else {
          sp[a[i]] = u; so[a[i]] = a[u];
          change(u, a[u], a[i]);
          change(i, a[i], b[i]);
        }
      }
    }
  }
  if (a[n - 1] != b[n - 1]) {
    change(n - 1, hole, b[n - 1]);
  }
  printf("%d\n", (int)ops.size());
  for (auto &op: ops) {
    if (op.first == 0) printf("foreach ($a as &$x) if ($x == %d) break;\n", op.second);
    else printf("foreach ($a as  $x) if ($x == %d) break;\n", op.second);
  }
  return 0;
}
