#include <cstdio>
#include <cassert>
#include <vector>
#include <set>

int main() {
  std::vector<int> sg = {0, 0};
  for (int i = 2; i <= 100; ++i) {
    std::set<int> s;
    s.insert(sg[i - 1]);
    s.insert(sg[(i + 1) / 2]);
    for (int j = 0; j <= 10; ++j) {
      if (!s.count(j)) {
        sg.push_back(j);
        break;
      }
    }
  }
  for (int i = 1; i <= 100; ++i) {
    int ctz = __builtin_ctz(i);
    int cnt = __builtin_popcount(i);
    printf("%d %d\n", i, sg[i]);
    if (ctz % 2) assert(sg[i] == 0);
    else if (cnt % 2) assert(sg[i] == 1);
    else assert(sg[i] == 2);
  }
  return 0;
}
