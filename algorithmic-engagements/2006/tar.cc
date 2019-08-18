#include <cstdio>
#include <vector>
#include <utility>

const int N = 2e6 + 10;

char farm[N];

int main() {
  int n;
  scanf("%d%s", &n, farm);
  std::vector<int> s, idx(n * 2);
  std::vector<std::pair<int, int>> ret;
  for (int i = 0, x = 0, y = 0; i < n * 2; ++i) {
    if (farm[i] == 'g') idx[i] = ++x;
    else idx[i] = ++y;
    if (!s.empty() && farm[s.back()] != farm[i]) {
      ret.emplace_back(s.back(), i);
      s.pop_back();
    } else {
      s.push_back(i);
    }
  }
  if (!s.empty()) puts("NIE");
  else {
    for (auto &e: ret) {
      int x = e.first, y = e.second;
      if (farm[x] == 't') std::swap(x, y);
      printf("%d %d\n", idx[x], idx[y]);
    }
  }
  return 0;
}
