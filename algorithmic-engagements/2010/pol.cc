#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 1000 + 10;

struct point {
  int64 x, y;
  point(int64 x = 0, int64 y = 0): x(x), y(y) {}
  point operator - (const point &rhs) const {
    return {x - rhs.x, y - rhs.y};
  }
  int64 det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  int64 dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
} p[N], q[N];

int count[N][N], r[N];

bool cmp(const point &a, const point &b) {
  if (a.y < 0 && b.y < 0) {
    return a.det(b) > 0;
  } else if (a.y > 0 && b.y > 0) {
    return a.det(b) > 0;
  } else {
    return a.y > 0;
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &p[i].x, &p[i].y);
  }
  std::vector<int> left(n, -1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) if (i != j) {
      if (p[i].y == p[j].y && p[j].x < p[i].x) left[i] = j;
    }
  }
  for (int i = 0; i < n; ++i) {
    int nn = 0;
    for (int j = 0; j < n; ++j) if (i != j) {
      if (p[i].y != p[j].y) {
        r[nn++] = j;
        q[j] = p[j] - p[i];
      }
    }
    std::sort(r, r + nn, [](int u, int v) {
      return cmp(q[u], q[v]);
    });
    if (i == 8) {
      for (int j = 0; j < nn; ++j) {
        printf("%lld %lld\n", q[r[j]].x, q[r[j]].y);
      }
    }
    if (nn > 0) {
      if (q[r[0]].y < 0) {
        for (int j = 0; j < nn; ++j) {
          count[i][r[j]] += j;
          count[r[j]][i] -= (left[i] != -1);
        }
      } else if (q[r[nn - 1]].y > 0) {
        for (int j = 0; j < nn; ++j) {
          count[i][r[j]] += nn - 1 - j + (left[i] != -1);
        }
      } else {
        int bound = 0;
        while (bound < nn && q[r[bound]].y > 0) ++bound;
        if (i == 8) printf("bound=%d, nn=%d\n", bound, nn);
        for (int j = 0, k = bound; j < bound; ++j) {
          point t = q[r[j]];
          t.x = -t.x;
          t.y = -t.y;
          while (k < nn && cmp(q[r[k]], t)) ++k;
          count[i][r[j]] += bound - 1 - j + (left[i] != -1);
          count[r[j]][i] -= k - bound;
        }
        for (int j = bound, k = 0; j < nn; ++j) {
          point t = q[r[j]];
          t.x = -t.x;
          t.y = -t.y;
          while (k < bound && cmp(q[r[k]], t)) ++k;
          count[i][r[j]] += j - bound;
          count[r[j]][i] -= bound - k + (left[i] != -1);
          if (r[j] == 6 && i == 8) {
            printf("%d %d\n", bound, k);
          }
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d ", count[i][j]);
    }
    puts("");
  }
  for (int i = 0, w; i < m; ++i) {
    scanf("%d", &w);
    std::vector<int> u(w + 2);
    for (int j = 0; j < w; ++j) {
      scanf("%d", &u[j]);
      --u[j];
    }
    u[w] = u[0]; u[w + 1] = u[1];
    std::reverse(u.begin(), u.end());
    int ret = 0;
    for (int a = 0, b = 1, c = 2; a < w; ++a, ++b, ++c) {
      const auto &s = p[u[a]], &t = p[u[b]], &r = p[u[c]];
      if (s.y < t.y) ret += count[u[a]][u[b]];
      else if (s.y > t.y) ret -= count[u[a]][u[b]];
      if ((t - s).det(r - s) < 0) --ret;
      //if (s.y > t.y && t.y > r.y) --ret;
      //if (s.y < t.y && t.y > r.y && s.x < t.x && t.x < r.x) --ret;
      //if (s.y == t.y && s.x < t.x && t.y < r.y) --ret;
      //printf("a=%d b=%d ret=%d\n", u[a] + 1, u[b] + 1, ret);
    }
    printf("%d\n", ret);
  }
  return 0;
}
