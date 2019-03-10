#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 30000 + 10;

struct Event {
  int x, y1, y2;
  int type;
  bool operator < (const Event& rhs) const {
    return x < rhs.x;
  }
};

struct Node {
  int sum, cnt;
} T[N << 2];

void update(int o, int l, int r) {
  if (T[o].cnt > 0) T[o].sum = r - l;
  else if (l + 1 == r) T[o].sum = 0;
  else T[o].sum = T[o << 1].sum + T[o << 1 | 1].sum;
}

void add(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].cnt += v;
    update(o, l, r);
    return;
  }
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R, v);
  if (R > m) add(o << 1 | 1, m, r, L, R, v);
  update(o, l, r);
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<Event> events;
  for (int i = 0; i < n; ++i) {
    int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    events.push_back({x1, y1, y2, +1});
    events.push_back({x2, y1, y2, -1});
  }
  std::sort(events.begin(), events.end());
  int prev = events[0].x;
  int ret = 0;
  for (auto &&e: events) {
    ret += (e.x - prev) * T[1].sum;
    add(1, 0, 30000, e.y1, e.y2, e.type);
    prev = e.x;
  }
  printf("%d\n", ret);
  return 0;
}
