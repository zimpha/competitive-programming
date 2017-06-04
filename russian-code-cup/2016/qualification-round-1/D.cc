#include <bits/stdc++.h>
using namespace std;
typedef double flt;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 100000 + 10, SIZE = 1000000 + 10, P = 900;

LL ret[P], u[SIZE];
int t[MAXN];
int n, m;

void add(int x, int v) {
  for (; x < SIZE; x += ~x & x + 1) u[x] += v;
}
int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += u[x];
  return r;
}

void del(int x) {
  x = t[x];
  add(x, -1);
  for (int i = 1; i < P; ++i) ret[i] -= x / i + !!(x % i);
}

void ins(int x) {
  x = t[x];
  add(x, 1);
  for (int i = 1; i < P; ++i) ret[i] += x / i + !!(x % i);
}

void run() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", t + i);
    ins(i);
  }
  for (int _ = 0; _ < m; ++_) {
    int op, x; scanf("%d%d", &op, &x);
    if (op == 1) {
      --x;
      del(x); t[x]++; ins(x);
    } else if (op == 2) {
      --x;
      del(x); t[x]--; ins(x);
    } else {
      if (x < P) printf("%lld\n", ret[x]);
      else {
        LL ans = 0;
        int cnt = 0;
        for (int i = 1; cnt < n; ++i) {
          int l = x * (i - 1) + 1, r = x * i;
          int s = get(r) - get(l - 1); cnt += s;
          ans += 1ll * i * (get(r) - get(l - 1));
        }
        printf("%lld\n", ans);
      }
    }
    //for (int i = 0; i < n; ++i) cerr << t[i] << " "; cerr << endl;
  }
}

int main() {
  run();
  return 0;
}
