#include <bits/stdc++.h>
using LL = long long;

const LL guess[22][2] = {
  5616185650518293ll, 2,
  3847439647293047ll, 1,
  5855462940810587ll, 3,
  9742855507068353ll, 3,
  4296849643607543ll, 3,
  3174248439465858ll, 1,
  4513559094146117ll, 2,
  7890971548908067ll, 3,
  8157356344118483ll, 1,
  2615250744386899ll, 2,
  8690095851526254ll, 3,
  6375711915077050ll, 1,
  6913859173121360ll, 1,
  6442889055042768ll, 2,
  2321386104303845ll, 0,
  2326509471271448ll, 2,
  5251583379644322ll, 2,
  1748270476758276ll, 3,
  4895722652190306ll, 1,
  3041631117224635ll, 3,
  1841236454324589ll, 3,
  2659862637316867ll, 2,
};

bool check_high(int n) {
  for (int i = 0; i < 22; ++i) {
    int v = guess[i][0] / 100000000, c = 0;
    for (int j = 0, u = n; j < 8; ++j) {
      if (u % 10 == v % 10) ++c;
      u /= 10, v /= 10;
      if (c > guess[i][1]) return false;
    }
    if (guess[i][1] > 1 && c < 1) return false;
  }
  return true;
}

bool check_low(int n) {
  for (int i = 0; i < 22; ++i) {
    int v = guess[i][0] % 100000000, c = 0;
    for (int j = 0, u = n; j < 8; ++j) {
      if (u % 10 == v % 10) ++c;
      u /= 10, v /= 10;
      if (c > guess[i][1]) return false;
    }
    if (guess[i][1] > 1 && c == guess[i][1]) return false;
  }
  return true;
}

bool check(LL n) {
  for (int i = 0; i < 22; ++i) {
    LL v = guess[i][0], c = guess[i][1];
    for (LL j = 0, u = n; j < 16; ++j) {
      if (u % 10 == v % 10) --c;
      u /= 10, v /= 10;
    }
    if (c != 0) return false;
  }
  return true;
}

void run() {
  std::vector<int> high, low;
  for (int i = 0; i < 100000000; ++i) {
    if (check_high(i)) high.push_back(i);
    if (check_low(i)) low.push_back(i);
  }
  std::cout << high.size() << " " << low.size() << std::endl;
  for (auto &a: high) for (auto &b: low) {
    if (check(a * 100000000ll + b)) {
      std::cout << a * 100000000ll + b << std::endl;
    }
  }
}

int main() {
  run();
  return 0;
}
