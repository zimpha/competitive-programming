#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> g(n + 1, 0);
  const int c[] = {1, 2, 5, 10, 20, 50, 100, 200};
  g[0] = 1;
  for (int i = 0; i < 8; ++ i) {
    for (int j = c[i]; j <= n; ++ j) {
      g[j] += g[j - c[i]];
    }
  }
  return g[n];
}

int main() {
  cout << sol(200) << endl;
  return 0;
}
