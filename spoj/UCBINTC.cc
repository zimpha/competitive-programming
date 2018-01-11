#include <cstdio>
#include <vector>

const int N = 4e5 + 10, offset = 2e5;

bool mark[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    bool find = false;
    for (int j = 0; j < i && !find; ++j) {
      int v = a[i] - a[j] + offset;
      if (v >= 0 && v < N && mark[v]) find = true;
    }
    ret += find;
    for (int j = 0; j <= i; ++j) {
      mark[a[i] + a[j] + offset] = 1;
    }
  }
  printf("%d\n", ret);
  return 0;
}
