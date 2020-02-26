#include "gdzlib.h"
#include <random>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

bool is_distinct(std::vector<std::pair<int, int>> &u){
  std::sort(u.begin(), u.end());
  for (size_t i = 1; i < u.size(); ++i) {
    if (u[i].first == u[i - 1].first) return false;
  }
  return true;
}

int main() {
  while (true) {
    int n = GetN();
    if (n == -1) break;
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[i] = i;
    std::vector<int> one;
    while (pos.size() > 2) {
      std::vector<std::pair<int, int>> val;
      for (size_t i = 1; i < pos.size(); ++i) {
        val.emplace_back(Ask(pos[0], pos[i]), pos[i]);
      }
      bool distinct = is_distinct(val);
      int mx = val.back().first;
      if (mx == 1) {
        Answer(pos[0]);
        pos = {};
      } else if (pos.size() == n && distinct) {
        int u = pos[0];
        pos = {u};
      } else {
        std::vector<int> tmp, tmp2;
        for (auto &e: val) {
          if (e.first == mx) tmp.push_back(e.second);
          else if (e.first == 1) tmp2.push_back(e.second);
        }
        if (one.empty()) one = tmp2;
        if (tmp.size() == 1) tmp.push_back(pos[0]);
        pos = tmp;
      }
    }
    if (pos.size() == 1) {
      for (int i = 0; i < n; ++i) if (pos[0] != i) {
        int g = Ask(pos[0], i);
        if (g == 1) {
          Answer(i);
          break;
        }
      }
    } else if (pos.size() == 2) {
      int a = pos[0], b = pos[1];
      for (auto &x: one) {
        int g = Ask(x, a);
        if (g == 1) {
          if (a != pos[0] || Ask(b, x) == 1) { Answer(x); break; }
          else std::swap(a, b);
        }
      }
    }
  }
  return 0;
}
