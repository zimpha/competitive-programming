#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using ll = long long;

const double eps = 1e-9;

struct container_t {
  std::map<int, double> re;
  double total;
  container_t(): re(), total(0) {}
  void add(int x, double v) {
    total += v;
    re[x] += v;
  }
};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> min(n), cr(n);
    std::vector<double> max(n), pr(n);
    std::vector<container_t> con(n);
    std::vector<double> vol(m);
    for (int i = 0; i < n; ++i) {
      scanf("%d%lf%d%lf", &min[i], &max[i], &cr[i], &pr[i]);
      --cr[i];
      pr[i] /= 100.0;
    }
    for (int i = 0; i < m; ++i) {
      scanf("%lf", &vol[i]);
    }
    auto solve = [&]() {
      for (int i = 0; i < n; ++i) {
        double use = min[i] * pr[i];
        if (vol[cr[i]] < use) return false;
        vol[cr[i]] -= use;
        con[i].add(cr[i], use);
      }
      std::vector<std::vector<std::pair<double, int>>> rea(m);
      for (int i = 0; i < n; ++i) {
        rea[cr[i]].emplace_back(pr[i], i);
      }
      for (int i = 0; i < m; ++i) {
        std::sort(rea[i].begin(), rea[i].end());
        for (auto &&e: rea[i]) {
          double use = max[e.second] * pr[e.second] - con[e.second].total;
          use = std::min(use, vol[i]);
          vol[i] -= use;
          con[e.second].add(i, use);
        }
      }
      for (int i = 0; i < n; ++i) {
        max[i] = std::min(max[i], con[i].total / pr[i]);
      }
      int it = 0;
      for (int i = 0; i < m; ++i) {
        while (it < n && con[it].total >= min[it]) ++it;
        if (it == n) break;
        double use = std::min(min[it] - con[it].total, vol[i]);
        if (use == 0) continue;
        vol[i] -= use;
        con[it].add(i, use);
        --i;
      }
      for (int i = 0; i < n; ++i) if (con[i].total > min[i]) {
        while (it < n && con[it].total >= min[it]) ++it;
        if (it == n) break;
        double use = std::min(con[it].total - min[it], con[i].total - min[i]);
        con[i].add(cr[i], -use);
        con[it].add(cr[i], use);
        --i;
      }
      if (it != n) return false;
      it = 0;
      for (int i = 0; i < m; ++i) {
        if (vol[i] <= eps) continue;
        while (it < n && con[it].total >= max[it]) ++it;
        if (it == n) return false;
        double use = std::min(max[it] - con[it].total, vol[i]);
        vol[i] -= use;
        con[it].add(i, use);
        --i;
      }
      puts("YES");
      for (int i = 0; i < n; ++i) {
        int s = 0;
        for (auto &&e: con[i].re) {
          if (e.second != 0) ++s;
        }
        printf("%d", s);
        for (auto &&e: con[i].re) {
          if (e.second) printf(" %d %.10f", e.first + 1, e.second);
        }
        puts("");
      }
      return true;
    };

    if (!solve()) puts("NO");
  }
  return 0;
}
