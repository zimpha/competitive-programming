#include <cstdio>
#include <algorithm>

int main() {
  int a[4];
  for (int i = 0; i < 4; ++i) scanf("%d", a + i);
  std::sort(a, a + 4);
  if (a[0] + a[1] + a[2] > a[3]) {
    do {
      if (a[0] + a[2] == a[1] + a[3]) {
        puts("Yes");
        return 0;
      }
    } while (std::next_permutation(a, a + 4));
    puts("No");
  } else {
    puts("No");
  }
  return 0;
}
