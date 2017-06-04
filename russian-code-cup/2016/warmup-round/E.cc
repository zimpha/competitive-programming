#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Event {
  int val, idx;
  bool operator < (const Event &rhs) const {
    return val < rhs.val || (val == rhs.val && idx > rhs.idx);
  }
};

const int MAXN = 100000 + 10;
const LL inf = (LL)2e14;
struct Node {
  LL sum, ml, mr, opt;
  Node() {}
  Node(LL x): sum(x), ml(x), mr(x), opt(x) {}
} T[MAXN << 2];

Node upd(Node &A, Node &B) {
  Node C;
  C.sum = A.sum + B.sum;
  C.ml = max(A.ml, A.sum + B.ml);
  C.mr = max(B.mr, B.sum + A.mr);
  C.opt = max(max(A.opt, B.opt), A.mr + B.ml);
  return C;
}

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)
void build(int rt, int l, int r) {
  if (l + 1 == r) {
    T[rt].sum = -inf;
    T[rt].ml = T[rt].mr = -inf;
    T[rt].opt = -inf;
    return;
  }
  build(lson, l, mid);
  build(rson, mid, r);
  T[rt] = upd(T[lson], T[rson]);
}
void ins(int rt, int l, int r, int x, LL v) {
  if (l + 1 == r) {
    T[rt].sum = T[rt].ml = T[rt].mr = T[rt].opt = v;
    return;
  }
  if (x < mid) ins(lson, l, mid, x, v);
  else ins(rson, mid, r, x, v);
  T[rt] = upd(T[lson], T[rson]);
}
Node ask(int rt, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[rt];
  Node x(-inf), y(-inf);
  x.sum = y.sum = 0;
  if (L < mid) x = ask(lson, l, mid, L, R);
  if (R > mid) y = ask(rson, mid, r, L, R);
  return upd(x, y);
}

vector<Event> pt;
LL ret[MAXN];
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int x; scanf("%d", &x);
    pt.push_back((Event){x, i});
  }
  for (int i = 0; i < m; ++i) {
    int x; scanf("%d", &x);
    pt.push_back((Event){x, i + n});
  }
  sort(pt.begin(), pt.end());
  build(1, 0, n);
  for (int i = pt.size() - 1; i >= 0; --i) {
    if (pt[i].idx < n) {
      ins(1, 0, n, pt[i].idx, pt[i].val);
    } else {
      ret[pt[i].idx - n] = ask(1, 0, n, 0, n).opt;
    }
  }
  for (int i = 0; i < m; ++i) {
    if (ret[i] <= -inf) ret[i] = 0;
    printf("%lld ", ret[i]);
  }
  puts("");
  return 0;
}
