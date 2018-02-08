#include <cstdio>
#include <vector>
#include <cstring>

const int N = 5000 + 10;

char s[N], t[N];
int a[N];

int main() {
  std::vector<int> x, y;
  scanf("%s%s", s, t);
  int n = strlen(s);
  int m = strlen(t);
  for (int i = 0; i < n; ++i) {
    if (s[i] == '+') x.push_back(i);
    else y.push_back(i);
  }
  for (int i = m - 1; i >= 0; --i) {
    if (t[i] == '+') {
      if (x.empty()) {
        puts("-1");
        return 0;
      }
      a[i] = x.back();
      x.pop_back();
    } else {
      if (y.empty()) {
        puts("-1");
        return 0;
      }
      a[i] = y.back();
      y.pop_back();
    }
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      ret += a[i] > a[j];
    }
  }
  printf("%d\n", ret);
  return 0;
}
