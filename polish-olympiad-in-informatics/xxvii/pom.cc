#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 1e5 + 10;

char A[N], B[N], C[N];
int sum[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%s%s%d", A, B, &m);
    n = strlen(A);
    for (int i = 0; i < n; ++i) {
      sum[i] = A[i] != B[i];
      if (i) sum[i] += sum[i - 1];
    }
    int p = -1;
    for (int i = n - 1; i >= 0 && p == -1; --i) if (B[i] != '0') {
      int e1 = i ? sum[i - 1] : 0, e2 = e1, e3 = e1;
      if (A[i] >= B[i]) ++e1, e2 = m + 1, e3 = m + 1;
      else {
        if (A[i] + 1 != B[i]) ++e2, e3 = m + 1;
        else {
          e2 = m + 1;
          if (A[i] != '0') ++e3;
          else e3 = m + 1;
        }
      }
      if (e1 <= m && e1 + n - 1 - i >= m) p = i;
      if (e2 <= m && e2 + n - 1 - i >= m) p = i;
      if (e3 <= m && e3 + n - 1 - i >= m) p = i;
    }
    if (p == -1) {
      puts("-1");
      continue;
    }
    for (int i = 0; i < p; ++i) {
      m -= A[i] != B[i];
      C[i] = B[i];
    }
    if (A[p] >= B[p]) {
      --m;
      C[p] = B[p] - 1;
    } else if (A[p] + 1 != B[p] && m - 1 <= n - 1 - p && m) {
      C[p] = B[p] - 1;
      --m;
    } else if (m > n - 1 - p) {
      C[p] = A[p] - 1;
      --m;
    } else {
      C[p] = A[p];
    }
    for (int i = p + 1; i < n; ++i) {
      if (!m) { C[i] = A[i]; continue; }
      if (A[i] != '9') {
        if (m - 1 <= n - 1 - i) C[i] = '9', --m;
        else C[i] = A[i];
      } else {
        if (m <= n - 1 - i) C[i] = '9';
        else C[i] = '8', --m;
      }
    }
    C[n] = 0;
    puts(C);
  }
  return 0;
}
