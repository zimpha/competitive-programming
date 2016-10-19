#include <bits/stdc++.h>

using LL = long long;

int vis[100];

bool check(LL val, int n) {
  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j < i; ++j) vis[j] = 0;
    for (LL m = val; m; m /= i) {
      vis[m % i]=1;
    }
    for (int j = 0; j < i; ++j) {
      if (!vis[j]) return false;
    }
  }
  return true;
}

LL run(int cnt) {
  int p[] = {1,0,2,3,4,5,6,7,8,9,10,11};
  LL ret = 0;
  do {
    LL val = 0;
    for (int i = 0; i < 12; ++i) {
      val = val * 12 + p[i];
    }
    if (check(val, 11)) {
      std::cout << val << std::endl;
      ret += val;
      --cnt;
    }
    if (cnt == 0) break;
  } while (std::next_permutation(p, p + 12));
  return ret;
}

int main() {
  std::cout << run(10) << std::endl;
  return 0;
}
