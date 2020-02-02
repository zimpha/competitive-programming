#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using uint64 = unsigned long long;
using int64 = long long;

const double eps = 1e-9;
const int P = 2234579;
const int N = 1e5 + 10;

int64 sqr(int64 x) { return x * x; }

std::vector<int> mod[P];

struct Node {
  int x, y, z, r;
  int64 sx, sy, sz;
  bool operator < (const Node &rhs) const {
    return r > rhs.r;
  }
} s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d%d", &s[i].x, &s[i].y, &s[i].z, &s[i].r);
      s[i].x *= 2, s[i].y *= 2, s[i].z *= 2, s[i].r *= 2;
    }

    std::sort(s, s + n);

    std::vector<int> result;
    auto count = [&](int mid, bool print = false) {
      int width = 1e9, last = -1;
      const int64 base = 1e9 + 10;
      result.clear();
      if (mid < 0) mid = 0;
      for (int i = 0; i < P; ++i) mod[i].clear();
      for (int i = 0; i < n; ++i) {
        int now = (s[i].r + mid) * 2;
        if (now * 2 < width) {
          if (last != -1) {
            for (int j = last; j < n; ++j) {
              int x = s[j].x / width, y = s[j].y / width, z = s[j].z / width;
              mod[(x * base % P * base + y * base + z) % P].clear();
            }
          }
          for (int i = 0; i < P; ++i) mod[i].clear();
          width = now, last = i + 1;
          for (int j = i + 1; j < n; ++j) {
            int x = s[j].x / width, y = s[j].y / width, z = s[j].z / width;
            mod[(x * base % P * base + y * base + z) % P].push_back(j);
          }
        }
        int x = s[i].x / width, y = s[i].y / width, z = s[i].z / width;
        for (int dx = -1; dx <= 1; ++dx) for (int dy = -1; dy <= 1; ++dy) for (int dz = -1; dz <= 1; ++dz) {
          int xx = x + dx, yy = y + dy, zz = z + dz;
          if (xx < 0 || yy < 0 || zz < 0) continue;
          auto &cube = mod[(xx * base % P * base + yy * base + zz) % P];
          if (cube.empty()) continue;
          for (auto &j: cube) if (i < j) {
            int64 dist = sqr(s[i].x - s[j].x) + sqr(s[i].y - s[j].y) + sqr(s[i].z - s[j].z);
            int64 bound = sqr(s[i].r + s[j].r + mid * 2);
            if (dist > bound) continue;
            double d = sqrtl(dist) - s[i].r - s[j].r;
            if (d < 0) d = 0;
            result.push_back(ceil(d / 2 - eps) + eps);
            if (result.size() == k) return k;
          }
        }
      }
      return 0;
    };

    int left = 0, right = 3000000;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      if (count(mid) >= k) right = mid;
      else left = mid + 1;
    }
    count(left - 1, true);
    std::sort(result.begin(), result.end());
    for (auto &x: result) printf("%d\n", x);
    for (int i = result.size(); i < k; ++i) {
      printf("%d\n", left);
    }
  }
  return 0;
}

