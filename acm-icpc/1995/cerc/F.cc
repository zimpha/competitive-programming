#include <cstdio>
#include <cstring>

const int MAXN=20;

int hash[MAXN];
int n;

bool check(int n, int m) {
  int rest = n * 2;
  int out = 0;
  while (rest > n) {
    out = (out + m - 1) % rest;
    if (out < n) return false;
    rest--;
  }
  return true;
}

int main() {
  memset(hash, 0, sizeof(hash));
  while (scanf("%d", &n) == 1 && n) {
    if (hash[n]) printf("%d\n", hash[n]);
    else {
      for (int i = n + 1; ; i += n + 1) {
        if (check(n, i)) {
          hash[n] = i;
          break;
        }
        if (check(n, i + 1)) {
          hash[n] = i + 1;
          break;
        }
      }
      printf("%d\n", hash[n]);
    }
  }
  return 0;
}
