#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

std::vector<int> kmp(int n, char *s) {
  std::vector<int> fail(n, -1);
  for (int i = 1, j = -1; i < n; ++i) {
    while (j >= 0 && s[j + 1] != s[i]) j = fail[j];
    fail[i] = s[j + 1] == s[i] ? ++j : j;
  }
  return fail;
}

const int N = 5e5 + 10;

char s[N];

bool valid(int n, int b) {
  int p = n - b;
  return p == n || n % p;
}

int main() {
  scanf("%s", s);
  int n = strlen(s);
  auto u = kmp(n, s);
  if (valid(n, u[n - 1] + 1)) {
    puts("1\n1");
    return 0;
  }
  if (u[n - 1] == n - 2) {
    printf("%d\n1\n", n);
    return 0;
  }
  std::reverse(s, s + n);
  auto v = kmp(n, s);
  int ret = 0;
  for (int i = 0; i + 1 < n; ++i) {
    ret += valid(i + 1, u[i] + 1) && valid(n - 1 - i, v[n - 1 - i - 1] + 1);
  }
  printf("2\n%d\n", ret);
  return 0;
}
