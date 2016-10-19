#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<LL> hn;

void dfs(int n, LL s, int ds) {
  hn.push_back(s);
  if (n == 13) return;
  for (int d = n == 0; d < 10; ++d) {
    LL x = s * 10 + d;
    if (x % (ds + d) == 0) dfs(n + 1, x, ds + d);
  }
}

bool isPrime(LL n) {
  if (n < 2) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0) return 0;
  for (LL i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int digitSum(LL n) {
  int r = 0;
  while (n) r += n % 10, n /= 10;
  return r;
}

LL gen(LL n) {
  if (!n) return 0;
  int ds = digitSum(n);
  if (!isPrime(n / ds)) return 0;
  LL ret = 0;
  for (int d = 1; d < 10; d += 2) {
    if (isPrime(n * 10 + d)) ret += n * 10 + d;
  }
  return ret;
}

int main() {
  dfs(0, 0, 0);
  sort(hn.begin(), hn.end());
  cout << hn.size() << endl;
  LL ret = 0;
  for (size_t i = 0; i < hn.size(); ++i) {
    ret += gen(hn[i]);
  }
  cout << ret << endl;
  return 0;
}
