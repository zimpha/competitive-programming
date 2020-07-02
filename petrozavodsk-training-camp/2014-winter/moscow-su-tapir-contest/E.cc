#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

struct Node {
  Node *ch[26], *fa;
  int val, sc;
  std::vector<int> children;
  Node(): fa(0), val(0), sc(0) {
    memset(ch, 0, sizeof(ch));
    children.clear();
  }
  void clear() {
    memset(ch, 0, sizeof(ch));
    children.clear();
    fa = 0; val = sc = 0;
  }
} pool[N << 1], *rt, *last;
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
    static Node* Q[N << 1];
    static int cnt[N];
    for (int i = 0; i <= n; ++ i) cnt[i] = 0;
    for (Node *p = pool; p < sz; ++ p) p->sc = 0, cnt[p->val] ++;
    for (int i = 1; i <= n; ++ i) cnt[i] += cnt[i - 1];
    for (Node *p = pool; p < sz; ++ p) Q[-- cnt[p->val]] = p;
    Node *p = rt;
    for (int i = 0; i < n; ++i) {
      p = p->ch[s[i] - 'a'];
      p->sc = i + 1;
    }
    for (int i = (sz - pool) - 1; i >= 0; -- i) {
      Node *p = Q[i];
      if (p->fa) {
        p->fa->sc = std::max(p->fa->sc, p->sc);
        p->fa->children.push_back(p - pool);
      }
    }
  }
  void build(char *s, int n) {
    init();
    for (int i = 0; i < n; ++ i) add(s[i] - 'a');
    getRight(s, n);
  }

  struct Value {
    int mx;
    int id;
    int64 sum;
  };

  std::vector<Value> stk[N << 1];
  int top;
  int lower_bound(int value) {
    if (stk[top].back().mx >= value) return top;
    if (stk[0].back().mx < value) return -1;
    int l = 0, r = top;
    while (l < r) {
      int m = (l + r + 1) >> 1;
      if (stk[m].back().mx >= value) l = m;
      else r = m - 1;
    }
    return l;
  }
  int64 dfs(Node* u, int up) {
    int64 ret = 0;
    int t_top = top;
    if (u != rt) {
      int l = 0, r = top + 1;
      while (l < r) {
        int m = (l + r - 1) >> 1;
        if (m > top || stk[m].back().mx <= up) r = m;
        else l = m + 1;
      }
      top = r;
      Node* p = rt;
      int64 sum = 0;
      if (top) p = stk[top - 1].back().id + pool, sum = stk[top - 1].back().sum;
      sum += (int64)up * (u->fa->val - p->val);
      stk[top].push_back((Value){up, int(u->fa - pool), sum});
      // query
      int vl = lower_bound(u->fa->val + 1);
      int vr = lower_bound(u->val);
      if (vl == -1) ret += (int64)(u->val - u->fa->val) * u->fa->val;
      else ret += (int64)(u->val - u->fa->val) * (u->fa->val - pool[stk[vl].back().id].val);
      if (vl != vr) {
        ret -= stk[vl].back().sum;
        if (vr != -1) ret += stk[vr].back().sum;
        ret += (int64)u->val * pool[stk[vl].back().id].val;
        if (vr != -1) ret -= (int64)u->val * pool[stk[vr].back().id].val;
      }
      ret += (int64)(u->val - u->fa->val) * (u->val - u->fa->val - 1) / 2;
    }
    int mx = -1, smx = -1;
    for (auto &e: u->children) {
      Node* v = pool + e;
      if (v->sc > smx) smx = v->sc;
      if (smx > mx) std::swap(smx, mx);
    }
    for (auto &e: u->children) {
      Node* v = pool + e;
      if (v->sc == mx) ret += dfs(v, smx);
      else ret += dfs(v, mx);
    }
    if (u != rt) {
      stk[top].pop_back();
      top = t_top;
    }
    return ret;
  }

  int64 solve() {
    top = -1;
    for (int i = 0; i < (sz - pool); ++i) stk[i].clear();
    return dfs(rt, 0);
  }
}

char s[N];

int main() {
  int n;
  scanf("%d%s", &n, s);
  std::reverse(s, s + n);
  SAM::build(s, n);
  printf("%lld\n", SAM::solve());
  return 0;
}
