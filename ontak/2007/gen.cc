#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>

using uint64 = unsigned long long;
const int N = 100, seed = 1e9 + 7;

char s[N], t[N];
std::vector<int> ops[N];

void gao() {
  std::vector<int> u = {3, 2, 2, 1, 6, 3, 1};
  //std::reverse(u.begin(), u.end());
  for (auto &o: u) {
    --o;
    char a = s[ops[o].back()];
    for (int j = ops[o].size() - 1; j > 0; --j) {
      s[ops[o][j]] = s[ops[o][j - 1]];
    }
    s[ops[o][0]] = a;
    puts(s);
  }
}

bool solve(int n, int m, int steps) {
  std::vector<int> pw(steps + 1, 1);
  for (int i = 1; i <= steps; ++i) {
    pw[i] = pw[i - 1] * m;
  }
  int x = steps / 2, y = steps - x;
  if (x < y) std::swap(x, y);
  std::vector<std::pair<uint64, int>> ps;
  for (int mask = 0; mask < pw[y]; ++mask) {
    static char tmp[N];
    for (int i = 0; i < n; ++i) tmp[i] = t[i];
    for (int i = y - 1; i >= 0; --i) {
      int o = mask / pw[y - 1 - i] % m;
      char a = tmp[ops[o][0]];
      for (size_t j = 0; j + 1 < ops[o].size(); ++j) {
        tmp[ops[o][j]] = tmp[ops[o][j + 1]];
      }
      tmp[ops[o].back()] = a;
    }
    uint64 hash = 9;
    for (int i = 0; i < n; ++i) hash = hash * seed + tmp[i];
    ps.emplace_back(hash, mask);
  }
  std::sort(ps.begin(), ps.end());
  for (int mask = 0; mask < pw[x]; ++mask) {
    static char tmp[N];
    for (int i = 0; i < n; ++i) tmp[i] = s[i];
    for (int i = 0; i < x; ++i) {
      int o = mask / pw[x - 1 - i] % m;
      char a = tmp[ops[o].back()];
      for (int j = ops[o].size() - 1; j > 0; --j) {
        tmp[ops[o][j]] = tmp[ops[o][j - 1]];
      }
      tmp[ops[o][0]] = a;
    }
    uint64 hash = 9;
    for (int i = 0; i < n; ++i) hash = hash * seed + tmp[i];
    auto it = std::lower_bound(ps.begin(), ps.end(), std::make_pair(hash, int(0)));
    if (it != ps.end() && it->first == hash) {
      for (int i = 0; i < x; ++i) {
        printf("%d ", mask / pw[x - 1 - i] % m + 1);
      }
      for (int i = 0; i < y; ++i) {
        printf("%d ", it->second / pw[y - 1 - i] % m + 1);
      }
      puts("");
      return true;
    }
  }
  return false;
}

int main() {
  int n, m;
  scanf("%d%d%s%s", &n, &m, s, t);
  for (int i = 0; i < m; ++i) {
    int c;
    scanf("%d", &c);
    ops[i].resize(c);
    for (int j = 0; j < c; ++j) {
      scanf("%d", &ops[i][j]);
      --ops[i][j];
    }
  }
  bool found = false;
  for (int i = 1; i <= 10 && !found; ++i) {
    found = solve(n, m, i);
  }
  if (!found) puts("NIE");
  return 0;
}
