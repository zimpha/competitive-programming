#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using int64 = long long;

const int N = 1e6 + 10, M = N;
const int mod = 20062006;

int sub[M], ways[M];
char s[N];

void mul(int a[3][3], int b[3][3]) {
  int c[3][3];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < 3; ++k) {
        c[i][j] += (int64)a[i][k] * b[k][j] % mod;
      }
    }
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a[i][j] = c[i][j] % mod;
    }
  }
}

// f(2k)=1+f(2k-1)+f(2k-2), f(2k-1)=f(2k-2)+f(2k-3)
// return {f(2k), f(2k - 1)}
std::pair<int, int> get_ways(int k) {
  if (k == 0) return {1, 0};
  if (k == 1) return {3, 1};
  int m[3][3] = {{2, 1, 1}, {1, 1, 0}, {0, 0, 1}};
  int r[3] = {3, 1, 1};
  --k;
  for (; k; k >>= 1) {
    if (k & 1) {
      int t[3];
      for (int i = 0; i < 3; ++i) {
        t[i] = 0;
        for (int j = 0; j < 3; ++j) {
          t[i] += (int64)r[j] * m[i][j] % mod;
        }
      }
      for (int i = 0; i < 3; ++i) r[i] = t[i] % mod;
    }
    mul(m, m);
  }
  return {r[0], r[1]};
}

int main() {
  std::vector<int> fib = {1, 1};
  for (int i = 2; i <= 41; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  int m, n;
  scanf("%d", &m);//, s);
  std::string xx = "b", yy = "a";
  for (int i = 2; i <= m; ++i) {
    auto z = yy + xx;
    xx = yy;
    yy = z;
  }
  std::map<std::string, int> sss;
  for (size_t ii = 0; ii < yy.size(); ++ii) {
    for (size_t jj = ii; jj < yy.size(); ++jj) {
      sss[yy.substr(ii, jj - ii + 1)]++;
    }
  }
  for (size_t ii = 0; ii < yy.size(); ++ii) {
    for (size_t jj = ii; jj < yy.size(); ++jj) {
      for (int k = ii; k <= jj; ++k) s[k - ii] = yy[k];
      s[jj - ii + 1] = 0;
      //if (!(ii == 0 && jj == 3)) continue;
      //printf("%s\n", s);
      n = strlen(s);
      if (m <= 1) {
        puts("1 1");
        return 0;
      }
      int x = 1;
      while (x < m && fib[x] < n * 10) ++x;
      if (x % 2 != m % 2) ++x;
      assert(x <= m);
      std::string t_fs = "b", fs = "a";
      for (int i = 2; i <= x; ++i) {
        std::string z = fs + t_fs;
        t_fs = fs; fs = z;
      }
      std::vector<int> acc;
      for (int i = x; i >= 1; i -= 2) acc.push_back(fib[i]);
      std::reverse(acc.begin(), acc.end());
      std::vector<std::pair<int, int>> go;
      std::vector<std::pair<int, int>> from;
      for (int i = 2; i < 41 && i + 1 <= m; ++i) {
        go.emplace_back(fib[i] - 2, fib[i + 1] - 1);
        from.emplace_back(fib[i + 1] - 1, fib[i] - 2);
      }
      sub[0] = 1;
      for (int i = 1, j = 0; i <= fib[x]; ++i) {
        sub[i] = sub[i - 1];
        while (j < from.size() && from[j].first < i) ++j;
        if (j < from.size() && from[j].first == i) sub[i] += sub[from[j].second];
        if (sub[i] >= mod) sub[i] -= mod;
      }
      auto accepted = get_ways((m - x) / 2);
      ways[fib[x]] = accepted.first;
      for (int i = fib[x] - 1, j = go.size() - 1, k = acc.size() - 1; i >= 0; --i) {
        ways[i] = ways[i + 1];
        while (k >= 0 && acc[k] > i) --k;
        if (k >= 0 && acc[k] == i) ways[i]++;
        while (j >= 0 && go[j].first > i) --j;
        if (j >= 0 && go[j].first == i) {
          if (go[j].second < fib[x]) ways[i] += ways[go[j].second];
          else ways[i] += accepted.second;
        }
        ways[i] %= mod;
      }

      int p = 0;
      for (int i = 0, j = 0; i < n; ++i) {
        if (fs[p] == s[i]) ++p;
        else {
          while (go[j].first < p) ++j;
          p = go[j].second;
        }
        assert(p <= fs.size());
      }
      //for (int i = 0; i <= fib[x]; ++i) printf("%d ", ways[i]);
      //puts("");
      //for (int i = 0; i <= fib[x]; ++i) printf("%d ", sub[i]);
      //puts("");
      int q = p;
      for (auto &x: acc) if (x >= p) {
        q = x;
        break;
      }
      for (auto &e: go) if (e.first >= p) {
        q = std::min(q, e.first);
        break;
      }
      int64 ret = 0;
      for (int i = 1; i <= q; ++i) ret += sub[i];
      //printf("%d %lld\n", ways[p], ret % mod);
      assert(ways[p] == sss[s]);
      int cnt = 0;
      for (auto &e: sss) cnt += e.second >= ways[p];
      assert(ret == cnt);
    }
  }
  //for (auto &x: sss) printf("%s %d\n", x.first.c_str(), x.second);
  return 0;
}
