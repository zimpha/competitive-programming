#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

int sol(int n, int m) {
  vector<PII> v(n + 1);
  for (int i = 1; i <= n; ++ i) v[i] = PII(i, 1);
  for (int a = 2; a <= n; ++ a) {
    int p = a;
    for (int k = 2; ; ++ k) {
      p = p * a;
      if (p > n) break;
      v[p] = min(v[p], PII(a, k));
    }
  }
  set<PII> S;
  for (int a = 2; a <= n; ++ a) {
    for (int b = 2; b <= m; ++ b) {
      S.insert(PII(v[a].first, v[a].second * b));
    }
  }
  return S.size();
}

int main() {
  cout << sol(5, 5) << endl;
  cout << sol(100, 100) << endl;
  return 0;
}
