#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    if (n == 1) puts("1 1 1 2");
    else if (n == 2) {
      puts("1 1 1 2");
      puts("1 3 1 4");
      puts("1 5 1 6");
    } else if (n == 3) {
      puts("1 1 2 1");
      puts("1 2 1 3");
      puts("2 2 2 3");
      puts("1 4 1 5");
      puts("2 5 2 4");
      puts("3 3 3 4");
    } else if (n == 4) {
      puts("1 1 2 1"); 
      puts("1 2 2 2");
      puts("3 1 4 1");
      puts("1 3 1 4");
      puts("3 2 3 3");
      puts("4 3 5 3");
      puts("2 3 2 4");
      puts("4 2 5 2");
      puts("5 4 4 4");
      puts("3 4 3 5");
    } else {
      puts("impossible");
    }
  }
  return 0;
}
