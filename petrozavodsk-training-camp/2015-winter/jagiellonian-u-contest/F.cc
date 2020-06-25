#include <cstdio>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>

using uint64 = unsigned long long;
const int N = 200;

int gcd[N][N];

int main() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      gcd[i][j] = std::__gcd(i, j);
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::map<std::vector<int>, int> cnt;
    for (int i = 0; i < m; ++i) {
      std::vector<int> p(n), q(n);
      for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        --p[i];
      }
      std::vector<int> mark(n);
      std::vector<std::pair<int, int>> shifts;
      for (int i = 0; i < n; ++i) if (!mark[i]) {
        std::vector<int> c;
        for (int j = i; !mark[j]; j = p[j]) {
          c.push_back(j); mark[j] = 1;
        }
        int ms = -1;
        for (int d = 0; d < (int)c.size(); ++d) if (gcd[d][c.size()] == 1) {
          bool valid = true;
          for (auto &e: shifts) {
            if ((e.first - d) % gcd[e.second][c.size()] != 0) {
              valid = false;
              break;
            }
          }
          if (valid && (ms == -1 || c[ms] > c[d])) ms = d;
        }
        assert(ms != -1);
        for (size_t j = 0; j < c.size(); ++j) {
          q[c[j * ms % c.size()]] = c[(j + 1) * ms % c.size()];
        }
        shifts.emplace_back(ms, c.size());
      }
      printf("%d\n", cnt[q]);
      cnt[q]++;
    }
  }
  return 0;
}
