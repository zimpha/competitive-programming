#include <bits/stdc++.h>

using LL = long long;

const int mask[10] = {0b1110111, 0b0010010, 0b1011101, 0b1011011, 0b0111010, 0b1101011, 0b1101111, 0b1110010, 0b1111111, 0b1111011};

int calc(int n) {
  std::vector<std::vector<int>> ds;
  int ret = 0;
  while (n >= 10) {
    std::vector<int> num;
    int sum = 0;
    while (n) {
      sum += n % 10;
      ret += __builtin_popcount(mask[n % 10]);
      num.push_back(n % 10);
      n /= 10;
    }
    n = sum;
    ds.push_back(num);
  }
  ds.push_back({n});
  ret += __builtin_popcount(mask[n]);
  ret *= 2;
  int now[8];
  for (int i = 0; i < 8; ++i) now[i] = 0;
  for (size_t i = 0; i < ds.size(); ++i) {
    for (size_t j = 0; j < ds[i].size(); ++j) {
      now[j] ^= mask[ds[i][j]];
      ret -= __builtin_popcount(now[j]);
      now[j] = mask[ds[i][j]];
    }
    if (i + 1 < ds.size()) {
      for (size_t j = 0; j < ds[i].size(); ++j) {
        int next = 0;
        if (j < ds[i + 1].size()) next = mask[ds[i + 1][j]];
        int val = now[j] & next;
        ret -= __builtin_popcount(now[j] ^ val);
        now[j] = val;
      }
    }
  }
  for (int j = 0; j < 8; ++j) ret -= __builtin_popcount(now[j]);
  return ret;
}

int run(int A, int B) {
  std::vector<bool> mark(B, 1);
  mark[0] = mark[1] = 0;
  for (int i = 2; i < B; ++i) if (mark[i]) {
    for (int j = i * 2; j < B; j += i) mark[j] = 0;
  }
  int ret = 0;
  for (int n = A; n <= B; ++n) if (mark[n]) {
    ret += calc(n);
  }
  return ret;
};

int main() {
  std::cout << calc(11) << std::endl;
  std::cout << calc(137) << std::endl;
  std::cout << run(10000000, 20000000) << std::endl;
  return 0;
}

