#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

struct Node {
  int64 sum;
  int cnt;
} T[N << 2];

void build(int o, int l, int r) {
  T[o].sum = T[o].cnt = 0;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}

void add(int o, int l, int r, int x, int64 v) {
  if (l + 1 == r) {
    T[o].sum += v;
    if (v > 0) T[o].cnt++;
    else T[o].cnt--;
    return;
  }
  int m = (l + r) >> 1;
  if (x < m) add(o << 1, l, m, x, v);
  else add(o << 1 | 1, m, r, x, v);
  T[o].sum = T[o << 1].sum + T[o << 1 | 1].sum;
  T[o].cnt = T[o << 1].cnt + T[o << 1 | 1].cnt;
}

int64 query(int o, int l, int r, int k) {
  if (k == 0) return 0;
  if (l + 1 == r) return T[o].sum / T[o].cnt * k;
  int m = (l + r) >> 1;
  if (T[o << 1 | 1].cnt >= k) return query(o << 1 | 1, m, r, k);
  else return T[o << 1 | 1].sum + query(o << 1, l, m, k - T[o << 1 | 1].cnt);
}

int64 solve(const std::vector<std::pair<int64, int>> &a, int64 n1, int h1, int64 n2, int h2) {
  int n = a.size();
  std::vector<int64> left(n);
  for (int i = n - 1; i >= 0; --i) {
    left[i] = a[i].first - a[i].second;
    if (i + 1 < n && a[i].first >= left[i + 1]) {
      left[i] = std::min(left[i], left[i + 1]);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (i && a[i - 1].first >= left[i]) {
      left[i] = std::min(left[i], left[i - 1]);
    }
  }
  std::vector<std::pair<int64, int>> gap;
  int64 ret = n1 + n2;
  for (int i = n - 1, j; i >= 0; i = j) {
    for (j = i; j >= 0 && left[i] <= a[j].first; --j);
    if (j >= 0) gap.emplace_back(left[i] - a[j].first, i - j);
    else gap.emplace_back(0, i - j);
    ret = std::max<int64>(ret, i - j + n1 + n2);
  }
  std::reverse(gap.begin(), gap.end());
  std::vector<int64> xs;
  for (size_t i = 0; i < gap.size(); ++i) {
    xs.push_back(gap[i].first % h2);
    if (i) gap[i].second += gap[i - 1].second;
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  int m = xs.size();
  build(1, 0, m);

  int64 sum = 0;
  auto ins = [&](int64 len) {
    sum += len / h2;
    len %= h2;
    if (len == 0) return;
    auto x = std::lower_bound(xs.begin(), xs.end(), len) - xs.begin();
    add(1, 0, m, x, (len + h1 - 1) / h1);
  };

  auto del = [&](int64 len) {
    sum -= len / h2;
    len %= h2;
    if (len == 0) return;
    auto x = std::lower_bound(xs.begin(), xs.end(), len) - xs.begin();
    add(1, 0, m, x, -((len + h1 - 1) / h1));
  };

  auto verify = [&] () {
    int64 ts = sum, tn1 = n1, tn2 = n2;
    if (ts <= tn2) tn2 -= ts, ts = 0;
    else ts -= tn2, tn2 = 0;
    if (ts > tn1 / (h2 / h1)) return false;
    tn1 -= h2 / h1 * ts;
    if (tn2 >= T[1].cnt) return true;
    return tn1 >= T[1].sum - query(1, 0, m, tn2);
  };

  for (size_t i = 0, j = 1; i < gap.size(); ++i) {
    if (i <= j - 1) del(gap[i].first);
    while (j < gap.size()) {
      ins(gap[j].first);
      if (!verify()) {
        del(gap[j].first);
        break;
      }
      ++j;
    }
    // [i + 1, j - 1] is valid
    if (i + 1 <= j - 1) {
      ret = std::max(ret, n1 + n2 + gap[j - 1].second - (i ? gap[i - 1].second : 0));
    }
  }
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int64, int>> a(n);
  for (int i = 0; i < n; ++i) scanf("%lld%d", &a[i].first, &a[i].second);
  int64 n1, n2;
  int h1, h2;
  scanf("%lld%d%lld%d", &n1, &h1, &n2, &h2);
  if (h1 > h2) std::swap(h1, h2), std::swap(n1, n2);
  if (h1 == h2) n2 += n1, n1 = 0, h1 = 1;
  std::sort(a.begin(), a.end());
  int64 ret = solve(a, n1, h1, n2, h2);
  std::reverse(a.begin(), a.end());
  for (int i = 0; i < n; ++i) {
    a[i].first = -a[i].first;
  }
  ret = std::max(ret, solve(a, n1, h1, n2, h2));
  printf("%lld\n", ret);
  return 0;
}
