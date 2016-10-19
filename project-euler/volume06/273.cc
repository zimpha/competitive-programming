#include <bits/stdc++.h>

typedef std::pair<__int128, __int128> num_t;

bool is_prime(int n) {
  if (n < 2) return false;
  if (n < 4) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

num_t square(int n) {
  for (int a = 1; a < n; ++a) {
    for (int b = a + 1; b < n; ++b) {
      if (a * a + b * b == n) return {a, b};
    }
  }
  return {-1, -1};
}

__int128 abs(__int128 x) {
  if (x < 0) return -x;
  else return x;
}

std::vector<num_t> build(auto l, auto r) {
  std::vector<num_t> f, g;
  for (; l < r; ++l) {
    __int128 a = l->first, b = l->second;
    g = f;
    f.push_back({a, b});
    for (auto &&e: g) {
      __int128 c = e.first, d = e.second;
      __int128 u = abs(b * d - a * c), v = a * d + b * c;
      if (u > v) std::swap(u, v);
      f.push_back({u, v});
      u = abs(a * d - b * c), v = a * c + b * d;
      if (u > v) std::swap(u, v);
      f.push_back({u, v});
    }
  }
  return f;
}

long run(int n) {
  std::vector<num_t> sq;
  for (int i = 1; i < n; ++i) {
    if (is_prime(i) && i % 4 == 1) {
      sq.push_back(square(i));
      assert(sq.back().first != -1);
    }
  }
  auto s = build(sq.begin(), sq.end());
  long ret = 0;
  for (auto &&e: s) ret += e.first;
  return ret;
}

int main() {
  std::cout << run(150) << std::endl;
  return 0;
}
