#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

int dsu[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<int> a(k), b(k);
  for (int i = 0; i < k; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    b[i] += n;
  }
  int steps = 0, ret = -1;
  while (n != 0 && ret == -1) {
    // v mod n = u mod n <=> u and v are connected after m steps
    std::vector<int> xs;
    for (int i = 0; i < k; ++i) {
      xs.push_back(a[i] % n);
      xs.push_back(b[i] % n);
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    auto x = (n + m) % n, y = n;
    if (xs.size() < n) {
      for (int i = 0; i < k; ++i) a[i] %= n, b[i] %= n;
      steps += m;
      n = x, m = y - x;
      continue;
    }
    for (int i = 0; i < n; ++i) dsu[i] = i;
    int cnt = n;
    for (int i = 0; i < k; ++i) {
      int u = get(a[i] % n), v = get(b[i] % n);
      if (u != v) --cnt, dsu[u] = v;
    }
    if (cnt != 1) {
      for (int i = 0; i < k; ++i) a[i] %= n, b[i] %= n;
      steps += m;
      n = x, m = y - x;
      continue;
    }

    auto check = [&](int mid) {
      if (n + m - mid > k + 1) return false;
      int s = mid;
      for (int i = 0; i < n + m - s; ++i) dsu[i] = i;
      int cnt = n + m - s;
      for (int i = 0; i < k; ++i) {
        int u = a[i], v = b[i];
        if (u < s) u += (s - u + n - 1) / n * n;
        if (v < s) v += (s - v + n - 1) / n * n;
        u -= s, v -= s;
        u = get(u); v = get(v);
        if (u != v) dsu[u] = v, --cnt;
      }
      return cnt == 1;
    };

    int left = 0, right = m;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      if (check(mid)) right = mid;
      else left = mid + 1;
    }
    ret = steps + left;
  }
  if (m == 1 && ret == -1) ret = steps;
  printf("%d\n", ret);
  return 0;
}
