#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;
using pii = std::pair<int, int64>;

std::pair<int, int> generate(int64 a, int64 b, int mod, std::vector<int> &p) {
  std::vector<int> last(mod, -1);
  last[--p[0]] = 0;
  for (int i = 1, x = p[0] + 1; ; ++i) {
    x = (a * x + b) % mod + 1;
    if (last[x - 1] != -1) {
      return {last[x - 1], i - last[x - 1]};
    }
    last[x - 1] = i;
    p.emplace_back(x - 1);
  }
}

int gcd(int a, int b) {
  return !b ? a : gcd(b, a % b);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, a, b, c, d, mod_w, mod_p;
    std::vector<int> p(1), w(1);
    scanf("%lld%d%d%lld%lld%lld%lld%lld%lld", &n, &p[0], &w[0], &mod_p, &mod_w, &a, &b, &c, &d);
    int extra_p, extra_w, period_p, period_w;
    std::tie(extra_p, period_p) = generate(a, b, mod_p, p);
    std::tie(extra_w, period_w) = generate(c, d, mod_w, w);
    std::vector<int> max_w(mod_p, -1), min_w(mod_p, -1);
    std::vector<int64> max_c(mod_p, 0), min_c(mod_p, 0);

    auto update_min = [&](int p, int w, int64 c) {
      if (c == 0) return;
      if (min_w[p] == -1 || min_w[p] > w) {
        min_w[p] = w;
        min_c[p] = 0;
      }
      if (min_w[p] == w) min_c[p] += c;
    };
    auto update_max = [&](int p, int w, int64 c) {
      if (c == 0) return;
      if (max_w[p] == -1 || max_w[p] < w) {
        max_w[p] = w;
        max_c[p] = 0;
      }
      if (max_w[p] == w) max_c[p] += c;
    };

    int upp = std::min<int64>(n, std::max(extra_p, extra_w));
    for (int i = 0; i < upp; ++i) {
      int pi = i < extra_p ? p[i] : p[extra_p + (i - extra_p) % period_p];
      int wi = i < extra_w ? w[i] : w[extra_w + (i - extra_w) % period_w];
      update_min(pi, wi, 1);
      update_max(pi, wi, 1);
    }
    if (upp + period_w > n) {
      for (int i = upp; i < n; ++i) {
        int pi = i < extra_p ? p[i] : p[extra_p + (i - extra_p) % period_p];
        int wi = i < extra_w ? w[i] : w[extra_w + (i - extra_w) % period_w];
        update_min(pi, wi, 1);
        update_max(pi, wi, 1);
      }
    } else {
      n -= upp;
      std::vector<int> tmp(period_p);
      for (int i = upp; i < upp + period_p; ++i) tmp[i - upp] = p[extra_p + (i - extra_p) % period_p];
      p.swap(tmp);
      tmp.resize(period_w);
      for (int i = upp; i < upp + period_w; ++i) tmp[i - upp] = w[extra_w + (i - extra_w) % period_w];
      w.swap(tmp);
      int g = gcd(period_p, period_w);
      std::vector<pii> value(period_w * 2);
      std::vector<int> pos(period_w);
      for (int i = 0, s = 0; i < g; ++i) {
        for (int j = 0; j < period_w / g; ++j) {
          int idx = (i + (int64)j * period_p) % period_w;
          pos[idx] = s;
          value.at(period_w + (s++)) = {w[idx], 1};
        }
      }

      auto take_min = [](const pii &a, const pii &b) -> pii {
        if (a.first < b.first || b.second == 0) return a;
        if (a.first > b.first || a.second == 0) return b;
        return {a.first, a.second + b.second};
      };
      auto take_max = [](const pii &a, const pii &b) -> pii {
        if (a.first > b.first || b.second == 0) return a;
        if (a.first < b.first || a.second == 0) return b;
        return {a.first, a.second + b.second};
      };

      auto query_min = [&] (int l, int r) {  // min on interval [l, r)
        pii res = {mod_w, 0};
        for (l += period_w, r += period_w; l < r; l >>= 1, r >>= 1) {
          if (l & 1) res = take_min(res, value[l++]);
          if (r & 1) res = take_min(res, value[--r]);
        }
        return res;
      };
      auto query_max = [&] (int l, int r) {  // max on interval [l, r)
        pii res = {-1, 0};
        for (l += period_w, r += period_w; l < r; l >>= 1, r >>= 1) {
          if (l&1) res = take_max(res, value[l++]);
          if (r&1) res = take_max(res, value[--r]);
        }
        return res;
      };

      for (int i = period_w - 1; i > 0; --i) {
        value[i] = take_min(value[i << 1], value[i << 1 | 1]);
      }
      int cyc = period_w / g;
      for (int i = 0; i < period_p && i < n; ++i) {
        int64 rest = (n - i - 1) / period_p + 1;
        int x = pos[i % period_w], pi = p[i];
        int st = x / cyc * cyc;
        pii res = {mod_w, 0};
        if (rest >= cyc) {
          res = query_min(st, st + cyc);
          res.second *= rest / cyc;
        }
        if (rest %= cyc) {
          int l = x % cyc;
          res = take_min(res, query_min(st + l, st + std::min<int64>(l + rest, cyc)));
          if (l + rest > cyc) res = take_min(res, query_min(st, st + l + rest - cyc));
        }
        update_min(pi, res.first, res.second);
      }

      for (int i = period_w - 1; i > 0; --i) {
        value[i] = take_max(value[i << 1], value[i << 1 | 1]);
      }
      for (int i = 0; i < period_p && i < n; ++i) {
        int64 rest = (n - i - 1) / period_p + 1;
        int x = pos[i % period_w], pi = p[i];
        int st = x / cyc * cyc;
        pii res = {-1, 0};
        if (rest >= cyc) {
          res = query_max(st, st + cyc);
          res.second *= rest / cyc;
        }
        if (rest %= cyc) {
          int l = x % cyc;
          res = take_max(res, query_max(st + l, st + std::min<int64>(l + rest, cyc)));
          if (l + rest > cyc) res = take_max(res, query_max(st, st + l + rest - cyc));
        }
        update_max(pi, res.first, res.second);
      }
    }
    int64 bargain = 0, min = mod_w;
    for (int i = 0; i < mod_p; ++i) if (min_w[i] != -1) {
      if (min > min_w[i]) bargain += min_c[i];
      min = std::min<int>(min, min_w[i]);
    }
    int64 terrible = 0, max = -1;
    for (int i = mod_p - 1; i >= 0; --i) if (max_w[i] != -1) {
      if (max < max_w[i]) terrible += max_c[i];
      max = std::max<int>(max, max_w[i]);
    }
    printf("Case #%d: %lld %lld\n", cas, terrible, bargain);
  }
  return 0;
}
