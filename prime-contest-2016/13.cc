#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

int table[26][26];
int cost[26][26], id[26];
int go[26], back[26];
int dp[27][1 << 13][2], cnt;

bool find_cycles() {
  static int degree[26], visited[26];
  memset(degree, 0, sizeof(degree));
  memset(visited, 0, sizeof(visited));
  for (int i = 0; i < 26; ++i) {
    degree[go[i]]++;
  }
  std::vector<int> queue;
  for (int i = 0; i < 26; ++i) {
    if (!degree[i]) queue.push_back(i);
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    visited[u] = true;
    if (--degree[go[u]] == 0) queue.push_back(go[u]);
  }
  memset(id, -1, sizeof(id));
  for (int i = 0; i < 26; ++i) {
    if (visited[i]) continue;
    assert(degree[i] == 1);
    if (go[i] == i) visited[i] = true;
    else {
      for (int j = i; !visited[j]; j = go[j]) {
        visited[j] = true;
        back[go[j]] = j;
        id[j] = cnt;
      }
      ++cnt;
    }
  }
  return cnt && queue.empty();
}

int main() {
  int n, c;
  std::cin >> n >> c;
  std::string s, t;
  std::cin >> s >> t;
  memset(table, 0, sizeof(table));
  memset(cost, 0, sizeof(cost));
  for (int i = 0; i < n; ++i) {
    table[s[i] - 'a'][t[i] - 'a']++;
  }
  for (int from = 0; from < 26; ++from) {
    go[from] = -1;
    for (int to = 0; to < 26; ++to) {
      cost[from][to] = (from == to ? 0 : c);
      for (int target = 0; target < 26; ++target) {
        if (to != target) cost[from][to] += table[from][target];
      }
      if (go[from] == -1 || cost[from][to] < cost[from][go[from]]) {
        go[from] = to;
      }
    }
  }
  cnt = 0;
  bool bad = find_cycles();
  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0;
  for (int i = 0; i < 26; ++i) {
    for (int mask = 0; mask < (1 << cnt); ++mask) {
      for (int diff = 0; diff < 2; ++diff) {
        if (dp[i][mask][diff] == -1) continue;
        for (int to = 0; to < 26; ++to) {
          int new_mask = mask, new_diff = diff | (to != go[i]);
          if (id[i] >= 0 && to != go[i]) new_mask |= 1 << id[i];
          if (id[to] >= 0 && i != back[to]) new_mask |= 1 << id[to];
          int &ret = dp[i + 1][new_mask][new_diff];
          if (ret == -1 || ret > dp[i][mask][diff] + cost[i][to]) {
            ret = dp[i][mask][diff] + cost[i][to];
          }
        }
      }
    }
  }
  int ans = 1e9;
  for (int mask = 0; mask < (1 << cnt); ++mask) {
    for (int diff = 0; diff < 2; ++diff) {
      if (bad && !diff) continue;
      if (dp[26][mask][diff] == -1) continue;
      ans = std::min(ans, dp[26][mask][diff] + (cnt - __builtin_popcount(mask)) * c);
    }
  }
  std::cout << ans << std::endl;
  return 0;
}
