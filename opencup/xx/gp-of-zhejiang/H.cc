#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10, M = 2 * N;

struct Block {
  int64 sum, cnt, val;
  bool operator == (const Block &rhs) const {
    return sum * rhs.cnt == cnt * rhs.sum;
  }
  bool operator < (const Block &rhs) const {
    return sum * rhs.cnt < cnt * rhs.sum;
  }
  Block operator + (const Block &rhs) const {
    return {sum + rhs.sum, cnt + rhs.cnt, val + rhs.val + cnt * rhs.sum};
  }
  Block operator - (const Block &rhs) const {
    return {sum - rhs.sum, cnt - rhs.cnt, val - rhs.val - (cnt - rhs.cnt) * rhs.sum};
  }
};

std::vector<Block> vs[N];
Block T[M << 2];

template<int sign>
void ins(int o, int l, int r, int x, Block &v) {
  if (l + 1 == r) {
    if (sign > 0) T[o] = T[o] + v;
    else T[o] = T[o] - v;
    return;
  }
  int m = (l + r) >> 1;
  if (x < m) ins<sign>(o << 1, l, m, x, v);
  else ins<sign>(o << 1 | 1, m, r, x, v);
  T[o] = T[o << 1 | 1] + T[o << 1];
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  std::vector<Block> xs;
  std::vector<Block> stk;
  for (int i = 0; i < n; ++i) {
    Block now = {a[i], 1};
    while (!stk.empty() && stk.back() < now) {
      now = stk.back() + now;
      stk.pop_back();
    }
    xs.push_back(now);
    stk.push_back(now);
  }
  stk.clear();
  for (int i = n - 1; i >= 0; --i) {
    Block now = {a[i], 1, a[i]};
    while (!stk.empty() && stk.back() < now) {
      now = stk.back() + now;
      vs[i].push_back(stk.back());
      stk.pop_back();
    }
    xs.push_back(now);
    stk.push_back(now);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  for (auto &e: stk) {
    auto x = std::lower_bound(xs.begin(), xs.end(), e) - xs.begin();
    ins<1>(1, 0, xs.size(), x, e);
  }
  std::vector<Block> stk2;
  for (int i = 0; i < n; ++i) {
    auto x = std::lower_bound(xs.begin(), xs.end(), stk.back()) - xs.begin();
    ins<-1>(1, 0, xs.size(), x, stk.back());
    stk.pop_back();
    std::reverse(vs[i].begin(), vs[i].end());
    for (auto &e: vs[i]) {
      stk.push_back(e);
      auto x = std::lower_bound(xs.begin(), xs.end(), e) - xs.begin();
      ins<1>(1, 0, xs.size(), x, e);
    }
    printf("%lld ", T[1].val + (int64)a[i] * (n - 1));
    Block now = {a[i], 1, a[i]};
    while (!stk2.empty() && stk2.back() < now) {
      auto x = std::lower_bound(xs.begin(), xs.end(), stk2.back()) - xs.begin();
      ins<-1>(1, 0, xs.size(), x, stk2.back());
      now = stk2.back() + now;
      stk2.pop_back();
    }
    x = std::lower_bound(xs.begin(), xs.end(), now) - xs.begin();
    ins<1>(1, 0, xs.size(), x, now);
    stk2.push_back(now);
  }
  puts("");
  return 0;
}
