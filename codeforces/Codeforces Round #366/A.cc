#include <bits/stdc++.h>

const int N = 300000 + 10;

int sum[N << 2], tag[N << 2];

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

void psd(int rt) {
  if (tag[rt]) {
    sum[lson] = sum[rson] = 0;
    tag[lson] = tag[rson] = 1;
  }
  tag[rt] = 0;
}

void ins(int rt, int l, int r, int T) {
  if (r <= T) {
    sum[rt] = 0;
    tag[rt] = 1;
    return;
  }
  psd(rt);
  ins(lson, l, mid, T);
  if (mid < T) ins(rson, mid, r, T);
  sum[rt] = sum[lson] + sum[rson];
}

void set(int rt, int l, int r, int x, int v) {
  if (l + 1 == r) {
    sum[rt] = v;
    return;
  }
  psd(rt);
  if (x < mid) set(lson, l, mid, x, v);
  else set(rson, mid, r, x, v);
  sum[rt] = sum[lson] + sum[rson];
}

int ask(int rt, int l, int r, int T) {
  if (r <= T) return sum[rt];
  psd(rt);
  int ret = ask(lson, l, mid, T);
  if (mid < T) ret += ask(rson, mid, r, T);
  return ret;
}

std::vector<int> note[N];

void run() {
  int n, q, m = 0;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < q; ++i) {
    int op, x;
    scanf("%d%d", &op, &x);
    if (op == 1) {
      note[x].push_back(m++);
      set(1, 0, q, note[x].back(), 1);
    } else if (op == 2) {
      for (auto &&e: note[x]) {
        set(1, 0, q, e, 0);
      }
      note[x].clear();
    } else if (op == 3) {
      ins(1, 0, q, x);
    }
    printf("%d\n", sum[1]);
  }
}

int main() {
  run();
  return 0;
}
