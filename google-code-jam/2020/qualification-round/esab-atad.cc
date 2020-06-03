#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

int main() {
  int T, B;
  scanf("%d%d", &T, &B);
  for (int cas = 1; cas <= T; ++cas) {
    std::vector<int> a(B, -1);

    auto ask = [&](int x) {
      assert(0 <= x && x < B);
      printf("%d\n", x + 1);
      fflush(stdout);
      int y;
      scanf("%d", &y);
      return y;
    };
    
    auto query = [&](int x) {
      assert(0 <= x && x < B);
      printf("%d\n", x + 1);
      fflush(stdout);
      int y;
      scanf("%d", &y);
      a[x] = y;
    };

    auto change = [&]() {
      int x1 = -1, x2 = -1;
      for (int i = 0; i < B; ++i) if (a[i] != -1) {
        if (x1 == -1 && a[i] == a[B - 1 - i]) x1 = i;
        if (x2 == -1 && a[i] != a[B - 1 - i]) x2 = i;
      }
      if (x2 == -1) {
        int a1 = ask(x1);
        if (a1 != a[x1]) {
          for (int i = 0; i < B; ++i) {
            if (a[i] != -1) a[i] ^= 1;
          }
        }
        ask(x1);
      } else if (x1 == -1) {
        int a2 = ask(x2);
        if (a2 != a[x2]) {
          for (int i = 0; i < B; ++i) {
            if (a[i] != -1) a[i] ^= 1;
          }
        }
        ask(x2);
      } else {
        int a1 = ask(x1), a2 = ask(x2);
        if (a1 != a[x1]) {
          if (a2 == a[x2]) std::reverse(a.begin(), a.end());
          for (int i = 0; i < B; ++i) {
            if (a[i] != -1) a[i] ^= 1;
          }
        } else {
          if (a2 != a[x2]) std::reverse(a.begin(), a.end());
        }
      }
    };

    for (int it = 0; ; ++it) {
      bool found = false;
      for (int i = 0; i < B; ++i) {
        assert(-1 <= a[i] && a[i] <= 1);
        found |= a[i] == -1;
      }
      if (!found) break;
      if (it == 0) {
        for (int x = 0; x < 5; ++x) {
          for (int i = 0; i < B; ++i) if (a[i] == -1) {
            query(i);
            query(B - 1 - i);
            break;
          }
        }
      } else {
        change();
        for (int x = 1; x < 5; ++x) {
          for (int i = 0; i < B; ++i) if (a[i] == -1) {
            query(i);
            query(B - 1 - i);
            break;
          }
        }
      }
    }
    for (int i = 0; i < B; ++i) putchar('0' + a[i]);
    puts("");
    fflush(stdout);
    char token[100];
    scanf("%s", token);
  }
  return 0;
}
