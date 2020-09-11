#include <cstdio>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm>

using ull = unsigned long long;
const int N = 1e5 + 10, seed = 1e9 + 7;

std::vector<int> vec[N];
int idx[N], ret[N];
ull hash[N];
int n, d;

void solve(int dim, int l, int r) {
  if (dim == d - 1) {
    for (int i = l; i < r; ++i) {
      ret[idx[i]] = idx[r + l - 1 - i];
      hash[i] = vec[idx[i]][dim];
    }
    return;
  }
  for (int i = l, j; i < r; i = j) {
    for (j = i; j < r && vec[idx[i]][dim] == vec[idx[j]][dim]; ++j);
    solve(dim + 1, i, j);
  }
  int mx = 0;
  for (int i = l; i < r; ++i) {
    mx = std::max(mx, vec[idx[i]][dim]);
  }
  std::unordered_map<ull, std::vector<int>> mp;
  for (int i = l; i < r; ++i) if (vec[idx[i]][dim] * 2 <= mx) {
    hash[i] = hash[i] * seed + vec[idx[i]][dim];
    mp[hash[i]].push_back(idx[i]);
  }
  for (int i = l; i < r; ++i) if (vec[idx[i]][dim] * 2 > mx) {
    auto w = hash[i] * seed + (mx - vec[idx[i]][dim]);
    assert(mp[w].size());
    std::swap(ret[idx[i]], ret[mp[w].back()]);
    mp[w].pop_back();
    hash[i] = hash[i] * seed + vec[idx[i]][dim];
  }
}

int main() {
  scanf("%d%d", &n, &d);
  for (int i = 0; i < d; ++i) scanf("%*d");
  for (int i = 0; i < n; ++i) {
    vec[i].resize(d);
    for (int j = 0; j < d; ++j) {
      scanf("%d", &vec[i][j]);
    }
    idx[i] = i;
  }
  std::sort(idx, idx + n, [&](int x, int y) {
    return vec[x] < vec[y];
  });

  solve(0, 0, n);
  for (int i = 0; i < n; ++i) {
    printf("%d %d\n", i + 1, ret[i] + 1);
  }
  return 0;
}
