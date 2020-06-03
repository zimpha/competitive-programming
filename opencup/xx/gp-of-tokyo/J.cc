#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

using uint64 = unsigned long long;

const int N = 3e5 + 10, mod = 1e9 + 7;

std::unordered_map<uint64, bool> dp;
char rule[10], s[N];

uint64 apply(uint64 x, int i) {
  int x3 = x >> i & 1;
  int x2 = x >> (i + 1) & 1;
  int x1 = x >> (i + 2) & 1;
  uint64 ret = x % (uint64(1) << i);
  ret |= uint64(rule[x1 + 2 * x2 + 4 * x3] - '0') << i;
  ret |= x >> (i + 3) << (i + 1);
  return ret;
}

int len(uint64 x) {
  int l = 0;
  for (int i = 0; i < 64; ++i) {
    if (x >> i & 1) l = i;
  }
  return l;
}

bool check(uint64 x) {
  if (dp.count(x)) return dp[x];
  int l = len(x);
  if (l % 2 == 0) return dp[x] = 0;
  if (l == 1) return dp[x] = x & 1;
  for (int i = 0; i + 3 <= l; ++i) {
    if (check(apply(x, i))) return dp[x] = 1;
  }
  return dp[x] = 0;
}

bool is_same(uint64 x, uint64 y) {
  if (len(x) % 2 == 0 || len(y) % 2 == 0) return false;
  for (int i = 0; i < 10; ++i) {
    for (int mask = 0; mask < (1 << i); ++mask) {
      if (check(x << i | mask) != check(y << i | mask)) return false;
    }
  }
  return true;
}

std::vector<std::pair<int, int>> trans;
std::vector<uint64> states;

void build() {
  std::unordered_map<uint64, int> mp;
  std::vector<uint64> queue = {1};
  states.clear(); dp.clear();
  for (size_t i = 0; i < queue.size(); ++i) {
    auto x = queue[i];
    bool found = false;
    for (auto &y: states) {
      if (is_same(x, y)) found = true;
      if (found) {
        mp[x] = mp[y];
        break;
      }
    }
    if (found) continue;
    mp[x] = states.size();
    states.push_back(x);
    queue.push_back(x << 1 | 0);
    queue.push_back(x << 1 | 1);
  }
  trans.resize(states.size());
  for (size_t i = 0; i < states.size(); ++i) {
    trans[i] = {mp[states[i] << 1 | 0], mp[states[i] << 1 | 1]};
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", rule, s);
    build();
    int m = trans.size();
    int n = strlen(s);
    std::vector<uint64> f(m), g(m);
    f[0] = 1;
    for (int i = 0; i < n; ++i) {
      g.assign(m, 0);
      for (int j = 0; j < m; ++j) if (f[j]) {
        if (s[i] == '0' || s[i] == '?') g[trans[j].first] += f[j];
        if (s[i] == '1' || s[i] == '?') g[trans[j].second] += f[j];
      }
      for (int j = 0; j < m; ++j) f[j] = g[j] % mod;
    }
    uint64 ret = 0;
    for (int j = 0; j < m; ++j) {
      if (check(states[j])) ret += f[j];
    }
    printf("%llu\n", ret % mod);
  }
  return 0;
}
