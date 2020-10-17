#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

const int N = 200000;

std::pair<int, int> mx[N << 2];
int a[N], p[N], n;

#define lson (rt<<1)
#define rson (rt<<1|1)

void build(int rt, int l, int r) {
  if (l + 1 == r) {
    mx[rt] = std::make_pair(a[l], l);
    return;
  }
  int m = (l + r) >> 1;
  build(lson, l, m);
  build(rson, m, r);
  mx[rt] = std::min(mx[lson], mx[rson]);
}

std::pair<int, int> ask(int rt, int l, int r, int L, int R) {
  if (L <= l && R >= r) return mx[rt];
  std::pair<int, int> ret(1e9, 0);
  int m = (l + r) >> 1;
  if (L < m) ret = std::min(ret, ask(lson, l, m, L, R));
  if (R > m) ret = std::min(ret, ask(rson, m, r, L, R));
  return ret;
}

bool solve(int l, int r, int base) {
  if (l > r) return true;
  if (l == r) {
    p[l] = l;
    return true;
  }
  std::pair<int, int> min = ask(1, 0, n - 1, l, r);
  if (min.first < base) return false;
  if (min.first == base) {
    return solve(l, min.second, base) && solve(min.second + 1, r, base);
  }
  base += 2;
  if (min.first != base) return false;
  if (a[l] != base || a[r - 1] != base) return false;
  p[l] = r; p[r] = l;
  return solve(l + 1, r - 1, base);
}

int main() {
  scanf("%d", &n);
  bool odd = false;
  for (int i = 0; i < n - 1; ++i) {
    scanf("%d", &a[i]);
    odd |= a[i] & 1;
  }
  build(1, 0, n - 1);
  if (odd || !solve(0, n - 1, 0)) puts("No");
  else {
    puts("Yes");
    for (int i = 0; i < n; ++i) {
      printf("%d ", p[i] + 1);
    }
    puts("");
  }
  return 0;
}
