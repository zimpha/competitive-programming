#include <cmath>
#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>

const int N = 40, S = 2e5 + 10;

using state = std::bitset<S>;
state reach[N];

int main() {
  int n, m, k, q, sum = 0;
  scanf("%d%d%d%d", &n, &m, &k, &q);
  std::vector<int> weight(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &weight[i]);
    sum += weight[i];
  }
  state secret;
  for (int i = 0; i <= m; ++i) {
    int upp = (weight[0] - 1) * i;
    int rest = (weight[0] - 1) * (m - i);
    for (int s = i; s <= k - sum && s <= upp; ++s) {
      if (m - i <= k - sum - s && k - sum - s <= rest) secret[s] = 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    reach[i] = secret;
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      reach[i] |= reach[i] << weight[j];
    }
  }
  for (int it = 0; it < q; ++it) {
    int x;
    scanf("%d", &x);
    std::vector<int> valid;
    for (int i = 0; i < n; ++i) {
      if (!reach[i][x]) valid.push_back(i);
    }
    if (valid.empty()) puts("-1");
    else {
      for (size_t i = 0; i < valid.size(); ++i) {
        if (i) putchar(' ');
        printf("%d", valid[i] + 1);
      }
      puts("");
    }
  }
  return 0;
}
