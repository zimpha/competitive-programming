#include <cstdio>

const int N = 1e5 + 10;

char s[N];

int main() {
  int n;
  scanf("%d%s", &n, s);
  int cl = 0, cr = 0;
  for (int i = 0; i < n; ++i) {
    cl += s[i] == 'L';
    cr += s[i] == 'R';
  }
  printf("%d\n", cl + cr + 1);
  return 0;
}
