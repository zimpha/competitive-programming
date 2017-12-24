// http://www.spoj.com/problems/BOI7SOU/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 10;

int A[MAXN], Qmax[MAXN], Qmin[MAXN];
int n, m, c;

int main() {
  scanf("%d%d%d", &n, &m, &c);
  for (int i = 0; i < n; ++ i) scanf("%d", A + i);
  int Hmax = 0, Tmax = -1, Hmin = 0, Tmin = -1, cnt = 0;
  for (int i = 0; i + 1 < m && i < n; ++ i) {
    while (Tmax >= Hmax && A[i] <= A[Qmax[Tmax]]) -- Tmax; Qmax[++ Tmax] = i;
    while (Tmin >= Hmin && A[i] >= A[Qmin[Tmin]]) -- Tmin; Qmin[++ Tmin] = i;
  }
  for (int i = m - 1; i < n; ++ i) {
    while (Tmax >= Hmax && A[i] <= A[Qmax[Tmax]]) -- Tmax; Qmax[++ Tmax] = i;
    while (Tmin >= Hmin && A[i] >= A[Qmin[Tmin]]) -- Tmin; Qmin[++ Tmin] = i;
    while (Hmax <= Tmax && Qmax[Hmax] <= i - m) ++ Hmax;
    while (Hmin <= Tmin && Qmin[Hmin] <= i - m) ++ Hmin;
    if (A[Qmin[Hmin]] - A[Qmax[Hmax]] <= c) ++ cnt, printf("%d\n", i - m + 2);
  }
  if (!cnt) puts("NONE");
  return 0;
}
