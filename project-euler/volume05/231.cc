#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 20000001;
int p[N], s;

LL run(int n, int m) {
  for (int i = 0; i <= n; ++i) p[i] = 0; s = 0;
  for (int i = 2; i <= n; ++i) if (!p[i]) {
    p[s++] = i;
    for (int j = i; j <= n; j += i) p[j] = 1;
  }
  vector<int> cnt(s, 0);
  for (int i = 0; i < s; ++i) {
    for (LL x = p[i]; n / x; x *= p[i]) cnt[i] += n / x;
  }
  for (int i = 0; i < s; ++i) {
    for (LL x = p[i]; m / x; x *= p[i]) cnt[i] -= m / x;
  }
  for (int i = 0; i < s; ++i) {
    for (LL x = p[i]; (n - m) / x; x *= p[i]) cnt[i] -= (n - m) / x;
  }
  LL ret = 0;
  for (int i = 0; i < s; ++i) ret += 1ll * cnt[i] * p[i];
  return ret;
}

int main() {
  cout << run(10, 3) << endl;
  cout << run(20000000, 15000000) << endl;
  return 0;
}
