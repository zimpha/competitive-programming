#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <cstring>

constexpr int N = 5e4 + 10;

using pii = std::pair<int, int>;
bool has[N], added[N];
std::vector<pii> adj[N];
std::vector<int> tree[N];
int memo[N][2];
int n, l, s;

void dfs(int x, int from, int sum) {
  if (2 * sum >= s) return;
  for (auto &&e: adj[x]) {
    if (e.first == from) continue;
    tree[x].push_back(e.first);
    dfs(e.first, x, sum + e.second);
  }
}

int mvc(int x, int prev) {
  int place = 1, dont_place = 0, already_placed = 0;
  if (memo[x][prev] != -1) return memo[x][prev];
  // place here
  for (auto &&v: tree[x]) {
    place += mvc(v, 1);
  }
  // don't place here
  if (prev) { // we can't skip if we didn't place before
    for (auto &&v: tree[x]) {
      dont_place += mvc(v, 0);
    }
  }

  // already has lamp
  if (has[x]) {
    for (auto &&v: tree[x]) {
      already_placed += mvc(v, 1);
    }
  }

  int ret = place;
  if (prev) ret = std::min(ret, dont_place);
  if (has[x]) ret = std::min(ret, already_placed);
  return memo[x][prev] = ret;
}

int main() {
  scanf("%d%d", &n, &s);
  for (int i = 0; i < n - 1; ++i) {
    int a, b, d;
    scanf("%d%d%d", &a, &b, &d);
    adj[a].emplace_back(b, d);
    adj[b].emplace_back(a, d);
  }
  scanf("%d", &l);
  for (int i = 0, x; i < l; ++i) {
    scanf("%d", &x);
    has[x] = true;
  }

  memset(memo,-1,sizeof(memo));
  added[1] = true;
  dfs(1, -1, 0);
  printf("%d\n", std::min(mvc(1,1), mvc(1,0)));
  return 0;
}
