#include <cstdio>
#include <vector>
#include <bitset>

const int N = 2048000;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> w;
  for (int i = 0, x; i <= n; ++i) {
    scanf("%d", &x);
    for (int s = 1; s <= x; s *= 2) {
      w.push_back(s * (1 << i));
      x -= s;
    }
    if (x) w.push_back(x * (1 << i));
  }
  std::bitset<N> f;
  f[0] = 1;
  for (auto &x: w) {
    f |= f << x;
  }
  for (int i = 1; i < N; ++i) {
    if (!f[i]) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
