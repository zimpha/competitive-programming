#include <bits/stdc++.h>

long ans[30000];

long parse(long n) {
  std::vector<int> a;
  while (n) {
    a.push_back(n % 2);
    n /= 2;
  }
  std::reverse(a.begin(), a.end());
  long v = 0, ret = 1;
  for (size_t i = 0; i < a.size(); ++i) {
    if (i + 1 < a.size() && a[i] == 0 && a[i + 1] == 0) {
      if (v) std::cout << v << " ";
      ret = ret * ans[v];
      v = 0;
      continue;
    } else v = v * 2 + a[i];
  }
  ret = ret * ans[v];
  if (v) std::cout << v << " ";
  std::cout << std::endl;
  return ret;
}

int main() {
  const int n = 30000 * 5 + 1;
  int cnt[n];
  ans[0] = 1;
  memset(cnt, 0, sizeof(cnt));
  cnt[0] = 1;
  for (int k = 1; k < 30000; ++k) {
    static int tmp[n];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (i + j < n) {
          tmp[i + j] += cnt[i];
          tmp[i + j] &= 1;
        }
      }
    }
    memcpy(cnt, tmp, sizeof(tmp));
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      ret += cnt[i] & 1;
    }
    ans[k] = ret;
  }
  long p = 10, ret = 0;
  for (int i = 1; i <= 18; ++i) {
    //std::cout << parse(p) << std::endl;
    ret += parse(p);
    p *= 10;
  }
  std::cout << ret << std::endl;
  return 0;
}
