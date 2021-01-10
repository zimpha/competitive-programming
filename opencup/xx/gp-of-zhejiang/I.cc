#include <cstdio>
#include <queue>
#include <algorithm>

using i64 = long long;

const int N = 1e5 + 10;

i64 a[N], sum[N], mx[N], A;
int n, B;

// make a[l..r] same as a[l]
i64 need(int l, int r) {
  return a[l] * (r - l) - (sum[r] - sum[l]);
}

i64 solve() {
  std::sort(a, a + n, std::greater<i64>());
  for (int i = 0; i < n; ++i) {
    sum[i] = a[i];
    if (i) sum[i] += sum[i - 1];
  }

  std::deque<std::pair<i64, int>> queue;
  for (int i = 0; i < n; ++i) queue.emplace_back(a[i], 1);
  for (int nn = (n + B - 1) / B * B + 1, now = n; nn > 1; ) {
    for (i64 rest = A; rest; ) {
      auto e = queue.back();
      queue.pop_back();
      i64 need = A + 1;
      if (!queue.empty()) {
        need = e.second * (queue.back().first - e.first);
      }
      if (need <= rest) {
        rest -= need;
        queue.back().second += e.second;
        continue;
      }
      e.first += rest / e.second;
      i64 rem = rest % e.second;
      if (rem) queue.emplace_back(e.first + 1, rem);
      queue.emplace_back(e.first, e.second - rem);
      break;
    }
    for (int rest = B; rest; ) {
      int del = std::min(rest, queue.front().second);
      rest -= del;
      queue.front().second -= del;
      if (queue.front().second == 0) queue.pop_front();
    }
    now -= B, nn -= B;
    if (now < nn) queue.emplace_back(0, nn - now), now = nn;
  }
  i64 ret = queue.front().first + A;

  int m = 0;
  auto add = [&](int l, int r, int times) {
    i64 s = sum[r] - (l ? sum[l - 1] : 0) + A * times;
    int ns = r - l + 1, rest = r + 1 - B * times;
    i64 avg = s / ns, rem = std::max<i64>(0, s % ns - (ns - rest));
    m = std::max(m, (rest - 1) / B);
    mx[(rest - 1) / B] = std::max(mx[(rest - 1) / B], avg * rest + rem);
  };

  for (int i = 0; i <= n; ++i) mx[i] = 0;
  for (int r = 0, times = 0; r < n; r += B) {
    while (need(B * times, r) > A * times) ++times;
    if (times && need(B * times - B, r) <= A * times) {
      add(B * times - B, r, times);
    } else {
      int left = 0, right = r;
      while (left < right) {
        int mid = (left + right - 1) >> 1;
        if (need(mid, r) <= A * times) right = mid;
        else left = mid + 1;
      }
      add(left, r, times);
    }
  }
  for (int i = m; i >= 1; --i) {
    i64 s = mx[i] + A;
    int c = i * B + 1;
    i64 v = s / c, r = s % c;
    r = std::max<i64>(r - B, 0);
    mx[i - 1] = std::max(mx[i - 1], v * (c - B) + r);
  }
  return std::max(mx[0] + A, ret);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%lld%d", &n, &A, &B);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
    }
    if (n == B) {
      printf("%lld\n", A + *std::max_element(a, a + n));
      continue;
    }
    i64 ret = solve();
    for (int i = 0; i < n - B; ++i) a[i] = (A - 1) / B;
    for (int i = n - B; i < n; ++i) a[i] = 0;
    ret = std::max(ret, solve());
    printf("%lld\n", ret);
  }
  return 0;
}
