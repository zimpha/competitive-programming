#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

const int N = 1e5 + 10;

std::map<int, int> boxes[N];
std::vector<std::pair<int, int>> col[N];

int main() {
  int n;
  scanf("%d", &n);
  int ret = 0;
  for (int i = 0, m; i < n; ++i) {
    std::map<int, int> cnt;
    scanf("%d", &m);
    ret += m;
    for (int j = 0, x; j < m; ++j) {
      scanf("%d", &x);
      cnt[x]++;
    }
    for (auto &e: cnt) {
      col[e.first].emplace_back(cnt.size(), i);
    }
    boxes[i] = cnt;
  }
  for (int i = 0; i < N; ++i) {
    std::sort(col[i].begin(), col[i].end());
  }
  for (int i = 0; i < n; ++i) {
    int extra = 0;
    std::vector<int> rest;
    for (auto &e: boxes[i]) {
      if (e.second >= 2) {
        ret = std::min<int>(ret, boxes[i].size() + 1);
      }
      if (col[e.first].size() == 1) {
        ++extra;
      } else {
        if (col[e.first][0].second == i) rest.push_back(col[e.first][1].first);
        else rest.push_back(col[e.first][0].first);
      }
    }
    std::sort(rest.begin(), rest.end(), std::greater<int>());
    for (size_t j = 0; j < rest.size(); ++j) {
      ret = std::min<int>(ret, extra + rest[j] + j + 1);
    }
  }
  printf("%d\n", ret);
  return 0;
}
