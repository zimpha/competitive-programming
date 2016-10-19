// n = p(p + d)(p + (p^2+1)/d), d | p^2 + 1
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, int> PII;

vector<LL> factor(LL n) {
  vector<PII> pl;
  for (int i = 2; 1ll * i * i <= n; ++i) if (n % i == 0) {
    PII nw = PII(i, 0);
    while (n % i == 0) nw.second++, n /= i;
    pl.push_back(nw);
  }
  if (n > 1) pl.push_back(PII(n, 1));
  vector<LL> d; d.push_back(1);
  for (size_t i = 0; i < pl.size(); ++i) {
    int s = d.size();
    for (int j = 0; j < s; ++j) {
      LL p = 1;
      for (int k = 0; k < pl[i].second; ++k) {
        p *= pl[i].first;
        d.push_back(d[j] * p);
      }
    }
  }
  return d;
}

LL run(int n) {
  vector<__int128> Alex;
  for (int p = 1; Alex.size() < 10 * n; ++p) {
    LL s = 1ll * p * p + 1;
    vector<LL> fac = factor(s);
    for (auto d: fac) if (d * d <= s) {
      Alex.push_back((__int128)p * (p + d) * (p + s / d));
    }
  }
  sort(Alex.begin(), Alex.end());
  return (LL)Alex[n - 1];
}

int main() {
  cout << run(6) << endl;
  cout << run(150000) << endl;
  return 0;
}
