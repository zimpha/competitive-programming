#include <bits/stdc++.h>

const int MAXN = 200000 + 1000;

struct Node {
  Node *ch[26], *fa;
  int val, sc;
  Node(): fa(0), val(0), sc(0) {
    memset(ch, 0, sizeof(ch));
  }
  void clear() {
    memset(ch, 0, sizeof(ch));
    fa = 0; val = sc = 0;
  }
} pool[MAXN << 1], *rt, *last;
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
  void getRight(char *s, int n) {
    static Node* Q[MAXN << 1];
    static int cnt[MAXN];
    for (int i = 0; i <= n; ++ i) cnt[i] = 0;
    for (Node *p = pool; p < sz; ++ p) p->sc = 0, cnt[p->val] ++;
    for (int i = 1; i <= n; ++ i) cnt[i] += cnt[i - 1];
    for (Node *p = pool; p < sz; ++ p) Q[-- cnt[p->val]] = p;
    for (Node *p = rt; ; p = p->ch[s[p->val] - 'a']) {
      p->sc = 1; if (p->val == n) break;
    }
    for (int i = (sz - pool) - 1; i >= 0; -- i) {
      Node *p = Q[i]; if (p->fa) p->fa->sc += p->sc;
    }
  }
  void build(char *s, int n) {
    init();
    for (int i = 0; i < n; ++ i) add(s[i] - 'a');
    getRight(s, n);
  }
}

const int M = 500;

std::vector<int> cnt[M][M];
char s[MAXN], w[MAXN];
int l[MAXN], r[MAXN];
int n, m, q, k;

void solve_small() {
  for (int i = 0; i < m; ++i) {
    cnt[l[i]][r[i]].push_back(i);
  }
  auto count = [](const std::vector<int> &v, int a, int b) {
    return std::upper_bound(v.begin(), v.end(), b) - std::lower_bound(v.begin(), v.end(), a);
  };
  SAM::build(s, n);
  for (int it = 0; it < q; ++it) {
    int a, b;
    scanf("%s%d%d", w, &a, &b);
    long ret = 0;
    for (int i = 0; w[i]; ++i) {
      Node *p = rt;
      for (int j = i; w[j]; ++j) {
        p = p->ch[w[j] - 'a'];
        if (!p) break;
        ret += count(cnt[i][j], a, b) * p->sc;
      }
    }
    printf("%ld\n", ret);
  }
}

struct SparseTable {
  static int lg[MAXN];
  int u[MAXN][20];
  static void init() {
    lg[0] = -1;
    for (int i = 1; i < MAXN; ++i) {
      lg[i] = lg[i >> 1] + 1;
    }
  }
  void build(int a[], int n) {
    for (int i = 0; i < n; ++i) u[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        u[i][j] = std::min(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int ask(int a, int b) {
    if (a > b) std::swap(a, b);
    int k = lg[b - a + 1];
    return std::min(u[a][k], u[b - (1 << k) + 1][k]);
  }
};

int SparseTable::lg[MAXN];

namespace SA {
  int cnt[MAXN], tr[2][MAXN], ts[MAXN];
  int sa[MAXN], rk[MAXN], ht[MAXN];
  SparseTable rmq;
  void build(int *s, int n, int m = 256) {
    int i, k, *x = tr[0], *y = tr[1];
    memset(cnt, 0,sizeof(cnt[0]) * m);
    for (i = 0; i < n; ++i) cnt[(int)s[i]]++;
    std::partial_sum(cnt, cnt + m, cnt);
    for (i = 0; i < n; ++i) rk[i] = cnt[(int)s[i]] - 1;
    for (k = 1; k <= n; k <<= 1) {
      for (i = 0; i < n; ++i) {
        x[i] = rk[i];
        y[i] = i + k < n ? rk[i + k] + 1 : 0;
      }
      std::fill(cnt, cnt + n + 1, 0);
      for (i = 0; i < n; ++i) cnt[y[i]]++;
      std::partial_sum(cnt, cnt + n + 1, cnt);
      for (i = n - 1; i >= 0; --i) ts[--cnt[y[i]]] = i;
      std::fill(cnt, cnt + n + 1, 0);
      for (i = 0; i < n; ++i) cnt[x[i]]++;
      std::partial_sum(cnt, cnt + n + 1, cnt);
      for (i = n - 1; i >= 0; --i) sa[--cnt[x[ts[i]]]] = ts[i];
      for (i = rk[sa[0]] = 0; i+1 < n; ++i) {
        rk[sa[i + 1]] = rk[sa[i]] +
          (x[sa[i]] != x[sa[i + 1]] || y[sa[i]] != y[sa[i + 1]]);
      }
    }
  }
  void get_height(int *s, int n) {
    for (int i = 0, l = 0, j; i < n; ++i) if (rk[i]) {
      j = sa[rk[i] - 1];
      while(i + l < n && j + l < n && s[i + l] == s[j + l]) l++;
      ht[rk[i]] = l; if (l) l--;
    }
  }
  void init_rmq(int n) {
    rmq.build(ht, n);
  }
  inline int lcp(int a, int b) {
    a = rk[a], b = rk[b];
    if (a > b) std::swap(a, b);
    if (a == b) return 1e9;
    return rmq.ask(a + 1, b);
  }
};

int buffer[MAXN], len;
int a[MAXN], b[MAXN];

void solve_large() {
  len = 0;
  int sep = 26;
  for (int i = 0; i < n; ++i) {
    buffer[len++] = s[i] - 'a';
  }
  buffer[len++] = sep++;
  for (int it = 0; it < q; ++it) {
    scanf("%s%d%d", w, &a[it], &b[it]);
    for (int i = 0; w[i]; ++i) {
      buffer[len++] = w[i] - 'a';
    }
    buffer[len++] = sep++;
  }
  using namespace SA;
  SA::build(buffer, len);
  SA::get_height(buffer, len);
  SA::init_rmq(len);
  std::vector<int> mark(len, 0);
  for (int i = 0; i < len; ++i) {
    if (SA::sa[i] < n) mark[i] = 1;
  }
  for (int i = 1; i < len; ++i) {
    mark[i] += mark[i - 1];
  }
  auto find_left = [&](int start, int least) {
    int left = 0, right = start;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      assert(mid < start);
      if (SA::rmq.ask(mid + 1, start) < least) left = mid + 1;
      else right = mid;
    }
    return left;
  };
  auto find_right = [&](int start, int least) {
    int left = start, right = len - 1;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (SA::rmq.ask(start + 1, mid) >= least) left = mid;
      else right = mid - 1;
    }
    return left;
  };
  for (int it = 0; it < q; ++it) {
    long ret = 0;
    for (int i = a[it]; i <= b[it]; ++i) {
      int least = r[i] - l[i] + 1;
      int start = SA::rk[n + (k + 1) * it + l[i] + 1];
      //std::cout << start << " ";
      int x = find_left(start, least);
      int y = find_right(start, least);
      ret += mark[y] - (x ? mark[x - 1] : 0);
      //std::cout << (mark[y] - (x ? mark[x - 1] : 0)) << " ";
      //std::cout << start << ' ' << x << ' ' << y << std::endl;
    }
    printf("%ld\n", ret);
  }
}

int main() {
  SparseTable::init();
  scanf("%d%d%d%d", &n, &m, &q, &k);
  scanf("%s", s);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", l + i, r + i);
  }
  if (k < 0) solve_small();
  else solve_large();
  return 0;
}
