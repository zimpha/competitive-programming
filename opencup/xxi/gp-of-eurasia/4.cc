#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue>

const int N = 1 << 24, M = 1 << 10;

uint8_t cell[N], from[N];
int value[M];

bool update(int &x, int y) {
  if (x == -1 || x > y) {
    x = y;
    return true;
  } else {
    return false;
  }
}

int& at(int p) {
  return value[(p + M) % M];
}

int main() {
  int n = fread(cell, sizeof(uint8_t), N, stdin);
  memset(value, -1, sizeof(value));
  at(-1) = 0;
  std::deque<int> queue;
  for (int i = 0; i < n; ++i) {
    // 1. right not change
    if (i - cell[i] - 1 >= 0 && at(i - cell[i] - 2) != -1) {
      int diff = cell[i] != cell[i - cell[i] - 1];
      if (update(at(i), at(i - cell[i] - 2) + diff)) {
        from[i] = cell[i];
      }
    }
    // 2. left not change
    if (i + cell[i] + 1 < n && at(i - 1) != -1) {
      int diff = cell[i] != cell[i + cell[i] + 1];
      if (update(at(i + cell[i] + 1), at(i - 1) + diff)) {
        from[i + cell[i] + 1] = cell[i];
      }
    }
    // 3. both change
    while (!queue.empty() && queue.front() < i - 257) queue.pop_front();
    if (i >= 2) {
      if (update(at(i), at(queue.front()) + 2)) {
        from[i] = i - queue.front() - 2;
      }
    }
    if (at(i - 1) != -1) {
      while (!queue.empty() && at(i - 1) <= at(queue.back())) {
        queue.pop_back();
      }
      queue.push_back(i - 1);
    }
    at(i - 300) = -1;
  }

  auto print = [] (uint32_t i, uint32_t v) {
    uint32_t w = i + (v << 24);
    fwrite(&w, 1, 4, stdout);
  };

  for (int i = n - 1; i >= 0; i -= (int)from[i] + 2) {
    if (cell[i] != from[i]) print(i, from[i]);
    if (cell[i - from[i] - 1] != from[i]) print(i - from[i] - 1, from[i]);
  }
  return 0;
}
