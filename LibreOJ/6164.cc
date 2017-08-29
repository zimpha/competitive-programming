#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 50000 + 10, P = 333;

struct query_t {
  int l, r, k, id;
  bool operator < (const query_t &rhs) const {
    return l / P == rhs.l / P ? r < rhs.r : l < rhs.l;
  }
} ql[N];

std::vector<int> fac[N];
int mu[N], a[N], n, m;

namespace Block {
  int u[N], cnt[N];
  void init(int n) {
    for (int i = 0; i <= n; ++i) {
      cnt[i] = u[i] = 0;
    }
  }
  void add(int x, int v) {
    for (auto &&e: fac[x]) u[e] += v;
  }
  void add(int x) {
    add(cnt[x], -1);
    ++cnt[x];
    add(cnt[x], +1);
  }
  void del(int x) {
    add(cnt[x], -1);
    --cnt[x];
    add(cnt[x], +1);
  }
  int ask(int x) {
    int ret = 0;
    for (auto &&e: fac[x]) ret += mu[e] * u[e];
    return ret;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);
  for (int i = mu[1] = 1; i <= n; ++i) if (mu[i]) {
    fac[i].push_back(i);
    for (int j = i + i; j <= n; j += i) {
      fac[j].push_back(i);
      mu[j] -= mu[i];
    }
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &ql[i].l, &ql[i].r, &ql[i].k);
    --ql[i].l, --ql[i].r;
    ql[i].id = i;
  }
  std::sort(ql, ql + m);
  Block::init(n);
  std::vector<int> ans(m);
  for (int i = 0, l = 0, r = -1; i < m; ++i) {
    int L = ql[i].l, R = ql[i].r;
    while (r < R) Block::add(a[++r]);
    while (r > R) Block::del(a[r--]);
    while (l < L) Block::del(a[l++]);
    while (l > L) Block::add(a[--l]);
    ans[ql[i].id] = Block::ask(ql[i].k);
  }
  for (int i = 0; i < m; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
