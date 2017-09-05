#include <bits/stdc++.h>

const int N = 1000 + 10;

struct node {
  node *l, *r, *u, *d;
  int val;
} cell[N][N];
int n, m, q;

node *get_cell(int r, int c) {
  node *res = &cell[0][0];
  for (int i = 0; i < r; ++i) {
    res = res->d;
  }
  for (int i = 0; i < c; ++i) {
    res = res->r;
  }
  return res;
}

void run() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &cell[i][j].val);
    }
  }
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= m + 1; ++j) {
      if (i) {
        cell[i][j].u = &cell[i - 1][j];
        cell[i - 1][j].d = &cell[i][j];
      }
      if (j) {
        cell[i][j].l = &cell[i][j - 1];
        cell[i][j - 1].r = &cell[i][j];
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    int a, b, c, d, w, h;
    scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &h, &w);
    node *ul1 = get_cell(a, b);
    node *ul2 = get_cell(c, d);
    node *ur1 = get_cell(a, b + w - 1);
    node *ur2 = get_cell(c, d + w - 1);
    for (int j = 0; j < h; ++j) {
      node *r1 = ul1, *r2 = ul2;
      node *l1 = r1->l, *l2 = r2->l;
      r1->l = l2, r2->l = l1;
      l1->r = r2, l2->r = r1;
      l1 = ur1, l2 = ur2;
      r1 = l1->r, r2 = l2->r;
      r1->l = l2, r2->l = l1;
      l1->r = r2, l2->r = r1;
      ul1 = ul1->d, ul2 = ul2->d;
      ur1 = ur1->d, ur2 = ur2->d;
    }
    ul1 = get_cell(a, b);
    ul2 = get_cell(c, d);
    node *bl1 = get_cell(a + h - 1, b);
    node *bl2 = get_cell(c + h - 1, d);
    for (int j = 0; j < w; ++j) {
      node *d1 = ul1, *d2 = ul2;
      node *u1 = d1->u, *u2 = d2->u;
      u1->d = d2, u2->d = d1;
      d1->u = u2, d2->u = u1;
      u1 = bl1, u2 = bl2;
      d1 = u1->d, d2 = u2->d;
      u1->d = d2, u2->d = d1;
      d1->u = u2, d2->u = u1;
      ul1 = ul1->r, ul2 = ul2->r;
      bl1 = bl1->r, bl2 = bl2->r;
    }
  }
  for (int i = 1; i <= n; ++i) {
    node *cur = &cell[i][0];
    for (int j = 1; j <= m; ++j) {
      cur = cur->r;
      printf("%d ", cur->val);
    }
    puts("");
  }
}

int main() {
  run();
  return 0;
}
