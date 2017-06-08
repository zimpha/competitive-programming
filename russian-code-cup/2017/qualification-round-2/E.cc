#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int N = 100000 + 10, B = 400;
std::vector<int> ql[B];

struct event_t {
  int type;// 0: answer, 1: max, 2: min
  int idx;
  int value;
  event_t() = default;
  event_t(int t, int i, int v): type(t), idx(i), value(v) {}
};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, q;
    scanf("%d", &n);
    std::vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      a[i] += a[i - 1];
    }
    std::vector<int> xs(a.begin(), a.end());
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    for (auto &&x: a) {
      x = std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    for (int i = 0; i < B; ++i) {
      ql[i].clear();
    }
    scanf("%d", &q);
    std::vector<int> l(q), r(q);
    for (int i = 0; i < q; ++i) {
      scanf("%d%d", &l[i], &r[i]);
      --l[i];
      ql[l[i] / B].push_back(i);
    }
    std::vector<int> min(xs.size()), max(xs.size());
    long long ret = 0;
    for (int b = 0; b < B; ++b) {
      std::vector<int> &q = ql[b];
      if (q.empty()) continue;
      std::sort(q.begin(), q.end(), [&](int x, int y) {
        return r[x] < r[y];
      });
      for (int i = 0; i < xs.size(); ++i) {
        min[i] = n + 1;
        max[i] = -1;
      }
      int i = b * B + B, j = 0, ans = 0;
      auto roll = [&](const event_t &e) {
        if (e.type == 0) ans = e.value;
        else if (e.type == 1) max[e.idx] = e.value;
        else min[e.idx] = e.value;
      };
      std::vector<event_t> stack;
      for (; j < q.size() && r[q[j]] < i; ++j) {
        for (int k = l[q[j]]; k <= r[q[j]]; ++k) {
          int v = a[k];
          stack.emplace_back(0, 0, ans);
          stack.emplace_back(1, v, max[v]);
          stack.emplace_back(2, v, min[v]);
          max[v] = std::max(max[v], k);
          min[v] = std::min(min[v], k);
          ans = std::max(ans, max[v] - min[v]);
        }
        //printf("%d %d\n", q[j], ans);
        ret += ans;
        while (stack.size()) {
          roll(stack.back());
          stack.pop_back();
        }
      }
      for (; i <= n; ++i) {
        int v = a[i];
        max[v] = std::max(max[v], i);
        min[v] = std::min(min[v], i);
        ans = std::max(ans, max[v] - min[v]);
        for (; j < q.size() && r[q[j]] == i; ++j) {
          for (int k = l[q[j]]; k < b * B + B; ++k) {
            int v = a[k];
            stack.emplace_back(0, 0, ans);
            stack.emplace_back(1, v, max[v]);
            stack.emplace_back(2, v, min[v]);
            max[v] = std::max(max[v], k);
            min[v] = std::min(min[v], k);
            ans = std::max(ans, max[v] - min[v]);
          }
          //printf("%d %d\n", q[j], ans);
          ret += ans;
          while (stack.size()) {
            roll(stack.back());
            stack.pop_back();
          }
        }
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}
