#include <bits/stdc++.h>

const int N = 200000 + 10;

int go[N * 30][2], sz[N * 30];
int cnt, q;

void ins(int x, int v) {
  int p = 0;
  for (int i = 30; ~i; --i) {
    int o = x >> i & 1;
    sz[p] += v;
    if (!go[p][o]) go[p][o] = cnt++;
    p = go[p][o];
  }
  sz[p] += v;
}

int ask(int x) {
  int ret = 0;
  for (int p = 0, i = 30; ~i; --i) {
    int  o = x >> i & 1;
    if (p == -1) continue;
    if (go[p][!o] && sz[go[p][!o]]) ret |= 1 << i, o ^= 1;
    if (!go[p][o]) p = -1;
    else p = go[p][o];
  }
  return ret;
}

void run() {
  scanf("%d", &q);
  cnt = 1;
  ins(0, 1);
  for (int i = 0; i < q; ++i) {
    char op;
    int x;
    scanf(" %c%d", &op, &x);
    if (op == '+') ins(x, 1);
    else if (op == '-') ins(x, -1);
    else printf("%d\n", ask(x));
  }
}

int main() {
  run();
  return 0;
}
