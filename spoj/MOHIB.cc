#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; scanf("%d", &T);
  for (int _ = 0; _ < T; ++ _) {
    int x, avg; scanf("%d%d", &x, &avg);
    int n = avg - x + 1;
    int sum = n * avg - x;
    if (n <= 2) printf("%d\n", sum);
    else printf("%d\n", sum - (n - 2) * (n - 1) / 2);
  }
  return 0;
}


