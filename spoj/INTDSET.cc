#include <cstdio>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;
#define x first
#define y second

const int N = 200000 + 10, mod = 1e9 + 7;

pii A[N];
int L[N], R[N], n;

inline void upd(int &x, int y) {
  x += y; if (x >= mod) x -= mod;
}

struct Node {
  int sum, mul;
  void set(int v) {
    sum = 1ll * sum * v % mod;
    mul = 1ll * mul * v % mod;
  }
} T[N << 2];

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

inline void psd(int rt) {
  if (T[rt].mul != 1) {
    T[lson].set(T[rt].mul);
    T[rson].set(T[rt].mul);
    T[rt].mul = 1;
  }
}
void build(int rt, int l, int r) {
  T[rt].sum = 0; T[rt].mul = 1;
  if (l + 1 == r) {
    if (l == R[0] || l == 0) T[rt].sum = 1;
    return;
  }
  build(lson, l, mid); build(rson, mid, r);
  T[rt].sum = (T[lson].sum + T[rson].sum) % mod;
}
void mul(int rt, int l, int r, int R, int v) {// [0, R)
  if (r <= R) {T[rt].set(v); return;}
  psd(rt);
  mul(lson, l, mid, R, v);
  if (R > mid) mul(rson, mid, r, R, v);
  T[rt].sum = (T[lson].sum + T[rson].sum) % mod;
}
void add(int rt, int l, int r, int x, int v) {
  if (l + 1 == r) {upd(T[rt].sum, v); return;}
  psd(rt);
  if (x < mid) add(lson, l, mid, x, v);
  else add(rson, mid, r, x, v);
  T[rt].sum = (T[lson].sum + T[rson].sum) % mod;
}
int sum(int rt, int l, int r, int L, int R) {// [L, R)
  if (L <= l && R >= r) return T[rt].sum;
  int ret = 0; psd(rt);
  if (L < mid) upd(ret, sum(lson, l, mid, L, R));
  if (R > mid) upd(ret, sum(rson, mid, r, L, R));
  return ret;
}

int u[N << 1], m;
void pre_ins(int x, int v) {
  for (; x >= 0; x -= ~x & x + 1) {
    u[x] = std::min(u[x], v);
  }
}
void suf_ins(int x, int v) {
  for (; x <= m; x += ~x & x + 1) {
    u[x] = std::max(u[x], v);
  }
}
int pre_get(int x, int r = -1) {
  for (; x >= 0; x -= ~x & x + 1) {
    r = std::max(r, u[x]);
  }
  return r;
}
int suf_get(int x, int r = n) {
  for (; x <= m; x += ~x & x + 1) {
    r = std::min(r, u[x]);
  }
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &A[i].x, &A[i].y);
    }
    sort(A, A + n, [](const pii &a, const pii &b) {
      return a.y < b.y || (a.y == b.y && a.x < b.x);
    });
    A[n].x = A[n - 1].y + 1;
    A[n].y = A[n].x + 1;
    std::vector<int> xs;
    for (int i = 0; i <= n; ++i) {
      xs.push_back(A[i].x);
      xs.push_back(A[i].y);
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    for (int i = 0; i <= n; ++i) {
      A[i].x = std::lower_bound(xs.begin(), xs.end(), A[i].x) - xs.begin();
      A[i].y = std::lower_bound(xs.begin(), xs.end(), A[i].y) - xs.begin();
      R[i] = n; L[i] = -1;
    }
    m = xs.size();
    for (int i = 0; i <= m; ++i) u[i] = -1;
    for (int i = 0; i < n; ++i) {
      L[i] = pre_get(A[i].x - 1);
      suf_ins(A[i].y, i);
    }
    for (int i = 0; i <= m; ++i) u[i] = n;
    for (int i = n - 1; i >= 0; --i) {
      R[i] = suf_get(A[i].y + 1);
      pre_ins(A[i].x, i);
    }
    build(1, 0, n + 1);
    for (int j = 1; j < n; ++j) {
      int e = sum(1, 0, n + 1, L[j] + 1, R[j] + 1);
      add(1, 0, n + 1, R[j], e);
      if (L[j] !=-1) mul(1, 0, n + 1, L[j] + 1, 2);
    }
    printf("%d\n", sum(1, 0, n + 1, n, n + 1));
  }
  return 0;
}
