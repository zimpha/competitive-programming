#include <cstdio>
#include <algorithm>

const int N = 200;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d%s", &n, s);
    int ret = 0, cnt = 0;
    for (int i = n - 1; i >= 0; --i) {
      if (s[i] == 'A') ret = std::max(ret, cnt), cnt = 0;
      else cnt++;
    }
    printf("%d\n", ret);
  }
  return 0;
}
