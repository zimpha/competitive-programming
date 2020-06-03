#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using int64 = long long;

template<typename T>
class DynamicRMQ {
public:
  void build(const std::vector<T> &data) {
    build(&data[0], data.size());
  }
  void build(const T *data, int n) {
    u.resize(n * 2);
    for (int i = 0; i < n; ++i) {
      u[i + n] = data[i];
    }
    for (int i = n - 1; i > 0; --i) {
      u[i] = std::max(u[i << 1], u[i << 1 | 1]);
    }
  }
  void modify(int p, const T& v) {
    for (u[p += u.size() / 2] = v; p > 1; p >>= 1) {
      u[p >> 1] = std::max(u[p], u[p ^ 1]);
    }
  }
  T query(int l, int r, T res = T()) {// [l, r)
    const int n = u.size() >> 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = std::max(res, u[l++]);
      if (r & 1) res = std::max(res, u[--r]);
    }
    return res;
  }
private:
  std::vector<T> u;
};

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n + 2);
  std::vector<int64> s(n + 2), ss(n + 2);
  std::vector<int64> p(n + 2);
  int extra = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    extra ^= (a[i] & 1);
  }
  std::sort(a.begin() + 1, a.begin() + n + 1);
  std::vector<int> d = {0};
  int m = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i]) d.push_back(a[i]), ++m;
  }
  if (d.back() >= m + 1) {
    puts("-1");
    return 0;
  }
  d.push_back(m + 1);
  std::reverse(d.begin(), d.end());
  std::vector<int64> sum(m + 2);
  sum[m + 1] = 0;
  for (int i = m; i >= 1; --i) sum[i] = sum[i + 1] + d[i];
  p[0] = s[m + 1] = 0;
  for (int i = 1; i <= m; ++i) p[i] = p[i - 1] + d[i];
  for (int i = m; i >= 1; --i) {
    s[i] = 0;
    if (d[i] <= i + 1) s[i] = sum[i];
    else {
      int l = i, r = m;
      while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (d[mid] > i + 1) l = mid;
        else r = mid - 1;
      }
      s[i] = (int64)(i + 1) * (l - i + 1) + sum[l + 1];
    }
    ss[i] = 0;
    if (i + 1 <= m) {
      if (d[i + 1] <= i) ss[i] = sum[i + 1];
      else {
        int l = i + 1, r = m;
        while (l < r) {
          int mid = (l + r + 1) >> 1;
          if (d[mid] > i) l = mid;
          else r = mid - 1;
        }
        ss[i] = (int64)i * (l - i) + sum[l + 1];
      }
    }
  }
  std::vector<int64> suffix_min(m + 2), prefix_max(m + 2);
  for (int k = 0; k <= m; ++k) {
    suffix_min[k] = s[k + 1] + (int64)k * (k + 1) - p[k];
    prefix_max[k] = p[k] - (int64)k * (k - 1) - ss[k];
  }
  for (int k = m - 1; k >= 0; --k) {
    suffix_min[k] = std::min(suffix_min[k], suffix_min[k + 1]);
  }
  std::vector<int> res;
  std::vector<int> valid(m + 1);
  valid[0] = 1;
  for (int i = 1; i <= m; ++i) {
    valid[i] &= valid[i - 1] && (p[i] <= (int64)i * i + ss[i]);
  }
  DynamicRMQ<int64> rmq;
  rmq.build(prefix_max);
  for (int bob = 0; bob <= m; ++bob) if (bob % 2 == extra) {
    int l = 0, r = m, e;
    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (d[mid] > bob) l = mid;
      else r = mid - 1;
    }
    e = l;
    assert(d[e] > bob && d[e + 1] <= bob);
    if (bob > suffix_min[e]) continue;
    //printf("1: %d\n", bob);
    //if (valid[std::min(bob, e)]) {
      //printf("2: %d\n", bob);
      if (bob < e) {
        if (bob >= rmq.query(bob + 1, e + 1)) {
          res.push_back(bob);
        }
      } else {
        res.push_back(bob);
      }
    //}
  }
  if (res.empty()) {
    puts("-1");
  } else {
    for (auto &&x: res) printf("%d ", x);
    puts("");
  }
  return 0;
}