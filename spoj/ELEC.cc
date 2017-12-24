#include <cassert>
#include <cstdio>
#include <complex>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include <set>

using value_t = std::complex<double>;
using pii = std::pair<int, int>;

const int N = 100 + 10;
const double eps = 1e-8;

value_t A[N][N], B[N];

void gauss(int n, value_t a[N][N], value_t b[N]) {
  for (int k = 0, i, j, s; k < n; ++k) {
    for (s = k, i = k + 1; i < n; ++i) {
      if (fabs(a[i][k]) > fabs(a[s][k])) s = i;
    }
    if (fabs(a[s][k]) < eps) return;
    if (s != k) {
      std::swap(b[s], b[k]);
      for (i = k; i < n; ++i) {
        std::swap(a[s][i], a[k][i]);
      }
    }
    for (j = k + 1; j < n; ++j) a[k][j] /= a[k][k];
    b[k] /= a[k][k];
    a[k][k] = 1;
    for (j = 0; j < n; ++j) if (j != k) {
      b[j] -= b[k] * a[j][k];
      for (i = k + 1; i < n; ++i) {
        a[j][i] -= a[j][k] * a[k][i];
      }
      a[j][k] = 0;
    }
  }
}

int main() {
  int n, m, z;
  while (scanf("%d%d%d", &n, &m, &z) == 3 && n) {
    std::vector<std::map<int, value_t>> link(n);
    std::vector<int> dsu(n);
    for (int i = 0; i < n; ++i) dsu[i] = i;
    std::function<int(int)> root = [&](int x) {
      if (x != dsu[x]) dsu[x] = root(dsu[x]);
      return dsu[x];
    };
    for (int i = 0; i < m; ++i) {
      int a, b;
      double re, im;
      scanf("%d%d%lf%lf", &a, &b, &re, &im);
      if (a == b) continue;
      --a, --b;
      link[a][b] += 1. / value_t(re, im);
      link[b][a] += 1. / value_t(re, im);
      a = root(a), b = root(b);
      dsu[a] = b;
    }
    std::vector<pii> query(z);
    std::vector<bool> skip(n);
    std::set<int> inq;
    for (int i = 0; i < z; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      if (a == b) {
        query[i] = {-1, 0};
      } else if (root(a) != root(b)) {
        query[i] = {-2, 0};
      } else {
        query[i] = {a, b};
        skip[a] = skip[b] = 1;
        inq.insert({a, b});
      }
    }
    std::set<int> simplify;
    for (int i = 0; i < n; ++i) {
      if (!skip[i]) simplify.emplace(i);
    }
    while (!simplify.empty()) {
      int u = *simplify.begin();
      for (auto &&v: simplify) {
        if (link[v].size() < link[u].size()) u = v;
      }
      simplify.erase(u);
      value_t sum = 0;
      for (auto &&e: link[u]) {
        link[e.first].erase(u);
        sum += e.second;
      }
      sum = 1. / sum;
      for (auto it = link[u].begin(); it != link[u].end(); ++it) {
        for (auto jt = link[u].begin(); jt != it; ++jt) {
          auto tmp = (it->second * jt->second) * sum;
          link[it->first][jt->first] += tmp;
          link[jt->first][it->first] += tmp;
        }
      }
    }
    for (int i = 0; i < n; ++i) inq.insert(i);
    std::vector<std::vector<int>> comp(n);
    for (auto &&u: inq) {
      comp[root(u)].emplace_back(u);
    }
    std::vector<int> mapping(n);
    for (int i = 0; i < z; ++i) {
      if (query[i].first == -1) {
        puts("0.00 0.00");
        continue;
      }
      if (query[i].first == -2) {
        puts("no connection");
        continue;
      }
      auto &ref = comp[root(query[i].first)];
      int m = ref.size();
      for (int j = 0; j < m; ++j) {
        mapping[ref[j]] = j;
        for (int k = 0; k < m; ++k) {
          A[j][k] = 0;
        }
      }
      for (auto &&u: ref) {
        for (auto &&e: link[u]) {
          int a = mapping[u];
          int b = mapping[e.first];
          A[a][b] += e.second;
          A[a][a] -= e.second;
        }
      }
      int x = mapping[query[i].first];
      int y = mapping[query[i].second];
      for (int j = 0; j < m; ++j) B[j] = 0;
      B[y] = 1, B[x] = -1;
      gauss(m, A, B);
      auto res = B[x] - B[y];
      printf("%.10lf %.10lf\n", res.real(), res.imag());
    }
    puts("");
  }
  return 0;
}
