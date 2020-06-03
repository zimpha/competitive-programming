#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 3.5e4 + 10;
const int64 inf = 1ll << 60;

int mx[N << 1];
std::vector<int64> dp[N << 1][2][2];
int ptr[N << 1][2][2];

void max(std::vector<int64> &x, const std::vector<int64>& y) {
  while (x.size() < y.size()) x.push_back(-inf);
  for (size_t i = 0; i < y.size(); ++i) {
    x[i] = std::max(x[i], y[i]);
  }
}

std::vector<int64> sum(const std::vector<int64> &x, const std::vector<int64> &y) {
  std::vector<int64> delta;
  delta.reserve(x.size() + y.size());
  size_t i = 1, j = 1;
  while (i < x.size() && j < y.size()) {
    if (x[i] - x[i - 1] > y[j] - y[j - 1]) delta.push_back(x[i] - x[i - 1]), ++i;
    else delta.push_back(y[j] - y[j - 1]), ++j;
  }
  while (i < x.size()) delta.push_back(x[i] - x[i - 1]), ++i;
  while (j < y.size()) delta.push_back(y[j] - y[j - 1]), ++j;
  std::vector<int64> z;
  z.reserve(x.size() + y.size());
  z.push_back(x[0] + y[0]);
  for (auto &d: delta) z.push_back(z.back() + d);
  return z;
}

void merge(int o, int l, int r) {
  mx[o] = std::min(mx[l], mx[r]);
  for (int al = 0; al < 2; ++al) for (int bl = 0; bl < 2; ++bl) {
    for (int ar = 0; ar < 2; ++ar) for (int br = 0; br < 2; ++br) {
      if (bl != ar) continue;
      auto z = sum(dp[l][al][bl], dp[r][ar][br]);
      max(dp[o][al][br], z);
      if (bl && ar) {
        for (size_t i = 1; i < z.size(); ++i) {
          if (i + 1 < z.size()) z[i] = z[i + 1];
          else z.pop_back();
        }
        max(dp[o][al][br], z);
      }
    }
  }
  max(dp[o][0][1], dp[o][1][1]);
  max(dp[o][1][0], dp[o][1][1]);
  max(dp[o][0][0], dp[o][0][1]);
  max(dp[o][0][0], dp[o][1][0]);
}

std::pair<int64, int> operator + (const std::pair<int64, int> &x, const std::pair<int64, int> &y) {
  return {x.first + y.first, x.second + y.second};
}

std::pair<int64, int> max(const std::pair<int64, int> &x, const std::pair<int64, int> &y) {
  if (x.first == y.first) return x.second < y.second ? x : y;
  else return x.first > y.first ? x : y;
}

std::pair<int64, int> get(int n, int l, int r, int64 x) {
  std::pair<int64, int> ret[2], buf[2], best[2][2];
  bool updated = false;

  auto update = [&] (int o) {
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
      int &p = ptr[o][i][j];
      while (p + 1 < (int)dp[o][i][j].size() && dp[o][i][j][p] - dp[o][i][j][p + 1] < x) ++p;
      best[i][j] = {dp[o][i][j][p] + p * x, p};
    }
    if (!updated) ret[0] = best[0][0], ret[1] = best[0][1], updated = true;
    else {
      for (int i = 0; i < 2; ++i) {
        buf[i] = max(ret[0] + best[0][i], ret[1] + best[1][i] + std::make_pair(-x, -1));
      }
      ret[0] = buf[0], ret[1] = buf[1];
    }
  };

  std::vector<std::pair<int, int>> segs;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) segs.emplace_back(mx[l], l), l++;
    if (r & 1) --r, segs.emplace_back(mx[r], r);
  }
  std::sort(segs.begin(), segs.end());
  for (auto &e: segs) update(e.second);

  return max(ret[0], ret[1]);
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n), ql(q), qr(q), qk(q);
  int64 bound = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    bound += std::abs(a[i]);
    mx[i + n] = i;
    dp[i + n][0][0] = {0, a[i]};
    dp[i + n][0][1] = {-inf, a[i]};
    dp[i + n][1][0] = {-inf, a[i]};
    dp[i + n][1][1] = {-inf, a[i]};
  }
  for (int i = n - 1; i > 0; --i) {
    merge(i, i << 1, i << 1 | 1);
  }
  std::vector<int64> vl(q), vr(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d%d", &ql[i], &qr[i], &qk[i]);
    vl[i] = -bound * 2, vr[i] = bound * 2;
    --ql[i];
  }
  std::vector<int64> ret(q);
  while (true) {
    for (int i = 0; i < n * 2; ++i) {
      memset(ptr[i], 0, sizeof(ptr[i]));
    }
    std::vector<std::pair<int64, int>> queries;
    for (int i = 0; i < q; ++i) if (vr[i] - vl[i] > 1) {
      queries.emplace_back((vr[i] + vl[i]) / 2, i);
    }
    if (queries.empty()) break;
    std::sort(queries.begin(), queries.end());
    for (auto &query: queries) {
      int64 x = query.first;
      int idx = query.second;
      auto best = get(n, ql[idx], qr[idx], x);
      if (best.second <= qk[idx]) {
        vl[idx] = x;
        ret[idx] = best.first - x * qk[idx];
      } else {
        vr[idx] = x;
      }
    }
  }
  for (int i = 0; i < q; ++i) printf("%lld\n", ret[i]);
  return 0;
}
