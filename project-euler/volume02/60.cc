#include <bits/stdc++.h>
using namespace std;

vector<int> vs;
vector<int> pl;

int p[5], ret;

bool isPrime(int n) {
  if (n % 2 == 0) return 0;
  for (int i = 3; i * i <= n; ++ i) {
    if (n % i == 0) return 0;
  }
  return 1;
}

bool check(int a, int b) {
  int x = a, y = b;
  for (int n = a; n; n /= 10) y *= 10;
  for (int n = b; n; n /= 10) x *= 10;
  x += b; y += a;
  return isPrime(x) && isPrime(y);
}

void dfs(int c, int d, int s) {
  if (s >= ret) return;
  if (d == 5) {
    cout << s << endl;
    ret = s;
    return;
  }
  for (size_t i = c; i < pl.size(); ++ i) {
    if (s + pl[i] * (5 - d) >= ret) return;
    p[d] = pl[i];
    bool ok(1);
    for (int j = 0; j < d; ++ j) {
      ok &= check(p[j], pl[i]);
    }
    if (ok) dfs(i + 1, d + 1, s + pl[i]);
  }
}

int main() {
  int n = 10000;
  vs.resize(n, 1); vs[0] = vs[1] = 0;
  for (int i = 2; i < n; ++ i) if (vs[i]) {
    pl.push_back(i);
    for (int j = i + i; j < n; j += i) vs[j] = 0;
  }
  ret = 1e9;
  dfs(0, 0, 0);
  cout << ret << endl;
  return 0;
}
