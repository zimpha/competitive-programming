#include <cstdio>
#include <cassert>
#include <vector>

using uint64 = unsigned long long;

char s[8][10];
uint64 a[8][8];

const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int check(uint64 state, int mask) {
  int ret = 0;
  for (int i = 0; i < 8; ++i) {
    if (mask >> i & 1) {
      ++ret;
      state ^= a[0][i];
    }
  }
  for (int i = 1; i < 8; ++i) {
    if (mask >> (i + 7) & 1) {
      ++ret;
      state ^= a[i][0];
    }
  }
  for (int i = 1; i < 8; ++i) {
    for (int j = 1; j < 8; ++j) {
      if (state >> ((i - 1) * 8 + j - 1) & 1) {
        ++ret;
        state ^= a[i][j];
      }
    }
  }
  if (state) return -1;
  return ret;
}

void output(uint64 state, int mask) {
  for (int i = 0; i < 8; ++i) {
    if (mask >> i & 1) {
      printf("%d ", i + 1);
      state ^= a[0][i];
    }
  }
  for (int i = 1; i < 8; ++i) {
    if (mask >> (i + 7) & 1) {
      printf("%d ", i * 8 + 1);
      state ^= a[i][0];
    }
  }
  for (int i = 1; i < 8; ++i) {
    for (int j = 1; j < 8; ++j) {
      if (state >> ((i - 1) * 8 + j - 1) & 1) {
        state ^= a[i][j];
        printf("%d ", i * 8 + j + 1);
      }
    }
  }
  puts("");
}

int main() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      a[i][j] = 0;
      for (int k = 0; k < 8; ++k) {
        int x = i + dx[k], y = j + dy[k];
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
          a[i][j] |= 1ull << (x * 8 + y);
        }
      }
    }
  }
  uint64 state = 0;
  for (int i = 0; i < 8; ++i) scanf("%s", s[i]);
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      state |= uint64(s[i][j] == 'B') << (i * 8 + j);
    }
  }
  int ret = -1;
  int tm = 0;
  uint64 ts = 0;
  for (int mask = 0; mask < (1 << 15); ++mask) {
    auto tmp = check(state, mask);
    if (tmp != -1 && (ret == -1 || tmp < ret)) {
      ret = tmp;
      tm = mask;
      ts = state;
    }
    tmp = check(~state, mask);
    if (tmp != -1 && (ret == -1 || tmp < ret)) {
      ret = tmp;
      tm = mask;
      ts = ~state;
    }
  }
  printf("%d\n", ret);
  if (ret) output(ts, tm);
  return 0;
}
