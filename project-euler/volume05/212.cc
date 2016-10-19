#include <bits/stdc++.h>

using LL = long long;

struct rect_t {
  int x1, y1, x2, y2;
};

struct event_t {
  int x, y1, y2, t;
  bool operator < (const event_t &rhs) const {
    return x < rhs.x;
  }
};

const int N = 10399;

int sum[N << 2], cnt[N << 2];

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

void build(int rt, int l, int r) {
  sum[rt] = cnt[rt] = 0;
  if (l + 1 == r) return;
  build(lson, l, mid);
  build(rson, mid, r);
}

void upd(int rt, int l, int r) {
  if (cnt[rt]) sum[rt] = r - l;
  else if (l + 1 == r) sum[rt] = 0;
  else sum[rt] = sum[lson] + sum[rson];
}

void ins(int rt, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    cnt[rt] += v;
    upd(rt, l, r);
    return;
  }
  if (L < mid) ins(lson, l, mid, L, R, v);
  if (R > mid) ins(rson, mid, r, L, R, v);
  upd(rt, l, r);
}

int calc(std::vector<rect_t> &rec) {
  build(1, 0, N);
  std::vector<event_t> ev;
  for (auto &&e: rec) {
    ev.push_back((event_t){e.x1, e.y1, e.y2, +1});
    ev.push_back((event_t){e.x2, e.y1, e.y2, -1});
  }
  std::sort(ev.begin(), ev.end());
  int ret = 0;
  for (int i = 0; i < (int)ev.size(); ++i) {
    if (i) ret += sum[1] * (ev[i].x - ev[i - 1].x);
    ins(1, 0, N, ev[i].y1, ev[i].y2, ev[i].t);
  }
  return ret;
}

LL run(int n) {
  std::vector<int> S(n * 6);
  for (int k = 0; k < n * 6; ++k) {
    if (k < 55) {
      int i = k + 1;
      S[k] = (100003ll - 200003ll * i + 300007ll * i * i * i) % 1000000;
      S[k] += 1000000, S[k] %= 1000000;
    } else {
      S[k] = (S[k - 24] + S[k - 55]) % 1000000;
    }
  }
  std::vector<int> x, y, z, dx, dy, dz;
  for (int i = 0; i < n; ++i) {
    x.push_back(S[i * 6 + 0] % 10000);
    y.push_back(S[i * 6 + 1] % 10000);
    z.push_back(S[i * 6 + 2] % 10000);
    dx.push_back(S[i * 6 + 3] % 399 + 1);
    dy.push_back(S[i * 6 + 4] % 399 + 1);
    dz.push_back(S[i * 6 + 5] % 399 + 1);
  }
  std::vector<rect_t> rec;
  long long ret = 0;
  for (int k = 0; k <= 10399; ++k) {
    rec.clear();
    for (int i = 0; i < n; ++i) {
      if (z[i] <= k && k < z[i] + dz[i]) {
        rec.push_back((rect_t){x[i], y[i], x[i] + dx[i], y[i] + dy[i]});
      }
    }
    ret += calc(rec);
  }
  return ret;
}

int main() {
  std::cout << run(1) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(50000) << std::endl;
  return 0;
}
