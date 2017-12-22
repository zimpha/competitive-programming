#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 400000 + 10;

struct Node {
  int mx, ps;
  void set(int v) {
    mx += v; ps += v;
  }
} T[MAXN << 2];
char s[MAXN];
int a[MAXN], n, q;

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

void build(int rt, int l, int r) {
  T[rt].ps = 0;
  if (l + 1 == r) {
    T[rt].mx = a[l];
    return;
  }
  build(lson, l, mid); build(rson, mid, r);
  T[rt].mx = min(T[lson].mx, T[rson].mx);
}

void psd(int rt) {
  T[lson].set(T[rt].ps);
  T[rson].set(T[rt].ps);
  T[rt].ps = 0;
}

void ins(int rt, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {T[rt].set(v); return;}
  psd(rt);
  if (L < mid) ins(lson, l, mid, L, R, v);
  if (R > mid) ins(rson, mid, r, L, R, v);
  T[rt].mx = min(T[lson].mx, T[rson].mx);
}

vector<int> can;
void get(int rt, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    can.push_back(rt);
    return;
  }
  psd(rt);
  if (L < mid) get(lson, l, mid, L, R);
  if (R > mid) get(rson, mid, r, L, R);
}

int ask(int rt, int l, int r) {
  if (l + 1 == r) {
    if (T[rt].mx >= 2) return l;
    else return r;
  }
  psd(rt);
  if (T[rson].mx >= 2) return ask(lson, l, mid);
  else return ask(rson, mid, r);
}

int main() {
  while (scanf("%d%d", &n, &q) == 2) {
    scanf("%s", s);
    int n = strlen(s);
    set<int> rhs;
    for (int i = 0; i < n; ++ i) {
      if (i) a[i] = a[i - 1];
      else a[i] = 0;
      if (s[i] == '(') a[i] ++;
      else a[i] --;
      if (s[i] == ')') rhs.insert(i);
    }
    build(1, 0, n);
    for (int i = 0; i < q; ++ i) {
      int x; scanf("%d", &x); -- x;
      if (s[x] == '(') {
        s[x] = ')'; rhs.insert(x);
        ins(1, 0, n, x, n, -2);
        x = *rhs.begin(); rhs.erase(x);
        s[x] = '(';
        ins(1, 0, n, x, n, 2);
      }
      else {
        s[x] = '('; rhs.erase(x);
        ins(1, 0, n, x, n, 2);
        can.clear();
        get(1, 0, n, 0, x + 1);
        int rt(-1);
        for (auto &p: can) if (T[p].mx < 2) rt = p;
        if (rt == -1) x = 0;
        else {
          int l(0), r(n);
          vector<int> bit;
          for (int p = rt; p > 1; p >>= 1) {
            bit.push_back(p & 1);
          }
          reverse(bit.begin(), bit.end());
          for (auto &p: bit) {
            if (p) l = (l + r) >> 1;
            else r = (l + r) >> 1;
          }
          x = ask(rt, l, r);
        }
        s[x] = ')'; rhs.insert(x);
        ins(1, 0, n, x, n, -2);
      }
      printf("%d\n", x + 1);
    }
  }
  return 0;
}

