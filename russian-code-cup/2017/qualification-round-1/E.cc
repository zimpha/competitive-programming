#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using ll = long long;

struct Trie {
  static const int SIZE = 100000 + 10;
  int go[SIZE][26], sz;
  int last[SIZE];

  int newNode() {
    memset(go[sz], 0, sizeof(go[sz]));
    last[sz] = 0;
    return sz ++;
  }
  void init() {
    sz = 0;
    newNode();
  }
  void ins(const char *s, int idx, int *v) {
    int n = strlen(s), p = 0;
    for (int i = 0; i < n; ++ i) {
      int o = s[i] - 'a';
      if (go[p][o] == 0) {
        go[p][o] = newNode();
      }
      p = go[p][o];
      v[i] = last[p];
      last[p] = idx;
    }
  }
} Prefix, Suffix;

const int N = 100000 + 10;

std::string s[N], t[N];
std::vector<std::pair<int, int>> ql[N];
std::vector<std::pair<int, int>> pre[N], suf[N];
int pcnt[N][26], scnt[N][26];
int ptot[N], stot[N];
int last[N], l[N], r[N];

struct FenwickTree {
  int u[N], n;
  void init(int _n) {
    n = _n;
    for (int i = 0; i <= n; ++i) {
      u[i] = 0;
    }
  }
  void add(int x, int v) {
    for (; x <= n; x += ~x & x + 1) u[x] += v;
  }
  int get(int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += u[x];
    return r;
  }
};

FenwickTree pbits[26], pfen;
FenwickTree sbits[26], sfen;

int main() {
  Prefix.init();
  Suffix.init();
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    static char buf[N];
    scanf("%s", buf);
    s[i] = std::string(buf);
    t[i] = std::string(buf);
    std::reverse(t[i].begin(), t[i].end());
    Prefix.ins(s[i].c_str(), i, last);
    for (size_t j = 0; j < s[i].size(); ++j) {
      pre[i].emplace_back(j, last[j]);
    }
    Suffix.ins(t[i].c_str(), i, last);
    for (size_t j = 0; j < t[i].size(); ++j) {
      suf[i].emplace_back(j, last[j]);
    }
  }
  for (int i = 0; i < 26; ++i) {
    sbits[i].init(n);
    pbits[i].init(n);
  }
  sfen.init(n); pfen.init(n);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", l + i, r + i);
    if (l[i]) {
      ql[l[i] - 1].emplace_back(i, -1);
    }
    ql[r[i]].emplace_back(i, 1);
  }
  for (int i = 0; i <= n; ++i) {
    for (auto &&e: pre[i]) {
      int o = s[i][e.first] - 'a';
      if (e.first) {
        pbits[o].add(e.second, 1);
      }
      pfen.add(e.second, 1);
    }
    for (auto &&e: suf[i]) {
      int o = t[i][e.first] - 'a';
      if (e.first) {
        sbits[o].add(e.second, 1);
      }
      sfen.add(e.second, 1);
    }
    for (auto &&e: ql[i]) {
      int v = l[e.first] - 1;
      int w = e.first;
      ptot[w] += e.second * pfen.get(v);
      stot[w] += e.second * sfen.get(v);
      for (int j = 0; j < 26; ++j) {
        pcnt[w][j] += e.second * pbits[j].get(v);
        scnt[w][j] += e.second * sbits[j].get(v);
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    ll ret = 1ll * ptot[i] * stot[i];
    for (int j = 0; j < 26; ++j) {
      ret -= 1ll * pcnt[i][j] * scnt[i][j];
    }
    printf("%lld\n", ret);
  }
  return 0;
}
