#include <cstdio>
#include <map>
#include <functional>

int gg[10][10], rr[10][10], bb[10][10];
std::map<int, int> cg, cr, cb;

std::pair<int, int> get(int n) {
  int b = n % 10, a = b;
  for (; n > 0; n /= 10) a = n % 10;
  return {a, b};
}

void input(int n, int f[10][10], std::map<int, int>& cnt) {
  for (int i = 0; i < n; ++i) {
    int x, a, b;
    scanf("%d", &x);
    cnt[x]++;
    std::tie(a, b) = get(x);
    f[a][b]++;
  }
}

int main() {
  int x, y, z;
  scanf("%d%d%d", &x, &y, &z);
  input(x, gg, cg); input(y, rr, cr); input(z, bb, cb);
  long long ret = 0;
  for (int a = 0; a < 10; ++a) {
    for (int b = 0; b < 10; ++b) {
      for (int c = 0; c < 10; ++c) {
        for (int d = 0; d < 10; ++d) {
          ret += 1ll * gg[a][b] * rr[b][c] * bb[c][d];
        }
      }
    }
  }
  for (auto &&e: cg) {
    int a, b;
    std::tie(a, b) = get(e.first);
    if (cr.count(e.first) && a == b) {
      for (int d = 0; d < 10; ++d) {
        ret -= 1ll * e.second * cr[e.first] * bb[a][d];
      }
    }
    if (cb.count(e.first)) {
      ret -= 1ll * e.second * cb[e.first] * rr[b][a];
    }
    if (cr.count(e.first) && cb.count(e.first) && a == b) {
      ret += 2ll * e.second * cr[e.first] * cb[e.first];
    }
  }
  for (auto &&e: cr) {
    int b, c;
    std::tie(b, c) = get(e.first);
    if (cb.count(e.first) && b == c) {
      for (int a = 0; a < 10; ++a) {
        ret -= 1ll * e.second * cb[e.first] * gg[a][b];
      }
    }
  }
  printf("%lld\n", ret);
  return 0;
}
