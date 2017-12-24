#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
  int T; scanf("%d", &T);
  for (int _ = 0; _ < T; ++ _) {
    int A, B, N; scanf("%d%d%d", &A, &B, &N);
    LL left = min(A, B), right = (LL)max(A, B) * N;
    int AB = A * B / __gcd(A, B);
    while (left < right) {
      LL mid = (left + right - 1) >> 1;
      LL cnt = mid / A + mid / B - mid / AB;
      if (cnt >= N) right = mid;
      else left = mid + 1;
    }
    printf("%lld\n", left);
  }
  return 0;
}
