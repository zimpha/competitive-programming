#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> A(n), B(n), idx(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &A[i], &B[i]);
    idx[i] = i;
  }
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
    return B[x] - A[x] < B[y] - A[y];
  });
  std::vector<int> laser;
  for (int i = 0, x; i < m; ++i) {
    scanf("%d", &x);
    while (laser.size() >= 1 && laser.back() == x) laser.pop_back();
    while (laser.size() >= 2 && ((x > laser.back() && laser.back() > laser[laser.size() - 2]) || (x < laser.back() && laser.back() < laser[laser.size() - 2]))) laser.pop_back();
    laser.push_back(x);
  }
  int64 sum = 0;
  std::set<std::pair<int, int>> len;
  std::set<int> pos;
  m = laser.size();
  for (int i = 0; i < m; ++i) pos.insert(i);
  for (int i = 1; i < m; ++i) {
    len.emplace(std::abs(laser[i] - laser[i - 1]), i - 1);
    sum += std::abs(laser[i] - laser[i - 1]);
  }

  auto remove = [&](int x) {
    auto ix = pos.lower_bound(x);
    if (ix == pos.begin()) {
      auto iy = ix; ++iy;
      len.erase(std::make_pair(std::abs(laser[*iy] - laser[*ix]), *ix));
      sum -= std::abs(laser[*iy] - laser[*ix]);
    } else {
      auto iy = ix; --iy;
      len.erase(std::make_pair(std::abs(laser[*ix] - laser[*iy]), *iy));
      sum -= std::abs(laser[*ix] - laser[*iy]);
      auto iz = ix; ++iz;
      if (iz != pos.end()) {
        len.erase(std::make_pair(std::abs(laser[*iz] - laser[*ix]), *ix));
        sum -= std::abs(laser[*iz] - laser[*ix]);
        len.emplace(std::abs(laser[*iz] - laser[*iy]), *iy);
        sum += std::abs(laser[*iz] - laser[*iy]);
      }
    }
    pos.erase(ix);
  };

  std::vector<int64> ret(n);
  for (auto &x: idx) {
    int bound = B[x] - A[x];
    while (len.size() > 1 && len.begin()->first <= bound) {
      int i = len.begin()->second;
      auto it1 = pos.lower_bound(i);
      auto it2 = it1; ++it2;
      auto it3 = it2; ++it3;
      if (it1 == pos.begin()) remove(i);
      else if (it3 == pos.end()) remove(*it2);
      else {
        remove(i); remove(*it2);
      }
    }
    auto first = pos.begin();
    auto second = first; ++second;
    int64 step = 0;
    if (len.size() >= 2) {
      step += sum - static_cast<int64>(bound) * len.size();
      if (laser[*second] > laser[*first]) step += std::abs(A[x] - laser[*first]);
      else step += std::abs(B[x] - laser[*first]);
    } else {
      int l = A[x], r = B[x];
      if (r < laser[*first]) {
        step += laser[*first] - r;
        l += laser[*first] - r;
        r = laser[*first];
      } else if (l > laser[*first]) {
        step += l - laser[*first];
        r -= l - laser[*first];
        l = laser[*first];
      }
      if (second != pos.end()) {
        if (r < laser[*second]) {
          step += laser[*second] - r;
          l += laser[*second] - r;
          r = laser[*second];
        } else if (l > laser[*second]) {
          step += l - laser[*second];
          r -= l - laser[*second];
          l = laser[*second];
        }
      }
    }
    ret[x] = step;
  }
  for (int i = 0; i < n; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}
