#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin >> T;
  for (int cas = 1; cas <= T; ++ cas) {
    int n; cin >> n;
    if (n == 1) puts("1");
    else printf("%lld\n", 6ll * n * n - 12ll * n + 8);
  }
  return 0;
}
