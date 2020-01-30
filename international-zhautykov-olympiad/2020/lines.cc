#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

int main() {
  int n;
  scanf("%d", &n);
  std::priority_queue<int, std::vector<int>, std::greater<int>> a, b;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    a.push(x);
  }
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    b.push(x);
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    assert(a.size() == b.size());
    if (a.top() > b.top()) {
      ++ret;
      b.pop();
      b.push(a.top());
    }
    a.pop(); b.pop();
  }
  printf("%d\n", ret);
  return 0;
}
