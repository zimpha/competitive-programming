#include <cstdio>
#include <vector>

using int64 = long long;
const int64 inf = 1ll << 61;

// max(\sum a_i) where \oplus a_i = x, 0 <= a_i <= m
int64 max_sum(int64 n, int64 m, int64 x) {
  std::vector<int64> cnt(60);
  int64 u = n, v = 0;
  for (int i = 59; i >= 0; --i) {
    int64 need = n;
    if ((x >> i & 1) != n % 2) --need;
    if (m >> i & 1) {
      cnt[i] = need;
      if (need > v) u = need - v, v = n - u;
    } else {
      if (v % 2 != need % 2) need = v - 1;
      else need = v;
      if (need < 0) return -1;
      cnt[i] = need;
    }
  }
  int64 ret = 0;
  for (int i = 0; i < 60; ++i) {
    if (cnt[i] >= inf / (int64(1) << i)) ret = inf;
    else ret += cnt[i] * (int64(1) << i);
    if (ret >= inf) break;
  }
  if (ret % 2 != x % 2) --ret;
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, s, x;
    scanf("%lld%lld%lld", &n, &s, &x);
    if (s < x || (s - x) % 2) {
      puts("-1");
      continue;
    }
    if (n == 1) {
      if (s != x) puts("-1");
      else printf("%lld\n", x);
    } else if (n == 2) {
      s = (s - x) / 2;
      int64 a = 0, b = 0;
      for (int i = 0; i < 60; ++i) {
        if (x >> i & 1) a |= int64(1) << i;
        if (x >> i & 1) b = int64(1) << i;
      }
      a ^= b;
      if (s & x) puts("-1");
      else printf("%lld\n", b + s);
    } else if (n == 3) {
      int64 ret = 0, extra = 0;
      s = (s - x) / 2;
      std::vector<std::pair<int, int64>> cnt;
      for (int i = 59; i >= 0; --i) {
        int sum = 0;
        if (s >> i & 1) sum += 2;
        if (x >> i & 1) sum += 1;
        if (sum == 1 || sum == 2) cnt.emplace_back(sum, int64(1) << i);
        if (sum == 3) extra |= int64(1) << i;
      }
      if (cnt.size() == 0) ret = 0;
      else if (cnt.size() == 1) ret = cnt[0].second;
      else if (cnt[0].first == 1) ret = cnt[0].second;
      else {
        ret = cnt[0].second;
        for (size_t i = 1; i < cnt.size(); ++i) if (cnt[i].first == 2) {
          ret |= cnt[i].second;
          break;
        }
      }
      printf("%lld\n", ret | extra);
    } else {
      if (max_sum(n, s, x) < s) puts("-1");
      else {
        int64 left = 0, right = s;
        while (left < right) {
          int64 mid = (left + right - 1) >> 1;
          auto mx = max_sum(n, mid, x);
          if (mx >= s) right = mid;
          else left = mid + 1;
        }
        printf("%lld\n", right);
      }
    }
  }
  return 0;
}
