#include <cmath>
#include <cstdio>
#include <cassert>

const int all[] = {2, 4, 9, 16, 25, 64, 289, 729, 1681, 2401, 3481, 4096, 5041, 7921, 10201, 15625, 17161, 27889, 28561, 29929, 65536, 83521, 85849, 146689, 262144, 279841, 458329, 491401, 531441, 552049, 579121, 597529, 683929, 703921, 707281, 734449, 829921, 0};

const int N = 1e6 + 10;

int sum[N];

int main() {
  for (int i = 0; all[i]; ++i) sum[all[i]] = 1;
  for (int i = 1; i < N; ++i) {
    sum[i] += sum[i - 1];
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", sum[b] - sum[a - 1]);
  }
  return 0;
}
