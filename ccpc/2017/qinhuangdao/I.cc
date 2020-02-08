#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 18;

template<typename T>
inline int sgn(T x) {
  return x < 0 ? -1 : (x > 0);
}

struct point {
  int x, y, id;
  point(int _x = 0, int _y = 0): x(_x), y(_y) {}
  bool operator < (const point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  int64 det(const point &rhs) const {
    return (int64)x * rhs.y - (int64)y * rhs.x;
  }
  int64 dot(const point &rhs) const {
    return (int64)x * rhs.x + (int64)y * rhs.y;
  }
};

int dp[1 << N][N], weight[N][N];
int64 cnt[1 << N][N];
bool empty[N][N][N];
bool above[N][N][N];

bool inside(const point &a, const point &b, const point &c, const point &o) {
  return sgn((o - a).det(c - a)) * sgn((o - a).det(b - a)) < 0 &&
         sgn((o - b).det(a - b)) * sgn((o - b).det(c - b)) < 0 &&
         sgn((o - c).det(b - c)) * sgn((o - c).det(a - c)) < 0;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<point> p(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &p[i].x, &p[i].y);
      p[i].x *= 1000;
      p[i].y *= 1000;
      p[i].id = i;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        scanf("%d", &weight[i][j]);
      }
    }
    std::sort(p.begin(), p.end());
    for (int i = 1; i < n; ++i) {
      if (p[i].x == p[i - 1].x) p[i].x++;
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (i == j || j == k || k == i) continue;
          above[i][j][k] = false;
          if (i < k && k < j) {
            above[i][j][k] = above[j][i][k] = (p[j] - p[i]).det(p[k] - p[i]) > 0;
          }
          empty[i][j][k] = true;
          for (int l = 0; l < n; ++l) {
            if (i == l || j == l || k == l) continue;
            if (inside(p[i], p[j], p[k], p[l])) {
              empty[i][j][k] = false;
            }
          }
        }
      }
    }

    std::vector<int> hull;
    for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
      while (hull.size() > m) {
        point A = p[hull.back()] - p[hull[hull.size() - 2]];
        point B = p[hull.back()] - p[i];
        if (A.det(B) < 0) break;
        hull.pop_back();
      }
      hull.push_back(i);
      if (i + 1 == p.size()) m = hull.size(), o = -1;
    }
    hull.pop_back();

    int lower = 1 << (n - 1) | 1;
    int upper = 1 << (n - 1) | 1;
    for (auto &&e: hull) {
      if (e == 0 || e == n - 1) continue;
      if (above[0][n - 1][e]) upper |= 1 << e;
      else lower |= 1 << e;
    }

    for (int i = 0; i < (1 << n); ++i) {
      for (int j = 0; j < n; ++j) {
        cnt[i][j] = 0;
        dp[i][j] = -1;
      }
    }
    dp[lower][0] = 0;
    cnt[lower][0] = 1;
    for (int i = 1, last = 0; i < n; ++i) {
      if (lower >> i & 1) {
        dp[lower][0] += weight[p[i].id][p[last].id];
        last = i;
      }
    }
    auto update = [] (int &x, int64 &y, int cost, int64 ways) {
      if (x == -1 || (x > cost)) {
        x = cost;
        y = ways;
      } else if (x == cost) {
        y += ways;
      }
    };
    std::queue<int> queue;
    queue.push(lower << 5);
    while (!queue.empty()) {
      int mask = queue.front() >> 5;
      int l = queue.front() & 31;
      queue.pop();
      static int edges[N];
      int t = 0;
      for (int i = 0; i < n; ++i) {
        if (mask >> i & 1) edges[t++] = i;
      }
      for (int m = l; m < t - 1; ++m) {
        int i = edges[m], j = edges[m + 1];
        for (int u = i + 1; u < j; ++u) {
          if (above[i][j][u] && empty[i][j][u]) {
            int new_mask = mask | (1 << u);
            int cost = dp[mask][l] + weight[p[i].id][p[u].id] + weight[p[u].id][p[j].id];
            if (dp[new_mask][m] == -1) queue.push(new_mask << 5 | m);
            update(dp[new_mask][m], cnt[new_mask][m], cost, cnt[mask][l]);
          }
        }
        if (!m) continue;
        int k = edges[m - 1];
        if (empty[i][j][k] && !above[k][j][i]) {
          int new_mask = mask ^ (1 << i);
          int cost = dp[mask][l] + weight[p[k].id][p[j].id];
          if (dp[new_mask][m - 1] == -1) queue.push(new_mask << 5 | (m - 1));
          update(dp[new_mask][m - 1], cnt[new_mask][m - 1], cost, cnt[mask][l]);
        }
      }
    }
    int ret = -1;
    int64 ways = 0;
    for (int i = 0; i < n; ++i) {
      if (dp[upper][i] == -1) continue;
      if (ret == -1 || ret > dp[upper][i]) {
        ret = dp[upper][i];
        ways = cnt[upper][i];
      } else if (ret == dp[upper][i]) {
        ways += cnt[upper][i];
      }
    }
    printf("%d %lld\n", ret, ways);
  }
  return 0;
}
