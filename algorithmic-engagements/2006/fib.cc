#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using i64 = long long;

const int N = 1e6 + 10;
const int mod = 20062006;

char s[N];
int n, m;

void mul(int a[3][3], int b[3][3]) {
  int c[3][3];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < 3; ++k) {
        c[i][j] += (i64)a[i][k] * b[k][j] % mod;
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
          t[i] += (i64)r[j] * m[i][j] % mod;
        }
      }
      for (int i = 0; i < 3; ++i) r[i] = t[i] % mod;
    }
    mul(m, m);
  }
  return {r[0], r[1]};
}

void solve_small() {
  std::vector<std::string> fib = {"b", "a"};
  for (int i = 2; i <= n; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  std::map<std::string, int> cnt;
  for (size_t i = 0; i < fib[n].size(); ++i) {
    for (size_t j = i; j < fib[n].size(); ++j) {
      cnt[fib[n].substr(i, j - i + 1)] += 1;
    }
  }
  int occ = cnt[s], ret = 0;
  for (auto &e: cnt) {
    ret += e.second >= occ;
  }
  printf("%d %d\n", occ, ret);
}

struct Node {
  int go[2];
  int len[2];
  i64 ways, occ;
  bool acc;
} nodes[300];

// build csam for fib[n]
int build(int n) {
  std::vector<int> fib = {1, 1};
  for (int i = 2; i <= n; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  int parity = n % 2;
  for (int i = 0; i < 300; ++i) {
    nodes[i].go[0] = nodes[i].go[1] = -1;
    nodes[i].len[0] = nodes[i].len[1] = 0;
    nodes[i].ways = nodes[i].occ = 0;
    nodes[i].acc = false;
  }
  int m = 0;
  for (; n >= 5; --n) {
    if (n % 2 == parity) {
      nodes[m].acc = true;
    }
    if (m) {
      nodes[m].go[0] = m - 1;
      nodes[m].len[0] = fib[n - 1] - 2;
    }
    if (n & 1) { // end with ba
      if (m) {
        nodes[m + 2].go[0] = m - 2;
        nodes[m + 2].len[0] = 1;
      }
      nodes[m + 2].go[1] = m + 1;
      nodes[m + 1].go[0] = m;
      nodes[m + 2].len[1] = nodes[m + 1].len[0] = 1;
    } else { // end with ab
      if (m) {
        nodes[m + 2].go[1] = m - 2;
        nodes[m + 2].len[1] = 1;
      }
      nodes[m + 2].go[0] = m + 1;
      nodes[m + 1].go[1] = m;
      nodes[m + 2].len[0] = nodes[m + 1].len[1] = 1;
    }
    m += 3;
  }
  if (parity == 0) {
    nodes[m].acc = nodes[m + 3].acc = 1;
  } else {
    nodes[m + 2].acc = nodes[m + 4].acc = 1;
  }
  nodes[m + 5].go[1] = m + 3;
  nodes[m + 5].len[1] = 1;
  nodes[m + 2].go[1] = m - 2;
  nodes[m + 2].len[1] = 1;
  nodes[m + 4].go[0] = m + 1;
  nodes[m + 4].len[0] = 1;
  static std::string s = "abaaba";
  for (int i = 0; i <= 5; ++i) {
    int e = s[5 - i] - 'a';
    nodes[m + i].go[e] = m + i - 1;
    nodes[m + i].len[e] = 1;
  }
  return m + 5;
}

void solve_large() {
  int w = std::min(n, 40);
  if (n % 2 != w % 2) ++w;

  int start = build(w);
  auto rest = get_ways((n - w) / 2);
  nodes[0].ways = nodes[1].ways = nodes[2].ways = rest.first;
  if (n != w) {
    nodes[2].ways = (nodes[2].ways + rest.second) % mod;
  }
  for (int i = 3; i <= start; ++i) {
    nodes[i].ways = nodes[i].acc;
    for (int e = 0; e < 2; ++e) {
      if (nodes[i].go[e] != -1) {
        nodes[i].ways += nodes[nodes[i].go[e]].ways;
      }
    }
    nodes[i].ways %= mod;
  }
  nodes[start].occ = 1;
  for (int i = start; i >= 0; --i) {
    nodes[start].occ %= mod;
    for (int e = 0; e < 2; ++e) {
      if (nodes[i].go[e] == -1) continue;
      nodes[nodes[i].go[e]].occ += nodes[i].occ;
    }
  }

  int m = strlen(s), p = start;
  for (int i = 0; i < m; ) {
    int o = s[i] - 'a';
    i += nodes[p].len[o];
    p = nodes[p].go[o];
  }
  int q = p;
  for (; q > 0; --q) {
    if (nodes[q].acc) break;
    if (nodes[q].go[0] != -1 && nodes[q].go[1] != -1) break;
  }
  i64 ret = 0;
  for (int i = start; i >= q; --i) {
    if (i != start) ret += nodes[i].occ;
    for (int e = 0; e < 2; ++e) {
      if (nodes[i].go[e] < q) continue;
      ret += nodes[i].occ * (nodes[i].len[e] - 1) % mod;
    }
  }
  printf("%lld %lld\n", nodes[p].ways, ret % mod);
}

int main() {
  scanf("%d%s", &n, s);
  if (n <= 6) solve_small();
  else solve_large();
  return 0;
}
