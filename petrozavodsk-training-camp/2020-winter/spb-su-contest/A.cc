#include <cstdio>
#include <cstring>

const int N = 3000 + 10;

char s[N * 2], t[N * 2];

int main() {
  static char run[20];
  scanf("%s", run);
  if (run[0] == 'p') {
    int n, k = 0;
    scanf("%d%s", &n, s);
    int sum = 0, cu = 0;
    int best = n * 2, best_u = 0;
    s[n * 2] = 'U';
    for (int i = 0; i <= n * 2; ++i) {
      if (s[i] == 'R') ++sum;
      else --sum, ++cu;
      if (sum < best) best = sum, best_u = cu, k = i + 1;
    }
    for (int i = 0; i < n * 2; ++i) {
      t[i] = s[(k + i) % (n * 2 + 1)];
      if (t[i] == 'R') t[i] = '(';
      else t[i] = ')';
    }
    t[n * 2] = 0;
    printf("%s\n%d\n", t, best_u - 1);
  } else {
    int n, k;
    scanf("%d%s%d", &n, s + 1, &k);
    int cu = 0;
    s[0] = ')';
    for (int i = 0; i <= n * 2; ++i) {
      if (s[i] == ')') {
        ++cu;
        if (cu + k == n + 1) {
          k = i + 1;
          break;
        }
      }
    }
    for (int i = 0; i < n * 2; ++i) {
      t[i] = s[(k + i) % (2 * n + 1)];
      if (t[i] == '(') t[i] = 'R';
      else t[i] = 'U';
    }
    t[n * 2] = 0;
    puts(t);
  }
  return 0;
}
