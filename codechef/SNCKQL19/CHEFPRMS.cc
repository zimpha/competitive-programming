#include <cstdio>

bool is_prime(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

bool is_semi(int n) {
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0 && i * i != n) {
      if (is_prime(i) && is_prime(n / i)) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    bool find = false;
    for (int x = 2; x < n && !find; ++x) {
      if (is_semi(x) && is_semi(n - x)) {
        find = true;
      }
    }
    if (find) puts("YES");
    else puts("NO");
  }
  return 0;
}
