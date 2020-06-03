#include <cstdio>
#include <functional>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

struct FastIO {
  static const int S = 655360;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  inline int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline void nextString(char *s) {
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
  }
} io;

int main() {
  int n = io.nextUInt();
  int m = io.nextUInt();
  int k = io.nextUInt();
  std::vector<int> a(m), b(m);
  for (int i = 0; i < m; ++i) {
    a[i] = io.nextUInt() - 1;
    b[i] = io.nextUInt() - 1;
  }
  std::vector<int> st(k), ed(k);
  std::vector<int> county(n), belong(n);
  for (int i = 0; i < k; ++i) {
    int w = io.nextUInt();
    if (i) st[i] = ed[i - 1];
    else st[i] = 0;
    ed[i] = st[i] + w;
    for (int j = 0; j < w; ++j) {
      county[j + st[i]] = io.nextUInt() - 1;
      belong[county[j + st[i]]] = i;
    }
  }

  std::vector<int> to(m * 2);
  std::vector<int> head(n * 2 + 1);
  for (int i = 0; i < m; ++i) {
    head[a[i]]++;
    head[b[i]]++;
  }
  for (int i = 1; i <= n * 2; ++i) {
    head[i] += head[i - 1];
  }
  for (int i = 0; i < m; ++i) {
    to[--head[a[i]]] = b[i] + n;
    to[--head[b[i]]] = a[i] + n;
  }


  auto l = st, r = ed;
  std::vector<bool> mark(n * 2);
  std::vector<int> stk; stk.reserve(n * 2);
  std::function<void(int)> dfs1 = [&](int x) {
    if (mark[x]) return;
    mark[x] = 1;
    for (int i = head[x]; i < head[x + 1]; ++i) dfs1(to[i]);
    if (x >= n) {
      int s = belong[x - n];
      while (l[s] < r[s]) {
        if (county[l[s]] != x - n) dfs1(county[l[s]++]);
        else if (county[r[s] - 1] != x - n) dfs1(county[--r[s]]);
        else break;
      }
    }
    stk.push_back(x);
  };
  for (int i = 0; i < n * 2; ++i) dfs1(i);

  l = st, r = ed;
  std::fill(head.begin(), head.end(), 0);
  for (int i = 0; i < m; ++i) {
    head[b[i] + n]++;
    head[a[i] + n]++;
  }
  for (int i = 1; i <= n * 2; ++i) {
    head[i] += head[i - 1];
  }
  for (int i = 0; i < m; ++i) {
    to[--head[a[i] + n]] = b[i];
    to[--head[b[i] + n]] = a[i];
  }
  int scc_cnt = 0;
  std::vector<int> col(n * 2);
  std::function<void(int)> dfs2 = [&](int x) {
    if (!mark[x]) return;
    mark[x] = 0;
    col[x] = scc_cnt;
    for (int i = head[x]; i < head[x + 1]; ++i) dfs2(to[i]);
    if (x < n) {
      int s = belong[x];
      while (l[s] < r[s]) {
        if (county[l[s]] != x) dfs2(county[l[s]++] + n);
        else if (county[r[s] - 1] != x) dfs2(county[--r[s]] + n);
        else break;
      }
    }
  };

  while (!stk.empty()) {
    scc_cnt++;
    dfs2(stk.back());
    stk.pop_back();
  }

  for (int i = 0; i < n; ++i) {
    if (col[i] == col[i + n]) {
      puts("NIE");
      return 0;
    }
  }
  std::vector<int> ret(k);
  for (int i = 0; i < k; ++i) ret[i] = county[st[i]];
  for (int i = 0; i < n; ++i) {
    if (col[i] < col[i + n]) ret[belong[i]] = i;
  }
  puts("TAK");
  for (int i = 0; i < k; ++i) {
    printf("%d ", ret[i] + 1);
  }
  puts("");
  return 0;
}
