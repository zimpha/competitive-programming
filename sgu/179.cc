#include <cstdio>
#include <vector>
#include <cstring>

const int N = 100000;

char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  std::vector<int> cnt(n);
  int p = -1;
  for (int i = 0; i < n; ++i) {
    cnt[i] = i ? cnt[i - 1] : 0;
    if (s[i] == '(') ++cnt[i];
    else --cnt[i];
    if (s[i] == '(') p = i;
  }
  if (p != n - 2) {
    std::swap(s[p], s[p + 1]);
    puts(s);
  } else {
    int q = -1;
    for (int i = p - 1; i >= 1; --i) {
      if (s[i] == ')' && s[i - 1] == '(' && cnt[i - 1] > 1) {
        q = i;
        break;
      }
    }
    if (q == -1) puts("No solution");
    else {
      int need = cnt[q - 2];
      std::swap(s[q], s[q - 1]);
      for (int i = q + 1; i < n; ++i) s[i] = '(';
      for (int i = 0; i < (n - q + need) / 2; ++i) {
        s[n - 1 - i] = ')';
      }
      puts(s);
    }
  }
  return 0;
}
