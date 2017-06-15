#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int r, b;
  scanf("%d%d", &r, &b);
  std::vector<char> res;
  int e = std::min(b, r);
  if (e) {
    for (int i = 1; i < e; ++i) {
      res.push_back('E');
      res.push_back('E');
    }
    res.push_back('E');
    b -= e;
    r -= e;
    if (b) {
      res.push_back('E'); res.push_back('W'); --b;
      for (int i = 0; i < e && b; ++i) {
        if (b >= 1) {
          res.push_back('N');
          res.push_back('S');
          --b;
        }
        if (b >= 1) {
          res.push_back('S');
          res.push_back('N');
          --b;
        }
        if (i != e - 1) {
          res.push_back('W');
          res.push_back('W');
        }
      }
    }
    if (r) {
      res.push_back('W');
      for (int i = 0; i < e && r; ++i) {
        if (r >= 1) {
          res.push_back('N');
          res.push_back('S');
          --r;
        }
        if (r >= 1) {
          res.push_back('S');
          res.push_back('N');
          --r;
        }
        if (r) {
          res.push_back('W');
          if (i + 1 != e) {
            res.push_back('W');
          }
        }
      }
    }
  }
  printf("%d\n", (int)res.size());
  for (auto &&c: res) putchar(c);
  puts("");
  return 0;
}
