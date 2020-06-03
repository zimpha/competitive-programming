#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>

using int64 = long long;

const int N = 1e6 + 10;

char s[N];

int main() {
  int n;
  scanf("%d", &n);
  std::map<int, int> left, right;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    int a = 0, b = 0;
    for (int j = 0; s[j]; ++j) {
      if (s[j] == '(') {
        ++b;
      } else {
        if (b) --b;
        else ++a;
      }
    }
    if (a == 0 && b == 0) ++cnt;
    else if (!a) left[b]++;
    else if (!b) right[a]++;
  }
  int ret = cnt / 2;
  for (auto &&x: left) {
    ret += std::min(x.second, right[x.first]);
  }
  printf("%d\n", ret);
  return 0;
}