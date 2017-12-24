#include <cstdio>

using uint64 = unsigned long long;

const int N = 20001, M = 313;

uint64 bit[N][M];

int main() {
  int Q;
  scanf("%d", &Q);
  while (Q--) {
    char op;
    int x, y;
    scanf(" %c%d%d", &op, &x, &y);
    if (op == '+') bit[x][y >> 6] ^= uint64(1) << (y & 63);
    else if (op == '-') bit[x][y >> 6] ^= uint64(1) << (y & 63);
    else if (op == 'v') {
      int ret = 0;
      for (int i = 0; i < M; ++i) {
        ret += __builtin_popcountll(bit[x][i] | bit[y][i]);
      }
      printf("%d\n", ret);
    } else if (op == '^') {
      int ret = 0;
      for (int i = 0; i < M; ++i) {
        ret += __builtin_popcountll(bit[x][i] & bit[y][i]);
      }
      printf("%d\n", ret);
    } else if (op == '!') {
      int a = 0, b = 0;
      for (int i = 0; i < M; ++i) {
        a += __builtin_popcountll(bit[x][i] | bit[y][i]);
        b += __builtin_popcountll(bit[x][i] & bit[y][i]);
      }
      printf("%d\n", a - b);
    } else if (op == '\\') {
      int ret = 0;
      for (int i = 0; i < M; ++i) {
        ret += __builtin_popcountll((bit[x][i] ^ bit[y][i]) & bit[x][i]);
      }
      printf("%d\n", ret);
    }
  }
  return 0;
}
