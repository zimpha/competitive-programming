#include "interaction.h"

int guess(int index) {
  int l = 0, r = 1000000;
  while (l < r) {
    int m = (l + r) >> 1;
    int res = guess(index, m);
    if (res == 0) return m;
    if (res == -1) l = m + 1;
    else r = m - 1;
  }
  return l;
}

int main() {
  int n = get_num();
  std::vector<int> res(n);
  for (int i = 0; i < n; ++i) {
    res[i] = guess(i);
  }
  submit(res);
  return 0;
}
