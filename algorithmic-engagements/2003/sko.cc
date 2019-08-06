#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

struct ring {
  int64 x, y;
  ring(int64 x = 0, int64 y = 0): x(x), y(y) {}
  int64 norm() const {
    return std::abs(x) + std::abs(y);
  }
  ring operator + (const ring& rhs) const {
    return ring(x + rhs.x, y + rhs.y);
  }
  ring operator - (const ring& rhs) const {
    return ring(x - rhs.x, y - rhs.y);
  }
  ring operator * (const int64 k) const {
    return ring(x * k, y * k);
  }
};

int main() {
  ring a, b;  
  scanf("%lld%lld%lld%lld", &a.x, &a.y, &b.x, &b.y);
  while (a.norm()) {
    if (a.norm() < b.norm()) std::swap(a, b);
    // find r such that |a - rb| is minimum
    std::vector<int64> candidate;
    if (b.x != 0) candidate.push_back(a.x / b.x);
    if (b.y != 0) candidate.push_back(a.y / b.y);
    int64 best_r = 0, best = - 1;
    for (auto &r: candidate) {
      for (int i = -2; i <= 2; ++i) {
        int64 now = (a - b * (r + i)).norm();
        if (best == -1 || best > now) best = now, best_r = r + i;
      }
    }
    if (best < b.norm()) {
      auto c = a - b * best_r;
      a = b;
      b = c;
    } else {
      break;
    } 
  }
  printf("%lld\n", b.norm());
  return 0;
}
