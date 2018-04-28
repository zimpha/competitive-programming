#include <cstdio>
#include <vector>

const int N = 500000 + 10;
char s[N];

int main() {
  int n;
  scanf("%d", &n);
  scanf("%s", s);
  for (int l = 1; l <= 20; ++l) {
    std::vector<bool> mark(1 << l);
    int v = 0;
    for (int i = 0; i < l - 1; ++i) {
      v = (v << 1) | (s[i] == 'b');
    }
    int mask = (1 << l) - 1;
    for (int i = l - 1; i < n; ++i) {
      v = ((v << 1) | (s[i] == 'b')) & mask;
      mark[v] = 1;
    }
    bool find = false;
    for (int i = 0; i < (1 << l) && !find; ++i) if (!mark[i]) {
      find = true;
      printf("%d\n", l);
      for (int j = 0; j < l; ++j) {
        putchar('a' + (i >> (l - j - 1) & 1));
      }
      puts("");
    }
    if (find) break;
  }
  return 0;
}
