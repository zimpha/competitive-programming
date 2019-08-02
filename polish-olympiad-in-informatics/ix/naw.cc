#include <cstdio>
#include <vector>

const int mod = 1e9;

int main() {
  int n;
  scanf("%d", &n);
  --n;
  std::vector<char> s(n);
  for (int i = 0; i < n; ++i) {
    scanf(" %c", &s[i]);
  }
  if (s[0] == '+') {
    puts("0");
    return 0;
  }
  std::vector<int> f(n);
  f[0] = 1;
  for (int i = 1; i < n; ++i) {
    std::vector<int> g(n);
    for (int j = i - 1; j >= 0; --j) {
      if (s[i] == '-' && j % 2 == 1) g[j + 1] = f[j];
      else if (s[i] == '+' && j % 2 == 0) g[j + 1] = f[j];
      f[j] = (f[j + 1] + f[j]) % mod;
    }
    for (int j = 0; j < i; ++j) {
      if (s[i] == '-' && j % 2 == 0) g[j] = (g[j] + f[j]) % mod;
      else if (s[i] == '+' && j % 2 == 1) g[j] = (g[j] + f[j]) % mod;
    }
    f.swap(g);
    //for (int j = 0; j <= i; ++j) printf("%d ", f[j]);
    //puts("");
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = (ret + f[i]) % mod;
  }
  printf("%d\n", ret);
  return 0;
}
