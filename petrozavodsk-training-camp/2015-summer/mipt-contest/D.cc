#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

const int N = 4e5 + 10;
struct Node {
  Node *ch[26], *fa;
  int val, rs, rt;
  Node(): fa(0), val(0), rs(-1), rt(-1) {
    memset(ch, 0, sizeof(ch));
  }
  void clear() {
    memset(ch, 0, sizeof(ch));
    fa = 0; val = 0;
    rs = rt = -1;
  }
} pool[N << 1], *rt, *last;

struct Value {
  int ps, pt, len;
};

namespace SAM {
  Node *sz = pool;
  void init() {
    if (sz != pool) {
      for (Node *p = pool; p < sz; ++ p) p->clear();
    }
    sz = pool; rt = sz ++; last = rt;
  }
  void add(int c) {
    Node *p = last, *np = sz ++;
    last = np; np->val = p->val + 1;
    for (; p && !p->ch[c]; p = p->fa) p->ch[c] = np;
    if (p) {
      Node *q = p->ch[c];
      if (p->val + 1 == q->val) np->fa = q;
      else {
        Node *nq = sz ++; *nq = *q;
        nq->val = p->val + 1;
        q->fa = nq; np->fa = nq;
        for (; p && p->ch[c] == q; p = p->fa) p->ch[c] = nq;
      }
    }
    else np->fa = rt;
  }
  void build(char *s, char *t, int n, int m) {
    init();
    for (int i = 0; i < n; ++ i) {
      add(s[i] - 'a');
      last->rs = i;
    }
    last = rt;
    for (int i = 0; i < m; ++i) {
      add(t[i] - 'a');
      last->rt = i;
    }

    static Node* Q[N << 1];
    static int cnt[N];
    for (int i = 0; i <= n + m; ++ i) cnt[i] = 0;
    for (Node *p = pool; p < sz; ++ p) cnt[p->val] ++;
    for (int i = 1; i <= n + m; ++ i) cnt[i] += cnt[i - 1];
    for (Node *p = pool; p < sz; ++ p) Q[-- cnt[p->val]] = p;
    for (int i = (sz - pool) - 1; i >= 0; -- i) {
      Node *p = Q[i];
      if (p->fa) {
        p->fa->rs = std::max(p->fa->rs, p->rs);
        p->fa->rt = std::max(p->fa->rt, p->rt);
      }
    }
  }
  std::vector<Value> get() {
    std::vector<Value> ret;
    ret.reserve(sz - pool);
    for (Node *p = pool; p < sz; ++p) if (p->rs != -1 && p->rt != -1 && p->val) {
      ret.emplace_back();
      ret.back().ps = p->rs;
      ret.back().pt = p->rt;
      ret.back().len = p->val;
    }
    return ret;
  }
}

char s[N], t[N];
std::pair<int, int> best_x, best_y;
int best, do_swap, nn;

std::pair<int, int> bit1[N];
int bit2[N];

void add1(int x, int v) {
  auto w = std::make_pair(v, x);
  for (; x <= nn; x += ~x & x + 1) {
    bit1[x] = std::max(bit1[x], w);
  }
}
void add2(int x, int v) {
  for (; x >= 0; x -= ~x & x + 1) {
    bit2[x] = std::min(bit2[x], v);
  }
}

int main() {
  scanf("%s%s", s, t);
  int n = strlen(s);
  int m = strlen(t);
  SAM::build(s, t, n, m);
  auto ys = SAM::get();
  std::reverse(s, s + n);
  std::reverse(t, t + m);
  SAM::build(s, t, n, m);
  auto xs = SAM::get();
  best = 0; do_swap = 0;
  best_x = {0, 0}; best_y = {0, 0};
  for (auto &e: xs) {
    e.ps = n - 1 - e.ps;
    e.pt = m - 1 - e.pt;
    if (e.len > best) {
      best = e.len;
      best_x = {e.pt, e.len};
      best_y = {0, 0};
    }
  }

  nn = std::max(n, m);

  auto solve = [&](bool flag) {
    std::sort(ys.begin(), ys.end(), [](const Value &a, const Value &b) {
        return a.ps - a.len < b.ps - b.len;
        });
    std::sort(xs.begin(), xs.end(), [](const Value &a, const Value &b) {
        return a.ps + a.len < b.ps + b.len;
        });
    for (int i = 0; i <= nn; ++i) {
      bit1[i] = {0, i};
      bit2[i] = nn;
    }
    for (size_t i = 0, j = 0; i < ys.size(); ++i) {
      for (; j < xs.size() && xs[j].ps + xs[j].len <= ys[i].ps - ys[i].len + 1; ++j) {
        add1(xs[j].pt + xs[j].len, xs[j].len);
        add2(xs[j].pt + xs[j].len, xs[j].pt);
      }
      for (int x = ys[i].pt - ys[i].len + 1; x >= 0; x -= ~x & x + 1) if (bit1[x].first) {
        auto len = bit1[x].first + ys[i].len;
        if (len > best) {
          best = len;
          do_swap = flag;
          best_x = {bit1[x].second - bit1[x].first, bit1[x].first};
          best_y = {ys[i].pt - ys[i].len + 1, ys[i].len};
        }
      }
      for (int x = ys[i].pt - ys[i].len + 2; x <= nn; x += ~x & x + 1) if (bit2[x] <= ys[i].pt) {
        auto len = ys[i].pt - bit2[x] + 1;
        if (len > best) {
          best = len;
          do_swap = flag;
          best_x = {bit2[x], len - ys[i].len};
          best_y = {ys[i].pt - ys[i].len + 1, ys[i].len};
        }
      }
    }
  };

  solve(false);
  for (auto &e: xs) std::swap(e.ps, e.pt);
  for (auto &e: ys) std::swap(e.ps, e.pt);
  solve(true);

  std::reverse(s, s + n);
  std::reverse(t, t + m);
  std::string a, b;
  if (do_swap) {
    for (int i = 0; i < best_x.second; ++i) putchar(s[i + best_x.first]), a += s[i + best_x.first];
    puts("");
    for (int i = 0; i < best_y.second; ++i) putchar(s[i + best_y.first]), b += s[i + best_y.first];
    puts("");
  } else {
    for (int i = 0; i < best_x.second; ++i) putchar(t[i + best_x.first]), a += t[i + best_x.first];
    puts("");
    for (int i = 0; i < best_y.second; ++i) putchar(t[i + best_y.first]), b += t[i + best_y.first];
    puts("");
  }
  return 0;
}
