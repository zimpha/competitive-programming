#include <cstdio>
#include <vector>

const int N = 2e5 + 20;

std::vector<int> ql[N];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  int s = 1, l = 0;
  while (s <= n) s *= 2, ++l;
  int t = 1 << (l / 2);
  std::vector<int> ret(q, 0), K(q), X(q);
  for (int it = 0; it < q; ++it) {
    int k, x;
    scanf("%d%d", &k, &x);
    --x;
    k %= s;
    K[it] = k % t;
    X[it] = x;
    ql[k / t].emplace_back(it);
  }
  for (int i = 0; i < t * 2; ++i) {
    for (auto &&e: ql[i]) {
      for (int y = 0; y <= K[e]; ++y) {
        if ((K[e] & y) == y && y + X[e] < n) {
          ret[e] ^= a[y + X[e]];
        }
      }
    }
    std::vector<int> b(n);
    for (int j = 0; j < n; ++j) {
      b[j] = a[j];
      if (j + t < n) b[j] ^= a[j + t];
    }
    a.swap(b);
  }
  for (int i = 0; i < q; ++i) printf("%d\n", ret[i]);
  return 0;
}
