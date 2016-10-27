//A255938
#include <bits/stdc++.h>

const int N = 1001, M = 10000;

bool grid[N][N];

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
int cnt[M + 1];

void prepare() {
  int x = 500, y = 500, d = 0, r = 0;
  for (int i = 1; i <= M; ++i) {
    if (grid[x][y]) d = (d + 3) % 4;
    else d = (d + 1) % 4;
    r -= grid[x][y];
    grid[x][y] ^= 1;
    r += grid[x][y];
    x += dx[d], y += dy[d];
    cnt[i] = r;
  }
}

long run(long n) {
  if (n <= M) return cnt[n];
  long k = (n - M) / 104;
  n -= k * 104;
  long ret = 12 * k;
  while (n > M) ret += 12, n -= 104;
  return ret + cnt[n];
}

int main() {
  prepare();
  std::cout << run(1000000000000000000ll) << std::endl;
  return 0;
}
