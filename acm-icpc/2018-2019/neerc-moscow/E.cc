#include <cstdio>
#include <ctime>
#include <cassert>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

const int N = 1e7 + 10;

char s[N / 4], t[N / 4];
int head[N * 2], to[N];
int dsu[N], rank[N], idx[N];
int pred[N], succ[N];
int L[N], R[N], match[N];

int gcd(int a, int b) {
  if (!b) return a;
  else return gcd(b, a % b);
}

int get(int x) {
  if (dsu[x] < 0) return x;
  else return dsu[x] = get(dsu[x]);
}

void merge(int x, int y) {
  int rx = idx[x], ry = idx[y];
  if (ry == -1) {
    idx[y] = rx;
    dsu[rx] = -y;
    return;
  }
  if (rank[rx] > rank[ry]) {
    std::swap(rx, ry);
  }
  if (dsu[rx] < dsu[ry]) dsu[ry] = dsu[rx];
  if (rank[rx] == rank[ry]) ++rank[ry];
  idx[-dsu[ry]] = dsu[rx] = ry;
}

int solve(int64 n, int st, int p, int q, int g, char *s, char *t) {
  int bound = q / g;
  int A = 0, B = 0;
  for (int i = 0, x = st; i < bound; ++i) {
    idx[x] = i; rank[i] = B;
    if (x < n && (t[x / 4] >> (x % 4) & 1)) ++B;
    if ((x += p) >= q) x -= q;
  }
  rank[bound] = B;
  if (!B) return 0;
  for (int i = st; i < p && i < n; i += g) if (s[i / 4] >> (i % 4) & 1) {
    int64 k = (n - i - 1) / p;
    int l = idx[i], r = -1, c = 0;
    if (k >= bound) l = 0, r = B - 1, c = B;
    else if (l + k < bound) r = rank[l + k + 1] - 1, l = rank[l], c = r - l + 1;
    else r = rank[l + k - bound + 1] - 1, l = rank[l], c = B - l + r + 1;
    l %= B;
    if (r == -1) r = B - 1;
    if (c == 0) continue;
    L[A] = l; R[A++] = r;
  }
  if (!A) return 0;
  auto run = [&](int mx) {
    memset(head, -1, sizeof(*head) * mx);
    for (int i = 1; i <= B + 1; ++i) {
      pred[i] = i - 1;
      succ[i] = i + 1;
      idx[i] = -1;
    }
    for (int i = 0; i < A; ++i) {
      if (L[i] > R[i]) to[i] = head[R[i] + B], head[R[i] + B] = i;
      else to[i] = head[R[i]], head[R[i]] = i;
      int u = L[i] + 1;
      if (idx[u] == -1) dsu[i] = -u, idx[u] = i, rank[i] = 1;
      else dsu[i] = idx[u], rank[idx[u]] = 2;
    }
    int ret = 0;
    for (int r = 0; r < mx; ++r) for (int i = head[r]; ~i; i = to[i]) {
      int u = -dsu[get(i)];
      if (u <= B && u - 1 <= r) {
        if (L[i] > R[i]) R[i] = B - 1;
        ++ret;
        merge(u, succ[u]);
        succ[pred[u]] = succ[u];
        pred[succ[u]] = pred[u];
      } else {
        if (L[i] > R[i]) L[i] = 0;
      }
    }
    return ret;
  };

  run(B * 2);
  return run(B);
}

int main() {
  int seed = time(NULL);
  printf("%d\n", seed);
  scanf("%d", &seed);
  srand(seed);
  int64 n;
  int p, q;
  /*
  scanf("%lld%d%d", &n, &p, &q);
  scanf("%s%s", s, t);
  for (int i = 0; i < (p + 3) / 4; ++i) {
    if ('a' <= s[i] && s[i] <= 'f') s[i] = s[i] - 'a' + 10;
    else s[i] -= '0';
  }
  for (int i = 0; i < (q + 3) / 4; ++i) {
    if ('a' <= t[i] && t[i] <= 'f') t[i] = t[i] - 'a' + 10;
    else t[i] -= '0';
  }*/
  for (int it = 0; it < 10; ++it) {
    n = rand() % 10000000000 + 1000000000;
    p = rand() % 10000000 + 1;
    q = rand() % 10000000 + 1;
    for (int i = 0; i <= p / 4; ++i) s[i] = rand() % 16;
    for (int i = 0; i <= q / 4; ++i) t[i] = rand() % 16;
  int g = gcd(p, q), ret = 0;
  bool invalid = false;
  for (int i = 0; i < p && !invalid; ++i) {
    if (s[i / 4] >> (i % 4) & 1) {
      ++ret;
      if (i >= n) invalid = true;
    }
  }
  for (int i = 0; i < q && !invalid; ++i) {
    if (t[i / 4] >> (i % 4) & 1) {
      ++ret;
      if (i >= n) invalid = true;
    }
  }
  if (invalid) {
    puts("-1");
    //continue;
    return 0;
  }
  for (int k = 0; k < g; ++k) {
    if (p < q) ret -= solve(n, k, p, q, g, s, t);
    else ret -= solve(n, k, q, p, g, t, s);
  }
  //printf("%d\n", ret);
  printf("cas=%d %d\n", it, ret);
  }
  return 0;
}
