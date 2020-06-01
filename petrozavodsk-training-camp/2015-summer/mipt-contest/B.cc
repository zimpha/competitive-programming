#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {
  srand(time(NULL));
  int n;
  scanf("%d", &n);
  while (true) {
    for (int len = 1; len <= n; len <<= 1) {
      std::vector<int> mark(n);
      for (int i = n - len; i < n; ++i) {
        int p = rand() % i;
        if (mark[p]) mark[i] = 1;
        else mark[p] = 1;
      }
      for (int i = 0; i < n; ++i) putchar('0' + mark[i]);
      puts("");
      fflush(stdout);
      static char res[10];
      scanf("%s", res);
      if (res[0] == '+') return 0;
    }
  }
  return 0;
}
