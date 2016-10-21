#include <bits/stdc++.h>

const int N = 1000000;

std::vector<int> leg[N];

void dfs(long a, long b, long c, long d, long n) {
  long u = a + c, v = b + d;
  long z = u * u + v * v, x = 2 * u * v, y = v * v - u * u;
  if (z >= n) return;
  if (u % 2 != v % 2) {
    for (int k = 1; k * z < n; ++k) {
      leg[k * x].push_back(k * z);
      leg[k * y].push_back(k * z);
    }
  }
  dfs(a, b, u, v, n);
  dfs(u, v, c, d, n);
}

long run(long n) {
  //h = sqrt(y^2-w^2) * sqrt(x^2 - w^2) / (sqrt(y^2 - w^2) + sqrt(x^2 - w^2))
  for (int i = 0; i < n; ++i) leg[i].clear();
  dfs(0, 1, 1, 1, n);
  long ret = 0;
  for (long w = 1; w < n; ++w) {
    std::sort(leg[w].begin(), leg[w].end());
    for (size_t i = 0; i < leg[w].size(); ++i) {
      for (size_t j = i + 1; j < leg[w].size(); ++j) {
        long x = leg[w][i], y = leg[w][j];
        long s = sqrt(x * x - w * w), t = sqrt(y * y - w * w);
        if (s * t % (s+ t) == 0) {
          ++ret;
//          std::cout << x << ' ' << y << ' ' << s * t / (s + t) << ' ' << w << std::endl;
        }
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run(200) << std::endl;
  std::cout << run(1000000) << std::endl;
  return 0;
}
