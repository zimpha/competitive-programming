#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <vector>
#include <algorithm>

using State = std::bitset<30001>;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int> x(n * 2);
  for (int i = 0; i < n * 2; ++i) {
    scanf("%d", &x[i]);
  }
  std::vector<State> dp(n);
  dp[0][0] = 1;
  for (int i = 2; i < n * 2; i += 2) {
    dp[i / 2] = dp[i / 2 - 1] | (dp[i / 2 - 1] << (x[i] - x[i - 1]));
  }
  int expected = x.back() - x[0] - k;
  if (expected < 0 || dp.back()[expected] == 0) {
    puts("No");
    return 0;
  }
  std::vector<int> mate(n * 2 + 1, -1);
  mate[n * 2] = n * 2;
  int last = n * 2 - 1;
  for (int i = n * 2 - 2; i >= 2; i -= 2) {
    int diff = x[i] - x[i - 1];
    assert(dp[i / 2][expected]);
    if (expected >= diff && dp[i / 2 - 1][expected - diff]) {
      mate[i] = last;
      last = i - 1;
      expected -= diff;
    }
  }
  mate[0] = last;
  for (int i = 0; i < n * 2; i = mate[i] + 1) {
    for (int j = i + 1; j < mate[i]; j += 2) mate[j] = j + 1;
  }
  puts("Yes");
  for (int i = 0; i < n * 2; ++i) {
    if (mate[i] != -1) printf("%d %d\n", i + 1, mate[i] + 1);
  }
  return 0;
}
