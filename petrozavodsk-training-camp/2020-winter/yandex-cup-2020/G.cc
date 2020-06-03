#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e6 + 10;

std::vector<int> dv[N], qs[N * 2];
int mp[N];

// check is n = x^k for some integer x
bool kth_power(int n, int k) {
  if (k == 1 || n == 1) return true;
  if (k > 20) return false;
  int last = -1, cnt = 0;
  while (n != 1) {
    int p = mp[n];
    if (p == last) ++cnt;
    else {
      if (cnt % k != 0) return false;
      cnt = 1;
    }
    n /= p;
  }
  return cnt % k == 0;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    for (int j = i; j <= m; j += i) {
      if (i != 1 && mp[j] == 0) mp[j] = i;
      dv[j].push_back(i);
    }
  }
  int ret = 0;
  for (int p = -m; p <= m; ++p) {
    if (p == 0) ++ret;
    else if (p > 0) {
      if (n % 2 == 1) ++ret;
      else ret += !kth_power(p, n - 1);
    } else {
      ret += !kth_power(-p, n - 1);
    }
  }

  auto pow = [&] (int x, int k) {
    int64 r = 1;
    for (int i = 0; i < k; ++i) {
      r *= x;
      if (r < -m || r > m) return m * 100;
    }
    return (int)r;
  };

  for (int q = -m; q <= m; ++q) if (q != 0) {
    for (auto &x: dv[std::abs(q)]) {
      auto v1 = pow(x, n - 1), v2 = pow(-x, n - 1);
      if (v1 < -m || v1 > m) continue;
      auto p1 = -q / x - v1;
      auto p2 = q / x - v2;
      if (-m <= p1 && p1 <= m) {
        printf("q=%d x=%d p1=%d\n", q, x, p1);
        qs[p1 + m].push_back(q);
      }
      if (-m <= p2 && p2 <= m) {
        printf("q=%d x=%d p1=%d\n", q, -x, p2);
        qs[p2 + m].push_back(q);
      }
    }
  }
  for (int p = -m; p <= m; ++p) {
    auto &a = qs[p + m];
    for (size_t i = 0, j; i < a.size(); i = j) {
      for (j = i; j < a.size() && a[i] == a[j]; ++j);
      if (j - i == 1) {
        printf("p=%d q=%d\n", p, a[i]);
        ++ret;
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}
