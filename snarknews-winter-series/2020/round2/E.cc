#include <cstdio>
#include <cassert>
#include <map>
#include <algorithm>

using int64 = long long;

std::map<int, int64> down;
std::map<int, int64> val;
int n, q;

int64 get_val(int x) {
  if (x > n) return 0;
  auto it = val.find(x);
  if (it == val.end()) return x;
  else return it->second;
}

int height(int x) {
  return 31 - __builtin_clz(n / x);
}

int64 get_mx(int x) {
  if (x > n) return 0;
  auto it = down.find(x);
  if (it != down.end()) return it->second;
  int64 ret = 0;
  for (; x <= n; ) {
    ret += x;
    int l = x * 2, r = l + 1;
    if (r > n) x = l;
    else {
      if (height(l) > height(r)) x = l;
      else x = r;
    }
  }
  return ret;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < q; ++i) {
    int op, x, y;
    int64 v;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%lld", &x, &v);
      val[x] = v;
      for (; x >= 1; x /= 2) {
        down[x] = std::max(get_mx(x * 2), get_mx(x * 2 + 1)) + get_val(x);
      }
    } else {
      scanf("%d", &x);
      int64 ret = get_mx(x * 2) + get_mx(x * 2 + 1) + get_val(x);
      int64 now = get_mx(x);
      for (y = x, x /= 2; x >= 1; y = x, x /= 2) {
        now += get_val(x);
        if (x * 2 == y) ret = std::max(ret, now + get_mx(y + 1));
        else ret = std::max(ret, now + get_mx(y - 1));
      }
      printf("%lld\n", ret);
    }
  }
  return 0;
}
