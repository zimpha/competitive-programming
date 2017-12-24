#include <cstdio>
#include <vector>

const int N = 3e6 + 10;

int sg[N];

int main() {
  std::vector<int> fib = {1, 1};
  for (int i = 2; ; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
    if (fib.back() > N) break;
  }
  sg[0] = 0;
  int mark[40] = {};
  for (int i = 1; i < N; ++i) {
    for (auto &&x: fib) {
      if (x <= i) mark[sg[i - x]] = 1;
    }
    for (sg[i] = 0; mark[sg[i]]; ++sg[i]);
    for (auto &&x: fib) {
      if (x <= i) mark[sg[i - x]] = 0;
    }
  }
  int n;
  scanf("%d", &n);
  int ret = 0;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    ret ^= sg[x];
  }
  if (ret) puts("Ada");
  else puts("Vinit");
  return 0;
}
