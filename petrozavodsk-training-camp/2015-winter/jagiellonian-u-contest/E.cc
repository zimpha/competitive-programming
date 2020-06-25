#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

using int64 = long long;

const int N = 1e6 + 10;
std::pair<int, int> a[21][N], t_a[N];
int dp[N], pool_ptr;

struct Node {
  int prev, next;
  int idx;
} pool[N];

struct Block {
  int first, last;
  int idx;
  void merge(Block &rhs, std::pair<int, int> *w) {
    while (last != -1) {
      int e1 = pool[last].idx;
      int e2 = pool[rhs.first].idx;
      if (dp[w[e1].second] < dp[w[e2].second]) break;
      if (last == first) last = first = -1;
      else last = pool[last].prev;
    }
    if (first == -1) {
      first = rhs.first;
      last = rhs.last;
    } else {
      pool[rhs.first].prev = last;
      pool[last].next = rhs.first;
      last = rhs.last;
    }
  }
};

int new_node(int idx) {
  pool[pool_ptr].prev = pool[pool_ptr].next = -1;
  pool[pool_ptr].idx = idx;
  return pool_ptr++;
}

void build(int l, int r, int d) {
  if (l + 1 == r) {
    a[d][l] = t_a[l];
    return;
  }
  int m = (l + r) >> 1;
  build(l, m, d + 1);
  build(m, r, d + 1);
  int x = l, y = m, z = l;
  for (; x < m && y < r; ) {
    if (a[d + 1][x] < a[d + 1][y]) a[d][z++] = a[d + 1][x++];
    else a[d][z++] = a[d + 1][y++];
  }
  while (x < m) a[d][z++] = a[d + 1][x++];
  while (y < r) a[d][z++] = a[d + 1][y++];
}

void solve(int l, int r, int d) {
  std::pair<int, int> *w = a[d];
  if (l + 1 == r) {
    if (dp[w[l].second] == 1e9) dp[w[l].second] = 1;
    return;
  }
  int m = (l + r) >> 1;
  solve(l, m, d + 1);

  // maintain the first and last node of list
  pool_ptr = 0;
  std::vector<Block> stk;
  //printf("l=%d r=%d: ", l, r);
  for (int i = l; i < r; ++i) {
    //printf("(%d %d) ", a[i].first, a[i].second);
    if (w[i].second < m) {
      while (!stk.empty()) {
        if (stk.back().first == -1) {
          stk.pop_back();
          continue;
        }
        int e = pool[stk.back().first].idx;
        if (w[i].second < w[e].second) break;
        if (stk.back().first == stk.back().last) {
          stk.back().first = stk.back().last = -1;
        } else {
          stk.back().first = pool[stk.back().first].next;
        }
      }
      if (stk.empty() || stk.back().idx != -1) {
        int p = new_node(i);
        stk.push_back((Block){p, p, -1});
      } else {
        int e = pool[stk.back().first].idx;
        if (dp[w[i].second] < dp[w[e].second]) {
          int p = new_node(i);
          pool[p].next = stk.back().first;
          pool[stk.back().first].prev = p;
          stk.back().first = p;
        }
      }
    } else {
      Block last = (Block){-1, -1, -1};
      while (!stk.empty()) {
        if (stk.back().idx != -1 && w[i].second > w[stk.back().idx].second) break;
        last.merge(stk.back(), w);
        stk.pop_back();
      }
      if (last.first != -1) {
        int e = pool[last.first].idx;
        dp[w[i].second] = std::min(dp[w[i].second], dp[w[e].second] + 1);
        last.idx = i;
        stk.push_back(last);
      }
    }
  }
  //puts("");
  //for (int i = m; i < r; ++i) printf("%d ", dp[i]);
  //puts("");
  solve(m, r, d + 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &t_a[i].first);
      t_a[i].second = i;
    }
    t_a[n] = {1e9 + 1, n};
    for (int i = 0; i <= n; ++i) dp[i] = 1e9;
    build(0, n + 1, 0);
    solve(0, n + 1, 0);
    printf("%d\n", dp[n] - 1);
  }
  return 0;
}
