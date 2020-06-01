#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

const int N = 2e5 + 10;

std::vector<int> edges[N];
int u[N], v[N], size[N];
int dsu[N * 2], pos[N * 2];
int n, a, b;

int id(int i, int x, int y) {
  if (u[i] == x && v[i] == y) return i * 2;
  else return i * 2 + 1;
}

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void merge(int a, int b) {
  a = get(a), b = get(b);
  if (a != b) dsu[a] = b;
}

void dfs(int x, int p = -1) {
  size[x] = 1;
  for (auto &e: edges[x]) {
    int y = u[e] + v[e] - x;
    if (y == p) continue;
    dfs(y, x);
    if (size[y] >= b && n - size[y] >= a) dsu[id(e, x, y)] = id(e, x, y);
    else dsu[id(e, x, y)] = -1;
    if (size[y] >= a && n - size[y] >= b) dsu[id(e, y, x)] = id(e, y, x);
    else dsu[id(e, y, x)] = -1;
    size[x] += size[y];
  }
}

int main() {
  scanf("%d%d%d", &n, &a, &b);
  for (int i = 0; i + 1 < n; ++i) {
    scanf("%d%d", &u[i], &v[i]);
    --u[i], --v[i];
    edges[u[i]].push_back(i);
    edges[v[i]].push_back(i);
  }
  dfs(0);
  memset(pos, -1, sizeof(pos));

  auto gao = [](std::vector<int> &va, std::vector<int> &vb) {
    for (size_t i = 0; i < va.size(); ++i) pos[va[i]] = i;
    int prefix = -1, suffix = va.size();
    for (auto &e: vb) {
      if (pos[e ^ 1] != -1) {
        if (pos[e ^ 1] != 0) merge(e, va[0]);
        if (pos[e ^ 1] != va.size() - 1) merge(e, va.back());
        prefix = std::max<int>(prefix, pos[e ^ 1] - 1);
        suffix = std::min<int>(suffix, pos[e ^ 1] + 1);
      } else {
        if (!va.empty()) merge(e, va[0]);
        prefix = std::max<int>(prefix, va.size() - 1);
        suffix = std::min<int>(suffix, 0);
      }
    }
    for (int i = 1; i < prefix; ++i) merge(va[i - 1], va[i]);
    for (int i = suffix; i + 1 < (int)va.size(); ++i) merge(va[i], va[i + 1]);
    for (size_t i = 0; i < va.size(); ++i) pos[va[i]] = -1;
  };

  for (int x = 0; x < n; ++x) {
    std::vector<int> va, vb;
    for (auto &e: edges[x]) {
      int y = u[e] + v[e] - x;
      int ib = id(e, x, y), ia = id(e, y, x);
      if (dsu[ib] != -1) vb.emplace_back(ib);
      if (dsu[ia] != -1) va.emplace_back(ia);
    }
    gao(va, vb);
    gao(vb, va);
  }
  int ret = 0;
  for (int i = 0; i < n * 2 - 2; ++i) if (dsu[i] != -1) {
    ret += get(i) == i;
  }
  printf("%d\n", ret);
  return 0;
}
