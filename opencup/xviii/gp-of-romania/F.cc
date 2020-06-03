#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

void update(int &x, int y) {
  if (y == -1) return;
  if (x == -1 || x > y) x = y;
}

int solve(int x, int y, int z, int a, int b, int c) {
  int n = x + y + z;
  if (z >= x) {
    int step = 2 * x;
    z -= x;
    y += std::min(step, b);
    if (b < step) b = 0, x = step - b;
    else b -= step, x = 0;
    if (x == 0) {
      if (z == 0) return step;
      int more_step = std::max(0, std::min(z - 1, std::min(a, b)));
      step += more_step * 2;
      z -= more_step, a -= more_step;
      b -= more_step, y += more_step;
      if (z == 1 && b) return step + 1;
      // a == 0, b == 0 or z == 1
      if (a == 0) {
        if (b + y >= n) return step + z * 2 - 1;
      }
    } else {
      assert(b >= 0);
    }
  } else {
    if (!z && !y) return -1;
    int extra = 0;
    if (!z) {
      --y, ++extra;
      if (b) --b, ++y;
      else if (c) --c, ++z;
      else if (a) --a, ++x;
    }
    auto step = solve(z, y, x, c, b, a);
    if (step != -1) return step + extra;
  }
  return -1;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<std::pair<int, int>> a(n);
  std::vector<int> cnt(n + k + 1);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }
  std::sort(a.begin(), a.end());
  for (int i = 0, x; i < k; ++i) {
    scanf("%d", &x);
    cnt[x]++;
  }
  for (int i = 1; i <= n + k; ++i) cnt[i] += cnt[i - 1];

  int ret = -1;

  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && (j == i || a[j].second > a[j - 1].second); ++j);
    int L = i == 0 ? 0 : a[i - 1].first;
    int R = j == n ? n + k + 1 : a[j].first;
    int x = i, y = j - i, z = n - j;
    update(ret, solve(x, y, z, cnt[L], cnt[R - 1] - cnt[L], k - cnt[R - 1]));
    printf("L=%d R=%d step=%d\n", L, R, solve(x, y, z, cnt[L], cnt[R - 1] - cnt[L], k - cnt[R - 1]));
  }
  for (int i = 0; i < n; ++i) {
    int L = i == 0 ? 0 : a[i - 1].first;
    int R = a[i].first;
    int x = i, y = 0, z = n - i;
    update(ret, solve(x, y, z, cnt[L], cnt[R - 1] - cnt[L], k - cnt[R - 1]));
  }
  printf("%d\n", ret);
  return 0;
}
