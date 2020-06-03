#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int cnt[101] = {0};
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    cnt[x]++;
    sum += x;
  }
  int ret = sum;
  for (int i = 1; i <= 100; ++i) {
    for (int j = 1; j <= 100; ++j) if (cnt[i] && cnt[j]) {
      if (i == j && cnt[i] < 2) continue;
      sum -= i + j;
      for (int x = 1; x <= i; ++x) if (i % x == 0) {
        sum += i / x + j * x;
        if (sum < ret) ret = sum;
        sum -= i / x + j * x;
      }
      sum += i + j;
    }
  }
  printf("%d\n", ret);
  return 0;
}
