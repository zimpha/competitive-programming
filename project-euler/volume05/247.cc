#include <bits/stdc++.h>

struct square_t {
  double x, y, sz;
  int l, b;
  square_t() {}
  square_t(double x, double y, int l, int b): x(x), y(y), l(l), b(b) {}
  void get_size() {
    sz = (sqrt((x - y) * (x - y) + 4) - (x + y)) / 2;
  }
};

int run(int x, int y) {
  double min_size = 1;
  std::stack<square_t> stk;
  stk.push(square_t(1, 0, 0, 0));
  while (!stk.empty()) {
    square_t now = stk.top();
    stk.pop();
    if (now.l > x || now.b > y) continue;
    now.get_size();
    if (now.l == x && now.b == y) {
      min_size = std::min(min_size, now.sz);
    }
    stk.push(square_t(now.x + now.sz, now.y, now.l + 1, now.b));
    stk.push(square_t(now.x, now.y + now.sz, now.l, now.b + 1));
  }
  stk.push(square_t(1, 0, 0, 0));
  int ret = 0;
  while (!stk.empty()) {
    square_t now = stk.top();
    stk.pop();
    now.get_size();
    if (now.sz < min_size) continue;
    ++ret;
    stk.push(square_t(now.x + now.sz, now.y, now.l + 1, now.b));
    stk.push(square_t(now.x, now.y + now.sz, now.l, now.b + 1));
  }
  return ret;
}

int main() {
  assert(run(1, 1) == 50);
  std::cout << run(3, 3) << std::endl;
  return 0;
}
