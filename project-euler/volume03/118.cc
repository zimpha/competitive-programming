#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int val[10], cnt[512];
LL ret = 0;

bool isPrime(int n) {
  if (n < 2) return false;
  if (n <= 3) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void dfs(int dep, int s) {
  if (dep == 9) {
    LL tmp = 1;
    for (int i = 0; i < s; ++i) {
      tmp *= cnt[val[i]];
    }
    ret += tmp;
    return;
  }
  for (int i = 0; i <= s; ++i) {
    val[i] ^= 1 << dep;
    dfs(dep + 1, s + (i == s));
    val[i] ^= 1 << dep;
  }
}

int main() {
  const int p[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int msk = 0; msk < 512; ++msk) {
    vector<int> pt;
    for (int i = 0; i < 9; ++i) {
      if (msk >> i & 1) pt.push_back(p[i]);
    }
    do {
      int val = 0;
      for (auto &x: pt) val = val * 10 + x;
      if (isPrime(val)) ++cnt[msk];
    } while (next_permutation(pt.begin(), pt.end()));
  }
  ret = 0;
  dfs(0, 0);
  cout << ret << endl;
  return 0;
}
