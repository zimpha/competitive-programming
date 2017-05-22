#include <bits/stdc++.h>

struct state_t {
  int write[2];
  int move[2];
  int next[2];
} state[7];

bool tape[10000000];

int main() {
  state[1] = (state_t){1, 1, -1, -1, 2, 1};
  state[2] = (state_t){1, 1, +1, +1, 3, 2};
  state[3] = (state_t){0, 1, +1, +1, 6, 4};
  state[4] = (state_t){1, 0, -1, +1, 1, 5};
  state[5] = (state_t){0, 1, -1, +1, 1, 3};
  state[6] = (state_t){1, 1, -1, -1, 5, 0};
  int p = 5000000, s = 1;
  long cnt = 0;
  for (long i = 0; ; ++i) {
    int v = tape[p];
    cnt -= v;
    tape[p] = state[s].write[v];
    cnt += state[s].write[v];
    p += state[s].move[v];
    s = state[s].next[v];
    if (cnt == 100000) {
      std::cout << i + 1 << std::endl;
      break;
    }
  }
  return 0;
}
