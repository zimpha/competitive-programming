#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 10;

char s[N];
int sum[N * 2], q[N * 2];
int n, m, len;

bool valid(int cnt, int l, int r) {
  int d = n - m - l;
  if (d < 0) d = d & 1;
  // mm + nn = n + m - cnt
  // nn - mm = d + r
  int mm = (n + m - cnt - d - r) / 2;
  return mm > 0;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d%s", &n, &m, s);
    if (n < m) std::swap(n, m);
    len = strlen(s);
    sum[0] = 0;
    for (int i = 1; i <= len * 2; ++i) {
      sum[i] = sum[i - 1];
      if (s[(i - 1) % len] == 'G') sum[i] -= 1;
      else sum[i] += 1;
    }
    int ret = 0;
    int head = 0, tail = -1;
    for (int i = len * 2, j = len * 2; i >= 1; --i) {
      while (j - i + 1 > len) --j;
      while (head <= tail && sum[i] <= sum[q[tail]]) --tail;
      q[++tail] = i;
      for (; i <= j; --j) {
        while (head <= tail && q[head] > j) ++head;
        assert(head <= tail);
        int l = sum[i - 1] - sum[q[head]];
        int r = sum[j] - sum[q[head]];
        if (valid(j - i + 1, l, r)) break;
      }
      ret = std::max(ret, j - i + 1);
    }
    printf("%d\n", std::min(ret + 1, len));
  }
  return 0;
}
