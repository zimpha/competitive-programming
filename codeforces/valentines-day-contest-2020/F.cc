#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <set>

const int N = 200000 + 10;
const std::string love = "LOVE";

char s[N];
int op;

int main() {
  scanf("%s%d", s, &op);
  int n = strlen(s);
  std::set<int> good, need;

  auto check = [&](int x, bool ins = false) {
    if (x + love.size() - 1 >= n) return -1;
    int cnt = 0, pos = -1;;
    for (size_t i = 0; i < love.size(); ++i) {
      if (s[x + i] == '?') {
        ++cnt; pos = x + i;
      } else if (love[i] != s[x + i]) return -1;
    }
    if (cnt == 1 && ins) good.insert(pos);
    return cnt;
  };

  for (int i = 0; i < n; ++i) {
    check(i, true);
    if (s[i] == '?') need.insert(i);
  }

  auto place = [&] (int x) {
    if (op == 1) {
      for (int i = 0; i < (int)love.size() && i <= x && s[x] == '?'; ++i) {
        if (check(x - i) == 1) s[x] = love[i];
      }
      if (s[x] == '?') s[x] = love[0];
    } else {
      for (int i = 0; i < love.size(); ++i) {
        s[x] = love[i];
        if (x >= i && (check(x - i) == 1 || check(x - i) == 0)) continue;
        break;
      }
    }
    printf("%d %c\n", x + 1, s[x]);
    fflush(stdout);
    for (int i = 0; i < (int)love.size() && i <= x; ++i) {
      check(x - i, true);
    }
  };

  for (int now = 1; !need.empty(); now ^= 3) {
    if (op != now) {
      int x;
      char c;
      scanf("%d %c", &x, &c);
      --x;
      s[x] = c;
      need.erase(x); good.erase(x);
      for (int i = 0; i < (int)love.size() && i <= x; ++i) {
        check(x - i, true);
      }
    } else {
      int u = *need.begin();
      if (!good.empty()) u = *good.begin();
      need.erase(u); good.erase(u);
      place(u);
    }
  }
  return 0;
}
